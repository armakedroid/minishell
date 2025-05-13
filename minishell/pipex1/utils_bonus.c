/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:23:02 by argharag          #+#    #+#             */
/*   Updated: 2025/03/21 20:48:57 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_u(char **line, char ***back)
{
	*back = ft_split(*line, '\n');
	if (!*back || !**back)
		return ;
}

void	fork_process2(char **argv, char **envp, t_my_s *my_s)
{
	my_s->outfile = open_f(argv[5], 1);
	if (dup2(my_s->fd[0], STDIN_FILENO) == -1)
		dup_err("cant open infile");
	if (dup2(my_s->outfile, STDOUT_FILENO) == -1)
		dup_err("cant open outfile");
	close(my_s->fd[0]);
	close(my_s->fd[1]);
	close(my_s->outfile);
	cmdfile(argv[4], my_s->cmd, envp);
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	dup_err(const char *str)
{
	if (errno == 0)
		errno = EIO;
	perror(str);
	exit(EXIT_FAILURE);
}

void	closing(t_my_s *my_s)
{
	close(my_s->fd[1]);
	close(my_s->fd[0]);
	waitpid(my_s->proc1, NULL, 0);
	waitpid(my_s->proc2, NULL, 0);
}
