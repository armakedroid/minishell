/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:55:50 by argharag          #+#    #+#             */
/*   Updated: 2025/03/21 20:39:31 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*check_envp(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (*envp + 5);
		envp++;
	}
	perror("cant find path");
	exit(EXIT_FAILURE);
}

static int	open_fi(char *file, int flag)
{
	int	fd;

	if (flag == 0)
		fd = open(file, O_RDONLY, 0444);
	else if (flag == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		exit(EXIT_FAILURE);
	if (fd == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	return (fd);
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

static void	fork_process(char **argv, char **envp, t_my_s *my_s, int is_child)
{
	if (is_child)
	{
		my_s->infile = open_fi(argv[1], 0);
		if (dup2(my_s->infile, STDIN_FILENO) == -1)
			dup_err("cant open input");
		if (dup2(my_s->fd[1], STDOUT_FILENO) == -1)
			dup_err("cant open outfile");
		close(my_s->fd[0]);
		close(my_s->fd[1]);
		close(my_s->infile);
		cmdfile(argv[2], my_s->cmd, envp);
	}
	else
	{
		my_s->outfile = open_fi(argv[4], 1);
		if (dup2(my_s->fd[0], STDIN_FILENO) == -1)
			dup_err("cant open infile");
		if (dup2(my_s->outfile, STDOUT_FILENO) == -1)
			dup_err("cant open outfile");
		close(my_s->fd[0]);
		close(my_s->fd[1]);
		close(my_s->outfile);
		cmdfile(argv[3], my_s->cmd, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_my_s	my_s;

	if (argc != 5)
		dup_err("argc is not correct");
	if (pipe(my_s.fd) == -1)
		dup_err("cant pipe the fd");
	my_s.path = check_envp(envp);
	if (!my_s.path)
		dup_err("PATH not found in envp");
	my_s.cmd = ft_split(my_s.path, ':');
	my_s.proc1 = fork();
	if (my_s.proc1 < 0)
		dup_err("cant do fork");
	else if (my_s.proc1 == 0)
		fork_process(argv, envp, &my_s, 1);
	my_s.proc2 = fork();
	if (my_s.proc2 < 0)
		dup_err("cant do fork2");
	else if (my_s.proc2 == 0)
		fork_process(argv, envp, &my_s, 0);
	free_cmd(my_s.cmd);
	close(my_s.fd[1]);
	close(my_s.fd[0]);
	waitpid(my_s.proc1, NULL, 0);
	waitpid(my_s.proc2, NULL, 0);
}
