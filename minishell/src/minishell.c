/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:48:13 by argharag          #+#    #+#             */
/*   Updated: 2025/06/21 18:16:14 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

int			g_exit_status = 0;

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
	i = -1;
	if (str)
	{
		while (str[++i])
			new->args[i] = ft_strdup(str[i]);
	}
	if (str && !infile && !outfile)
		new->args[i] = NULL;
	new->next = NULL;
	return (new);
}

t_output	*parse(t_token *token)
{
	t_parse		parse;

	parse.back = NULL;
	parse.tmp = NULL;
	parse.i = 0;
	while (token)
	{
		if (!token)
			return (parse.back);
		if (!parse_heredoc(&token, &g_exit_status))
			return (NULL);
		if (!token)
			return (parse.back);
		if (my_parse_ut(&parse.back, &parse.tmp, &token, &parse.for_args) == 1)
		{
			parse.i = 0;
			continue ;
		}
		if (parse_wrd(&token, &parse.tmp, &parse.i, &g_exit_status) == 1)
		{
			parse.i = 1;
			return (NULL);
		}
		token = token->next;
		cmdfun(&parse.back, parse.tmp);
	}
	return (parse.back);
}

int exit_var(t_mini *var)
{
	char	**str;
	size_t		k;

	k = 0;
	if (ft_strlen(var->line) > 4)
		if (var->line[4] != ' ')
			return (0);
	printf("exit\n");
	str = ft_split(var->line, ' ');
	if (!str)
		return (1);
	if (str && !str[1])
	{
		free_split(str);
		return (1);
	}
	if (!ft_strncmp(str[1], "$?", 2))
	{
		free_split(str);
		return (1);
	}
	while (str[1][k])
	{
		if (ft_isdigit(str[1][k]))
			k++;
		else
			break ;
	}
	if (!ft_isdigit(ft_atoi(str[1])) && ft_strlen(str[1]) == k)
	{
		if (str[2])
		{
			g_exit_status = ft_errors(100, str, NULL);
			free_split(str);
			return (0);
		}
		g_exit_status = ft_atoi(str[1]);
		free_split(str);
		return (1);
	}
	g_exit_status = ft_errors(2, &str[1], str[0]);
	free_split(str);
	return (1);
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
		var.line1 = readline("-----> minishell$ ");
		if (!var.line1)
			break ;
		if (*var.line1)
			add_history(var.line1);
		var.line = ft_strtrim(var.line1, " ");
		free(var.line1);
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
		while (var.ttmp->next)
		{
			if (var.ttmp->type == HEREDOC && var.ttmp->next)
				heredoc(var.ttmp->next->value);
			var.ttmp = var.ttmp->next;
		}
		if (!ft_strncmp(var.line, "exit", 4))
			if (exit_var(&var))
			{
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
		if (var.cmd && var.cmd->next && var.cmd->next->next 
				&& var.cmd->next->is_p)
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
					check_f(var.cmd->args, var.env, 
							var.my_p, 1, &g_exit_status);
				}
				else if (var.cha > 0)
				{
					signal(SIGINT, SIG_IGN);
					waitpid(var.cha, &var.signal1, 0);
					dup2(var.stdout1, STDOUT_FILENO);
					dup2(var.stdin1, STDIN_FILENO);
					signal(SIGINT, handle_sigint);
					if (var.signal1 < 256 && var.signal1)
						g_exit_status = ft_errors(WTERMSIG(var.signal1)
							+ 128, NULL, NULL);
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
	}
	free(var.path);
	free_split(var.env);
	free_split(var.my_p);
	return (g_exit_status);
}
