/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:48:13 by argharag          #+#    #+#             */
/*   Updated: 2025/06/15 19:05:20 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

int			g_exit_status = 0;

void	print_str(char **str, char *type)
{
	int	i;

	i = 0;
	if (str || *str)
	{
		while (str[i])
		{
			printf("%s = %s\n", type, str[i]);
			i++;
		}
	}
}

void	print_cmd(t_output *token)
{
	t_output	*tmp;
	char		*str;
	int			i;

	i = 0;
	str = NULL;
	if (!token)
		return ;
	while (token->args[i])
	{
		str = ft_strjoin(str, token->args[i]);
		i++;
	}
	if (token)
	{
		tmp = token;
		while (tmp)
		{
			printf("infile: %s, outfile: %s, is_p: %d, next: %d, ", tmp->infile,
				tmp->outfile, tmp->is_p, !(!(tmp->next)));
			print_str(tmp->args, "args");
			printf("\n");
			tmp = tmp->next;
		}
	}
}

void	print_token(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	tmp = token;
	while (tmp)
	{
		printf("token value: %s, token type: %d, token quote: %d\n", tmp->value,
			tmp->type, tmp->q_type);
		tmp = tmp->next;
	}
}

void	handle_sigint(int sl)
{
	(void)sl;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

char	**ft_copy_env(char **envp)
{
	char	**tmp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	tmp = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "SHLVL=", 7))
			envp[i] = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(envp[i] + 6) + 1));
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

t_token	*create_t(char *str, int i)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = str;
	token->type = i;
	token->q_type = DOUBLE;
	if (str[0] == '\'')
		token->q_type = SINGLE;
	token->next = NULL;
	return (token);
}

static void	ft_lstadd_back1(t_token **lst, t_token *new)
{
	t_token	*back;

	back = NULL;
	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	back = *lst;
	while (back->next)
		back = back->next;
	back->next = new;
}

void	add_token(t_token **token, char *str, int i)
{
	t_token	*new;

	new = create_t(str, i);
	if (!new)
		return ;
	if (!*token)
		*token = new;
	else
		ft_lstadd_back1(token, new);
}


void	cmdfun(t_output **lst, t_output *new)
{
	t_output	*back;

	back = NULL;
	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	back = *lst;
	while (back->next)
		back = back->next;
	back->next = new;
}

t_output	*create_out(char **str, char *infile, char *outfile)
{
	t_output	*new;
	int			i;

	i = 0;
	new = malloc(sizeof(t_output));
	new->infile = infile;
	new->outfile = outfile;
	new->is_p = 0;
	new->num = 0;
	if (str)
		while (str[i])
			i++;
	new->args = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	if (str)
	{
		while (str[i])
		{
			new->args[i] = ft_strdup(str[i]);
			i++;
		}
	}
	if (str && !infile && !outfile)
		new->args[i] = NULL;
	new->next = NULL;
	return (new);
}

t_output	*parse(t_token *token)
{
	t_output	*back;
	t_output	*tmp;
	t_output	*for_args;
	int			i;
	char		*str;

	back = NULL;
	tmp = NULL;
	i = 0;
	while (token)
	{
		if (!token)
			return (back);
		if (token->type == HEREDOC)
		{
			if (token->next)
				token = token->next->next;
			else
			{
				str = "newline";
				g_exit_status = ft_errors(2, &str, NULL);
				return (NULL);
			}
		}
		if (!back)
			tmp = create_out(NULL, NULL, NULL);
		else
		{
			// free_cmd(tmp);
			for_args = back;
			while (for_args->next)
				for_args = for_args->next;
			if (!(for_args->is_p))
				tmp = create_out(for_args->args, for_args->infile,
						for_args->outfile);
			else
				tmp = create_out(NULL, NULL, NULL);
		}
		if (token->type == PIPE)
		{
			// free_split(tmp->args);
			// tmp->args = NULL;
			tmp->is_p = 1;
			token = token->next;
			cmdfun(&back, tmp);
			// free_split(tmp->args);
			// tmp->args = ft_strdup("|");
			// tmp = NULL;
			i = 0;
			continue ;
		}
		if (token->type == WORD)
		{
			// if (!(tmp->args))
			tmp->args[i] = ft_strdup(token->value);
			i++;
			// tmp->args[i] = NULL;
		}
		else if (token->next)
		{
			if (token->type == IN)
			{
				token = token->next;
				tmp->infile = ft_strdup(token->value);
			}
			else if (token->type == OUT)
			{
				token = token->next;
				tmp->outfile = ft_strdup(token->value);
			}
			else if (token->type == APPEND)
			{
				token = token->next;
				tmp->outfile = ft_strdup(token->value);
				tmp->num = 1;
			}
		}
		else
		{
			str = "newline";
			g_exit_status = ft_errors(2, &str, NULL);
			return (NULL);
		}
		token = token->next;
		cmdfun(&back, tmp);
		// free_cmd(tmp);
		// tmp = NULL;
	}
	// print_cmd(tmp);
	// free(tmp->args[0]);
	return (back);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	var;

	(void)argv;
	var.my_p = NULL;
	if (argc != 1)
		return (write(2, "Error: You must run only ./minishell\n", 37));
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	var.env = ft_copy_env(envp);
	var.path = get_path(var.env);
	var.my_p = ft_split(var.path, ':');
	var.fd = 0;
	g_exit_status = 0;
	tcgetattr(STDIN_FILENO, &var.orig_termios);
	while (1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &var.orig_termios);
		var.stdout1 = dup(STDOUT_FILENO);
		var.stdin1 = dup(STDIN_FILENO);
		var.line = readline("\n-------> minishell$ ");
		if (!var.line)
			break ;
		if (*var.line)
			add_history(var.line);
		var.k = 0;
		while (var.line[var.k])
		{
			while (is_space(var.line[var.k]))
				var.k++;
			if (var.line[var.k] == '|')
			{
				var.path = "|";
				ft_errors(2, &var.path, NULL);
			}
			break ;
		}
		if (var.line[var.k] == '|')
			continue ;
		var.token = my_tok(var.line);
		var.ttmp = var.token;
		while (var.ttmp)
		{
			if (var.ttmp->type == HEREDOC && var.ttmp->next)
				heredoc(var.ttmp->next->value);
			var.ttmp = var.ttmp->next;
		}
		if (ft_strncmp(var.line, "exit", 5) == 0)
		{
			printf("exit\n");
			free(var.line);
			free_tokens(var.token);
			break ;
		}
		var.cmd = parse(var.token);
		var.cmd_start = var.cmd;
		free_tokens(var.token);
		free(var.line);
		// print_token(var.token);
		// printf("\n\n");
		// print_cmd(var.cmd);
		if (!var.cmd || !var.cmd->args)
		{
			if (g_exit_status)
			{
				close(var.stdin1);
				close(var.stdout1);
			}
			continue ;
		}
		while (var.cmd->next && var.cmd->next->is_p != 1)
			var.cmd = var.cmd->next;
		if (var.cmd && var.cmd->next && var.cmd->next->next && var.cmd->next->is_p)
		{
			g_exit_status = my_pipe(var.cmd, &var.val, var.env, var.my_p);
		}
		else
		{
			if (var.cmd->outfile)
				g_exit_status = big_crt(var.cmd, &var.fd);
			else if (var.cmd->infile)
				g_exit_status = small(var.cmd, &var.fd);
			if (!(ft_strncmp(var.cmd->args[0], "cd", 3)))
			{
				var.cd_result = ft_cd(var.cmd->args, var.env);
				if (var.cd_result == 100)
					g_exit_status = ft_errors(100, var.cmd->args, NULL);
				else if (var.cd_result == 1)
					g_exit_status = ft_errors1(1, var.cmd->args, NULL);
			}
			else if (!(ft_strncmp(var.cmd->args[0], "export", 7)))
				var.env = ft_export(var.env, var.cmd->args);
			else if (ft_strncmp(var.cmd->args[0], "unset", 6) == 0)
				var.env = ft_unset(var.env, var.cmd->args);
			else
			{
				var.cha = fork();
				if (var.cha == 0)
				{
					signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
					while (var.cmd->next)
						var.cmd = var.cmd->next;
					check_f(var.cmd->args, var.env, var.my_p, 1, &g_exit_status);
				}
				else if (var.cha > 0)
				{
					signal(SIGINT, SIG_IGN);
					waitpid(var.cha, &var.signal1, 0);
					dup2(var.stdout1, STDOUT_FILENO);
					dup2(var.stdin1, STDIN_FILENO);
					signal(SIGINT, handle_sigint);
					if (var.signal1 < 256 && var.signal1)
						g_exit_status = ft_errors(WTERMSIG(var.signal1) + 128, NULL,
								NULL);
					else
						g_exit_status = WEXITSTATUS(var.signal1);
				}
				else
					perror("fork");
			}
			dup2(var.stdout1, STDOUT_FILENO);
			dup2(var.stdin1, STDIN_FILENO);
			close(var.stdout1);
			close(var.stdin1);
			if (var.fd)
				close(var.fd);
		}
		free_cmd(var.cmd_start);
		// print_cmd(var.cmd);
	}
	free(var.path);
	free_split(var.env);
	free_split(var.my_p);
	return (0);
}
