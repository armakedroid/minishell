/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:48:06 by argharag          #+#    #+#             */
/*   Updated: 2025/07/13 14:48:15 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void fork_ut(t_mini *var)
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

void	main_function_utils(t_mini *var)
{
	if ((*var).cmd)
	{
		if ((*var).cmd->outfile)
			g_exit_status = big_crt((*var).cmd, &(*var).fd);
		else if ((*var).cmd->infile)
			g_exit_status = small((*var).cmd, &(*var).fd);
		if ((var->cmd->outfile || var->cmd->infile) && (g_exit_status
				|| !var->cmd->args[0]))
		{
			dup2((*var).stdout1, STDOUT_FILENO);
			dup2((*var).stdin1, STDIN_FILENO);
			close((*var).stdout1);
			close((*var).stdin1);
			if ((*var).fd)
				close((*var).fd);
			return ;
		}
	}
	var_f(var);
}

int tokens_and_parse(t_mini *var)
{
	t_parse	*pa;

	pa = parse((*var).token);
	if (!pa)
		return (1);
	(*var).cmd = pa->back;
	free_parse(pa);
	if ((*var).token)
		free_tokens((*var).token);
	free_var((*var).line);
	return (0);
}

int	main_while(t_mini *var)
{
	int	i;

	tcsetattr(STDIN_FILENO, TCSANOW, &var->orig_termios);
	var->path = get_path(var->env);
	var->my_p = ft_split(var->path, ':');
	i = main_main(&(*var), var->env);
	if (i)
	{
		free_var(var->path);
		free_split(var->my_p);
		if (i == 2)
			return (2);
		return (1);	
	}
	free_cmd_start(var->cmd_start);
	free_var(var->path);
	free_split(var->my_p);
	return (0);
}

void cmds_while_utils(t_pipes *m_p, t_output *cmds)
{
	if ((*m_p).in_fd != (*m_p).saved_stdin)
	close((*m_p).in_fd);
		if (cmds->next)
	{
		close(((*m_p).fd)[(*m_p).a][1]);
		(*m_p).in_fd = ((*m_p).fd)[(*m_p).a][0];
	}
}
