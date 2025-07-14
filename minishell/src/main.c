/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:39:37 by argharag          #+#    #+#             */
/*   Updated: 2025/07/14 18:21:44 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_exit_status = 0;

void	main_ut(t_mini *var)
{
	(*var).cha = fork();
	if ((*var).cha == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		while ((*var).cmd->next)
			(*var).cmd = var->cmd->next;
		free_var((*var).path);
		free_cmd_start_wthend(var->cmd_start);
		check_f((*var).cmd, (*var).env, (*var).my_p, 1);
	}
	else if ((*var).cha > 0)
		fork_ut(var);
	else
		perror("fork");
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

t_output	*new_parse(t_output *var)
{
	t_output	*new;
	int			i;
	int			j;

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
	return (new);
}

int	parse_and_pipe(t_mini *var)
{
	if (tokens_and_parse(var))
		return (1);
	if (!(*var).cmd || !(*var).cmd->args)
	{
		if (g_exit_status)
		{
			close((*var).stdin1);
			close((*var).stdout1);
		}
		return (1);
	}
	var->cmd_start = var->cmd;
	while ((*var).cmd->next && (*var).cmd->next->is_p != 1)
		(*var).cmd = var->cmd->next;
	if ((*var).cmd && (*var).cmd->next && (*var).cmd->next->next
		&& (*var).cmd->next->is_p)
		g_exit_status = my_pipe((*var).cmd, var, (*var).my_p);
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
		i = main_while(&var);
		if (i == 2)
			continue ;
		if (i == 1)
			break ;
	}
	free_split(var.env);
	return (g_exit_status);
}
