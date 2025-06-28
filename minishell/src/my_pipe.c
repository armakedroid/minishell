/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:22:57 by argharag          #+#    #+#             */
/*   Updated: 2025/06/28 18:23:04 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_pipe(t_output *cmds, t_pipe *val, char **env, char **my_p)
{
	int			saved_stdin;
	int			saved_stdout;
	int			in_fd;
	int			**fd;
	int			errors;
	int			errors1;
	int			inf;
	int			outf;
	pid_t		*pid;
	int			a;
	int			cmd_nbr;
	t_output	*str;

	(void)val;
	errors = 0;
	errors1 = 0;
	a = 0;
	cmd_nbr = cmd_count(cmds);
	in_fd = cmd_nbr - 1;
	pid = malloc(sizeof(pid_t) * cmd_nbr);
	fd = malloc(sizeof(int *) * (cmd_nbr - 1));
	while (in_fd > 0)
	{
		fd[in_fd - 1] = malloc(sizeof(int) * 2);
		in_fd--;
	}
	in_fd = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	str = cmds;
	while (str->next)
		str = str->next;
	inf = open("/dev/null", O_RDWR, 0666);
	dup2(inf, STDOUT_FILENO);
	pid[a] = fork();
	if (pid[a] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid[a] == 0)
	{
		check_f(str->args, env, my_p, 0);
	}
	else
	{
		waitpid(pid[a], &errors, 0);
		if (errors)
			errors1 = WEXITSTATUS(errors);
		if (errors1)
		{
			if (pid)
				free(pid);
			if (fd)
				free_fd(fd, cmd_nbr - 1);
			dup2(saved_stdout, STDOUT_FILENO);
			close(inf);
			ft_errors(errors1, str->args, NULL);
			return (errors1);
		}
	}
	if (inf)
		close(inf);
	dup2(saved_stdout, STDOUT_FILENO);
	str = cmds;
	in_fd = saved_stdin;
	a = 0;
	errors = 0;
	errors1 = 0;
	while (cmds)
	{
		while (cmds->next && !(cmds->is_p))
			cmds = cmds->next;
		if (cmds->next)
			if (pipe(fd[a]) == -1)
				perror("pipe");
		pid[a] = fork();
		if (pid[a] == 0)
		{
			dup2(in_fd, STDIN_FILENO);
			if (cmds->next)
				dup2(fd[a][1], STDOUT_FILENO);
			if (cmds->infile)
				small(cmds, &inf);
			if (cmds->outfile)
				big_crt(cmds, &outf);
			if (cmds->next)
			{
				close(fd[a][0]);
				close(fd[a][1]);
			}
			if (in_fd != saved_stdin)
				close(in_fd);
			check_f(cmds->args, env, my_p, 1);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (in_fd != saved_stdin)
				close(in_fd);
			if (cmds->next)
			{
				close(fd[a][1]);
				in_fd = fd[a][0];
			}
		}
		a++;
		cmds = cmds->next;
	}
	a = 0;
	while (a < cmd_nbr)
	{
		str = str->next;
		while (str->next && !(str->is_p))
			str = str->next;
		in_fd = waitpid(pid[a], &errors, 0);
		if (errors)
		{
			errors1 = WEXITSTATUS(errors);
		}
		if (errors1)
		{
			ft_errors(errors1, str->args, NULL);
			errors1 = 0;
		}
		a++;
	}
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	if (pid)
		free(pid);
	if (fd)
		free_fd(fd, cmd_nbr - 1);
	return (errors1);
}
