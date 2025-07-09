/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:09:50 by apetoyan          #+#    #+#             */
/*   Updated: 2025/07/09 20:15:06 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmds_exit(t_pipes *m_p)
{
	if ((*m_p).in_fd != (*m_p).saved_stdin)
		close((*m_p).in_fd);
	dup2((*m_p).saved_stdin, STDIN_FILENO);
	dup2((*m_p).saved_stdout, STDOUT_FILENO);
	close((*m_p).saved_stdin);
	close((*m_p).saved_stdout);
	if ((*m_p).pid)
		free((*m_p).pid);
	if ((*m_p).fd)
		free_fd((*m_p).fd, (*m_p).cmd_nbr - 1);
}
