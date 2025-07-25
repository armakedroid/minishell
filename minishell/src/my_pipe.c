/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:22:57 by argharag          #+#    #+#             */
/*   Updated: 2025/07/10 19:20:19 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_pipe1(t_pipes *m_p, char **env, char **my_p, t_output *cmds)
{
	if ((*m_p).pid[(*m_p).a] == 0)
		check_f((*m_p).str, env, my_p, 0);
	else
	{
		waitpid((*m_p).pid[(*m_p).a], &(*m_p).errors, 0);
		if ((*m_p).errors)
			(*m_p).errors1 = WEXITSTATUS((*m_p).errors);
		if ((*m_p).errors1)
		{
			if ((*m_p).pid)
				free((*m_p).pid);
			if ((*m_p).fd)
				free_fd((*m_p).fd, (*m_p).cmd_nbr - 1);
			dup2((*m_p).saved_stdout, STDOUT_FILENO);
			close((*m_p).inf);
			ft_errors((*m_p).errors1, (*m_p).str->args, NULL);
			return (1);
		}
	}
	if ((*m_p).inf)
		close((*m_p).inf);
	dup2((*m_p).saved_stdout, STDOUT_FILENO);
	(*m_p).str = cmds;
	(*m_p).in_fd = (*m_p).saved_stdin;
	return (0);
}

void	child_p(t_output *cmds, char **env, t_pipes *m_p, char **my_p)
{
	dup2((*m_p).in_fd, STDIN_FILENO);
	if (cmds->next)
		dup2((*m_p).fd[(*m_p).a][1], STDOUT_FILENO);
	if (cmds->infile)
		small(cmds, &(*m_p).inf);
	if (cmds->outfile)
		big_crt(cmds, &(*m_p).outf);
	if (cmds->next)
	{
		close((*m_p).fd[(*m_p).a][0]);
		close((*m_p).fd[(*m_p).a][1]);
	}
	if ((*m_p).in_fd != (*m_p).saved_stdin)
		close((*m_p).in_fd);
	check_f(cmds, env, my_p, 1);
}

void	cmds_init(t_pipes *m_p, t_output *cmds)
{
	(*m_p).errors1 = 0;
	(*m_p).a = 0;
	(*m_p).cmd_nbr = cmd_count(cmds);
	(*m_p).in_fd = (*m_p).cmd_nbr - 1;
	(*m_p).pid = malloc(sizeof(pid_t) * (*m_p).cmd_nbr);
	(*m_p).fd = malloc(sizeof(int *) * ((*m_p).cmd_nbr - 1));
	while ((*m_p).in_fd > 0)
	{
		((*m_p).fd)[(*m_p).in_fd - 1] = malloc(sizeof(int) * 2);
		((*m_p).in_fd)--;
	}
	(*m_p).in_fd = 0;
	(*m_p).saved_stdin = dup(STDIN_FILENO);
	(*m_p).saved_stdout = dup(STDOUT_FILENO);
	(*m_p).str = cmds;
	while ((*m_p).str->next)
		(*m_p).str = (*m_p).str->next;
	(*m_p).inf = open("/dev/null", O_RDWR | O_CREAT | O_TRUNC, 0666);
	dup2((*m_p).inf, STDOUT_FILENO);
	((*m_p).pid)[(*m_p).a] = fork();
	if (((*m_p).pid)[(*m_p).a] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

int	cmds_utils(t_output *cmds, t_pipes *m_p, char **my_p, char **env)
{
	while (cmds)
	{
		while (cmds->next && !(cmds->is_p))
			cmds = cmds->next;
		if (cmds->next)
			if (pipe(((*m_p).fd)[(*m_p).a]) == -1)
				perror("pipe");
		(*m_p).pid[(*m_p).a] = fork();
		if ((*m_p).pid[(*m_p).a] == 0)
		{
			child_p(cmds, env, &(*m_p), my_p);
		}
		else
			cmds_while_utils(m_p, cmds);
		(*m_p).a++;
		cmds = cmds->next;
	}
	(*m_p).a = 0;
	return (0);
}

int	my_pipe(t_output *cmds, t_mini *var, char **my_p)
{
	t_pipes	m_p;

	m_p.cmd_s = cmds;
	cmds_init(&m_p, cmds);
	if (my_pipe1(&m_p, var->env, my_p, cmds))
		return (1);
	m_p.errors = 0;
	if (cmds_utils(cmds, &m_p, my_p, var->env))
	{
		m_p.in_fd = waitpid((m_p.pid)[m_p.a], &m_p.errors, 0);
		if (m_p.errors)
			m_p.errors1 = WEXITSTATUS(m_p.errors);
		if (m_p.errors1)
		{
			ft_errors(m_p.errors1, m_p.str->args, NULL);
			m_p.errors1 = 0;
		}
		cmds_exit(&m_p);
		return (m_p.errors1);
	}
	my_pipe_while(&m_p);
	cmds_exit(&m_p);
	return (m_p.errors1);
}
