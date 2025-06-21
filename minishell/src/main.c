/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:39:37 by argharag          #+#    #+#             */
/*   Updated: 2025/06/21 18:43:53 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

void main_ut(t_mini *var)
{
	(*var).cha = fork();
	if ((*var).cha == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		while ((*var).cmd->next)
			(*var).cmd = (*var).cmd->next;
		check_f((*var).cmd->args, (*var).env, 
				(*var).my_p, 1, &g_exit_status);
	}
	else if ((*var).cha > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid((*var).cha, &(*var).signal1, 0);
		dup2((*var).stdout1, STDOUT_FILENO);
		dup2((*var).stdin1, STDIN_FILENO);
		signal(SIGINT, handle_sigint);
		if ((*var).signal1 < 256 && (*var).signal1)
			g_exit_status = ft_errors(WTERMSIG((*var).signal1)
				+ 128, NULL, NULL);
		else
			g_exit_status = WEXITSTATUS((*var).signal1);
	}
	else
		perror("fork");
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
			if (exit_var(&var, &g_exit_status))
			{
				free(var.line);
				free_tokens(var.token);
				break ;
			}
		var.cmd = parse(var.token, &g_exit_status);
		var.cmd_start = var.cmd;
		free_tokens(var.token);
		free(var.line);

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
				main_ut(&var);
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
