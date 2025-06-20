/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigsmall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:58:26 by argharag          #+#    #+#             */
/*   Updated: 2025/06/19 18:51:09 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	small(t_output *back, int *fd)
{
	int	dup_res;

	if (back->infile)
	{
		*fd = open(back->infile, O_RDONLY, 0444);
		if (*fd == -1)
			return (ft_errors1(1, back->args, back->infile));
	}
	dup_res = dup2(*fd, STDIN_FILENO);
	if (dup_res == -1)
		return (ft_errors1(127, back->args, NULL));
	close(*fd);
	return (0);
}
void	here_doc_u(char **line, char ***back)
{
	*back = ft_split(*line, '\n');
	if (!*back || !**back)
		return ;
}

void	heredoc(const char *li)
{
	char	*line;
	int		fd;
	char	**back;

	fd = open(TMP, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	while (1)
	{
		write(1, "> ", 2);
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
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
}

int	big_crt(t_output *back, int *fd)
{
	int	dup_res;

	if (back->outfile && back->num == 1)
	{
		*fd = open(back->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (*fd == -1)
			return (ft_errors1(1, back->args, NULL));
	}
	else if (back->outfile)
	{
		*fd = open(back->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (*fd == -1)
			return (ft_errors1(1, back->args, NULL));
	}
	dup_res = dup2(*fd, STDOUT_FILENO);
	if (dup_res == -1)
		return (ft_errors1(127, back->args, NULL));
	close(*fd);
	return (0);
}

int	cmd_count(t_output *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		if (cmds->is_p)
			count++;
		cmds = cmds->next;
	}
	return (count + 1);
}

void	free_fd(int **fd, int i)
{
	while (i > 0)
	{
		free(fd[i - 1]);
		i--;
	}
	free(fd);
}

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

	// pid_t	pid;
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
		check_f(str->args, env, my_p, 0, 0);
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
			{
				small(cmds, &inf);
				// inf = open(cmds->infile, O_RDONLY);
				// if (inf == -1)
				// 	perror(cmds->infile), exit(EXIT_FAILURE);
				// dup2(inf, STDIN_FILENO);
				// close(inf);
			}
			if (cmds->outfile)
			{
				big_crt(cmds, &outf);
				// if (cmds->num == 1)
				// 	flags = (O_RDWR | O_CREAT | O_APPEND);
				// else
				// 	flags = (O_RDWR | O_CREAT | O_TRUNC);
				// outf = open(cmds->outfile, flags, 0666);
				// if (outf == -1)
				// 	perror(cmds->outfile), exit(EXIT_FAILURE);
				// dup2(outf, STDOUT_FILENO);
				// close(outf);
			}
			if (cmds->next)
			{
				close(fd[a][0]);
				close(fd[a][1]);
			}
			if (in_fd != saved_stdin)
				close(in_fd);
			check_f(cmds->args, env, my_p, 1, 0);
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
			errors1 = WEXITSTATUS(errors);
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
