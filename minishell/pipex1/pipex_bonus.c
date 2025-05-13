/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:22:47 by argharag          #+#    #+#             */
/*   Updated: 2025/03/20 19:14:42 by argharag         ###   ########.fr       */
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

int	open_f(char *file, int i)
{
	int	fd;

	if (i)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	heredoc(const char *li)
{
	char	*line;
	int		fd;
	char	**back;

	fd = open(TMP, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(STDIN_FILENO);
		if (!line || !*line)
			break ;
		if (*line != '\n')
		{
			here_doc_u(&line, &back);
			if (ft_strncmp(back[0], li, sizeof(back[0])) == 0)
			{
				free(line);
				break ;
			}
		}
		write(fd, line, strlen(line));
		free(line);
	}
	close(fd);
}

static void	fork_process1(char **argv, char **envp, t_my_s *my_s)
{
	int	tmp;

	tmp = open(TMP, O_RDONLY, 0444);
	if (dup2(tmp, STDIN_FILENO) == -1)
		dup_err("cant open input");
	if (dup2(my_s->fd[1], STDOUT_FILENO) == -1)
		dup_err("cant open outfile");
	close(my_s->fd[0]);
	close(my_s->fd[1]);
	close(tmp);
	cmdfile(argv[3], my_s->cmd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_my_s	my_s;

	if (argc != 6 || ft_strncmp(argv[1], "here_doc", 8) != 0)
		dup_err("argc is not 6 or invalid here_doc");
	heredoc(argv[2]);
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
		fork_process1(argv, envp, &my_s);
	my_s.proc2 = fork();
	if (my_s.proc2 < 0)
		dup_err("cant do fork2");
	else if (my_s.proc2 == 0)
		fork_process2(argv, envp, &my_s);
	free_cmd(my_s.cmd);
	closing(&my_s);
	unlink(TMP);
}
