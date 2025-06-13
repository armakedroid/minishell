/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:48:13 by argharag          #+#    #+#             */
/*   Updated: 2025/06/12 18:48:48 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

int g_exit_status = 0;

void print_str(char **str, char *type)
{
	int i;

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

void print_cmd(t_output *token)
{
	t_output *tmp;
	char *str;
	int i;

	i = 0;
	str = NULL;
	if (!token)
		return;
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

void print_token(t_token *token)
{
	t_token *tmp;

	if (!token)
		return;
	tmp = token;
	while (tmp)
	{
		printf("token value: %s, token type: %d, token quote: %d\n", tmp->value,
			   tmp->type, tmp->q_type);
		tmp = tmp->next;
	}
}

int is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}

char **command_s(char *line)
{
	char **back;

	back = ft_split(line, ' ');
	if (!back)
		return (NULL);
	return (back);
}

void check_f(char **back, char **envp, char **path, int flag)
{
	char *line;
	int i;

	i = 0;
	line = NULL;
	if (ft_strncmp(back[0], "exit", 5) == 0)
		g_exit_status = 0;
	else if (!ft_strncmp(back[0], "echo", 5))
		g_exit_status = ft_echo(back, g_exit_status);
	else if (!ft_strncmp(back[0], "pwd", 4))
	{
		line = ft_pwd(envp);
		if (line)
			printf("%s\n", line);
		free(line);
	}
	else if (!ft_strncmp(back[0], "env", 4))
		g_exit_status = ft_env(envp);
	else
	{
		if (flag)
			cmdfile(back, path, envp, &g_exit_status);
		else
			cmd_unexit(back, path, envp, &g_exit_status);
	}
	exit(g_exit_status);
}

void free_tokens(t_token *tokens)
{
	t_token *next;

	if (tokens)
	{
		while (tokens)
		{
			next = tokens->next;
			if (tokens->value)
				free(tokens->value);
			if (tokens)
				free(tokens);
			tokens = next;
		}
	}
}

void free_split(char **back)
{
	int i;

	if (!back)
		return;
	i = 0;
	while (back[i])
	{
		free(back[i]);
		i++;
	}
	free(back);
}

void free_cmd(t_output *cmd)
{
	t_output *next;

	if (cmd)
	{
		while (cmd)
		{
			next = cmd->next;
			if (cmd->args && cmd->args[0])
				free_split(cmd->args);
			if (cmd->infile)
				free(cmd->infile);
			if (cmd->outfile)
				free(cmd->outfile);
			free(cmd);
			cmd = next;
		}
	}
}

void handle_sigint(int sl)
{
	(void)sl;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void handle_sigint1(int sl)
{
	(void)sl;
	printf("Artur\n");
	rl_replace_line("", 0);
	// write(1, "\n", 1);
	// rl_on_new_line();
	// rl_redisplay();
	exit(130) ;
}

char **ft_copy_env(char **envp)
{
	char **tmp;
	int i;

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

t_token *create_t(char *str, int i)
{
	t_token *token;

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

static void ft_lstadd_back1(t_token **lst, t_token *new)
{
	t_token *back;

	back = NULL;
	if (!lst || !new)
		return;
	if (*lst == NULL)
	{
		*lst = new;
		return;
	}
	back = *lst;
	while (back->next)
		back = back->next;
	back->next = new;
}

void add_token(t_token **token, char *str, int i)
{
	t_token *new;
	t_token *tmp;

	new = create_t(str, i);
	tmp = *token;
	if (!new)
		return;
	if (!*token)
		*token = new;
	else
		ft_lstadd_back1(token, new);
}

t_token *my_tok(char *line)
{
	int i;
	int start;
	int quote_d;
	t_token *token;

	i = 0;
	start = 0;
	token = NULL;
	while (line[i])
	{
		quote_d = 0;
		if (line[i] == ' ' || (line[i] == '\"' && line[i + 1] == ' '))
			i++;
		else if (line[i] == '|')
		{
			add_token(&token, ft_strdup("|"), PIPE);
			i++;
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
			{
				add_token(&token, ft_strdup(">>"), APPEND);
				i += 2;
			}
			else
			{
				add_token(&token, ft_strdup(">"), OUT);
				i++;
			}
		}
		else if (line[i] == '<')
		{
			if (line[i + 1] == '<')
			{
				add_token(&token, ft_strdup("<<"), HEREDOC);
				i += 2;
			}
			else
			{
				add_token(&token, ft_strdup("<"), IN);
				i++;
			}
		}
		else
		{
			start = i;
			while (line[i] && !is_operator(line[i]) && !is_space(line[i]) && !quote_d)
			{
				if (line[i] == '\"')
				{
					quote_d = 1;
					start = i + 1;
				}
				i++;
			}
			while (line[i] && line[i] != '\"' && quote_d)
			{
				i++;
				if (line[i] == '\"')
				{
					quote_d = 0;
					break;
				}
			}
			if ((line[start] == '\"' && (i - start) == 1) || !(i - start))
				break;
			add_token(&token, ft_substr(line, start, i - start), WORD);
		}
	}
	return (token);
}

void cmdfun(t_output **lst, t_output *new)
{
	t_output *back;

	back = NULL;
	if (!new || !lst)
		return;
	if (*lst == NULL)
	{
		*lst = new;
		return;
	}
	back = *lst;
	while (back->next)
		back = back->next;
	back->next = new;
}

t_output *create_out(char **str, char *infile, char *outfile)
{
	t_output *new;
	int i;

	i = 0;
	new = malloc(sizeof(t_output));
	new->infile = infile;
	new->outfile = outfile;
	new->is_p = 0;
	if (str)
		while (str[i])
			i++;
	new->args = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	if (str)
	{
		while (str[i])
		{
			new->args[i] = ft_strdup(str[i]);
			i++;
		}
	}
	new->next = NULL;
	return (new);
}

t_output *parse(t_token *token)
{
	t_output *back;
	t_output *tmp;
	t_output *for_args;
	int i;

	back = NULL;
	tmp = NULL;
	i = 0;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			if (token->next)
				token = token->next->next;
			else
			{
				g_exit_status = ft_errors(2, NULL, NULL);
				return (NULL);
			}
		}
		if (!token)
			return (back);
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
				tmp = create_out(for_args->args, NULL, NULL);
		}
		if (token->type == PIPE)
		{
			tmp->is_p = 1;
			token = token->next;
			cmdfun(&back, tmp);
			// free_cmd(tmp);
			// tmp = NULL;
			i = 0;
			continue;
		}
		if (token->type == WORD)
		{
			tmp->args[i] = ft_strdup(token->value);
			i++;
			tmp->args[i] = NULL;
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
			g_exit_status = ft_errors(2, NULL, NULL);
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

int main(int argc, char **argv, char **envp)
{
	t_token *token;
	t_token *ttmp;
	int cd_result;
	char *line;
	char **env;
	pid_t cha;
	char *path;
	static int signal1;
	char **my_p;
	t_output *cmd;
	t_output *cmd_start;
	int stdout1;
	int stdin1;
	int fd;
	t_pipe val;

	(void)argv;
	my_p = NULL;
	if (argc != 1)
		return (write(2, "Error: You must run only ./minishell\n", 37));
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	env = ft_copy_env(envp);
	path = get_path(env);
	my_p = ft_split(path, ':');
	fd = 0;
	while (1)
	{
		g_exit_status = 0;
		stdout1 = dup(STDOUT_FILENO);
		stdin1 = dup(STDIN_FILENO);
		line = readline("minishell$ ");
		if (!line)
			break;
		if (*line)
			add_history(line);
		token = my_tok(line);
		ttmp = token;
		while (ttmp)
		{
			if (ttmp->type == HEREDOC && ttmp->next)
				heredoc(ttmp->next->value);
			ttmp = ttmp->next;
		}
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			printf("exit\n");
			free(line);
			free_tokens(token);
			break;
		}
		cmd = parse(token);
		cmd_start = cmd;
		free_tokens(token);
		free(line);
		// print_token(token);
		// printf("\n\n");
		// print_cmd(cmd);
		if (!cmd || !cmd->args)
		{

			if (g_exit_status)
			{
				close(stdin1);
				close(stdout1);
			}
			continue;
		}
		while (cmd->next && cmd->next->is_p != 1)
			cmd = cmd->next;
		if (cmd->outfile)
		{
			g_exit_status = big_crt(cmd, &fd);
		}
		else if (cmd->infile)
			g_exit_status = small(cmd, &fd);
		if (cmd && cmd->next && cmd->next->next && cmd->next->is_p)
			g_exit_status = my_pipe(cmd, &val, env, my_p);
		else
		{
			if (!(ft_strncmp(cmd->args[0], "cd", 3)))
			{
				cd_result = ft_cd(cmd->args, env);
				if (cd_result == 100)
					g_exit_status = ft_errors(100, cmd->args, NULL);
				else if (cd_result == 1)
					g_exit_status = ft_errors1(1, cmd->args, NULL);
			}
			else if (!(ft_strncmp(cmd->args[0], "export", 7)))
				env = ft_export(env, cmd->args);
			else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
				env = ft_unset(env, cmd->args);
			else
			{
				cha = fork();
				if (cha == 0)
				{
					signal(SIGINT, handle_sigint1);
					while (cmd->next)
						cmd = cmd->next;
					check_f(cmd->args, env, my_p, 1);
				}
				else if (cha > 0)
				{
					waitpid(cha, &signal1, 0);
					if (signal1 >= 256)
						g_exit_status = WEXITSTATUS(signal1);
					else
						g_exit_status = signal1 + 128;
				}
				else
					perror("fork");
			}
			dup2(stdout1, STDOUT_FILENO);
			dup2(stdin1, STDIN_FILENO);
			close(stdout1);
			close(stdin1);
			if (fd)
				close(fd);
			// close(df[0]);
			// close(df[1]);
			// waitpid(proc1, NULL, 0);
			// waitpid(proc2, NULL, 0);
		}
		free_cmd(cmd_start);
		// print_cmd(cmd);
	}
	free(path);
	free_split(env);
	free_split(my_p);
	return (0);
}
