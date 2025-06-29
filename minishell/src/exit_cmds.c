#include "../includes/minishell.h"

void cmds_exit(t_pipes *m_p)
{
	dup2((*m_p).saved_stdin, STDIN_FILENO);
	dup2((*m_p).saved_stdout, STDOUT_FILENO);
	close((*m_p).saved_stdin);
	close((*m_p).saved_stdout);
	if ((*m_p).pid)
		free((*m_p).pid);
	if ((*m_p).fd)
		free_fd((*m_p).fd, (*m_p).cmd_nbr - 1);
}