/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:39:37 by argharag          #+#    #+#             */
/*   Updated: 2025/07/04 16:57:15 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_exit_status = 0;

void	main_ut(t_mini *var)
{
	t_output	*exmpl1;

	(*var).cha = fork();
	if ((*var).cha == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		while ((*var).cmd->next)
		{
			exmpl1 = var->cmd->next;
			free_cmd(var->cmd);
			(*var).cmd = exmpl1;
		}
		free((*var).path);
		check_f((*var).cmd, (*var).env, (*var).my_p, 1);
	}
	else if ((*var).cha > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid((*var).cha, &(*var).signal1, 0);
		dup2((*var).stdout1, STDOUT_FILENO);
		dup2((*var).stdin1, STDIN_FILENO);
		signal(SIGINT, handle_sigint);
		if ((*var).signal1 < 256 && (*var).signal1)
			g_exit_status = ft_errors(WTERMSIG((*var).signal1) + 128, NULL,
					NULL);
		else
			g_exit_status = WEXITSTATUS((*var).signal1);
	}
	else
		perror("fork");
}

void	main_function_utils(t_mini *var)
{
	if ((*var).cmd)
	{
		if ((*var).cmd->outfile)
			g_exit_status = big_crt((*var).cmd, &(*var).fd);
		else if ((*var).cmd->infile)
			g_exit_status = small((*var).cmd, &(*var).fd);
		if (g_exit_status && var->cmd->infile)
			return ;
	}
	if (!(ft_strncmp((*var).cmd->args[0], "cd", 3)))
	{
		(*var).cd_result = ft_cd((*var).cmd->args, (*var).env);
		if ((*var).cd_result == 100)
			g_exit_status = ft_errors(100, (*var).cmd->args, NULL);
		else if ((*var).cd_result == 1)
			g_exit_status = ft_errors1(1, (*var).cmd->args, NULL);
	}
	else if (!(ft_strncmp((*var).cmd->args[0], "export", 7)))
		(*var).env = ft_export((*var).env, (*var).cmd->args);
	else if (ft_strncmp((*var).cmd->args[0], "unset", 6) == 0)
		(*var).env = ft_unset((*var).env, (*var).cmd->args);
	else
		main_ut(&(*var));
	dup2((*var).stdout1, STDOUT_FILENO);
	dup2((*var).stdin1, STDIN_FILENO);
	close((*var).stdout1);
	close((*var).stdin1);
	if ((*var).fd)
		close((*var).fd);
}

int	space_token(t_mini *var, char **env)
{
	(*var).k = 0;
	while ((*var).line[(*var).k])
	{
		while (is_space((*var).line[(*var).k]))
			(*var).k++;
		if ((*var).line[(*var).k] == '|')
		{
			(*var).str = "|";
			g_exit_status = ft_errors(2, &(*var).str, NULL);
		}
		break ;
	}
	if ((*var).line[(*var).k] == '|')
		return (1);
	(*var).token = my_tok((*var).line, env);
	(*var).ttmp = (*var).token;
	while ((*var).ttmp && (*var).ttmp->next)
	{
		if ((*var).ttmp->type == HEREDOC && (*var).ttmp->next)
			heredoc((*var).ttmp->next->value);
		(*var).ttmp = (*var).ttmp->next;
	}
	return (0);
}

t_output *new_parse(t_output *var)
{
	t_output *new;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new = ft_calloc(sizeof(t_output), 1);
	if (var->infile)
		new->infile = ft_strdup(var->infile);
	if (var->outfile)
		new->outfile = ft_strdup(var->outfile);
	if (var->args)
	{
		while (var->args[j])
			j++;
		new->args = ft_calloc(j, sizeof(char *));
		while (var->args[i])
		{
			new->args[i] = ft_strdup(var->args[i]);
			i++;
		}
	}
	return(new);
}


int	parse_and_pipe(t_mini *var)
{
	t_parse		*pa;
	t_output	*exmpl;

	pa = parse((*var).token);
	if (!pa)
		return (1);
	(*var).cmd = pa->back;
	free_parse(pa);
	if ((*var).token)
		free_tokens((*var).token);
	if ((*var).line)
		free((*var).line);
	if (!(*var).cmd || !(*var).cmd->args)
	{
		if (g_exit_status)
		{
			close((*var).stdin1);
			close((*var).stdout1);
		}
		return (1);
	}
	while ((*var).cmd->next && (*var).cmd->next->is_p != 1)
	{
		exmpl = (*var).cmd->next;
		free_cmd((*var).cmd);
		(*var).cmd = exmpl;
	}
	if ((*var).cmd && (*var).cmd->next && (*var).cmd->next->next
		&& (*var).cmd->next->is_p)
		g_exit_status = my_pipe((*var).cmd, (*var).env, (*var).my_p);
	else
		main_function_utils(&(*var));
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	var;
	int		i;

	(void)argv;
	var.my_p = NULL;
	if (argc != 1)
		return (write(2, "Error: You must run only ./minishell\n", 37));
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	initialization(&var, envp);
	g_exit_status = 0;
	tcgetattr(STDIN_FILENO, &var.orig_termios);
	while (1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &var.orig_termios);
		i = main_main(&var, var.env);
		if (i == 2)
			continue ;
		else if (i == 1)
			break ;
		if(var.cmd)
			free_cmd(var.cmd);
	}
	free(var.path);
	free_split(var.env);
	free_split(var.my_p);
	return (g_exit_status);
}
