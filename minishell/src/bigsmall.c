/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigsmall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:58:26 by argharag          #+#    #+#             */
/*   Updated: 2025/06/03 21:03:36 by argharag         ###   ########.fr       */
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
			return (ft_errors(1, back->args, back->infile));
	}
	dup_res = dup2(*fd, STDIN_FILENO);
	if (dup_res == -1)
		return (ft_errors(127, back->args, NULL));
	close(*fd);
	return (0);
}
void here_doc_u(char **line, char ***back)
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
		write(fd, line, strlen(line));
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
			return (ft_errors(1, back->args, NULL));
	}
	else if (back->outfile)
	{
		*fd = open(back->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (*fd == -1)
			return (ft_errors(1, back->args, NULL));
	}
	dup_res = dup2(*fd, STDOUT_FILENO);
	if (dup_res == -1)
		return (ft_errors(127, back->args, NULL));
	close(*fd);
	return (0);
}
/*
 int	open_fi(char *file, int flag)
{
	int	fd;

	if (flag == 0)
		fd = open(file, O_RDONLY, 0444);
	else if (flag == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		return(ft_errors(1, NULL, 1));
	if (fd == -1)
		return(ft_errors(1, NULL, 1));
	return (fd);
}*/
void my_pipe(t_output *cmds, t_pipe *val, char **env, char **my_p)
{
	int	out_fd;

	write(1, "1\n", 2);
	out_fd = STDOUT_FILENO;
	val->in_fd = STDIN_FILENO;
	while (cmds)
	{
		if (cmds->next)
			pipe(val->fd);
		val->pid = fork();
		if (val->pid == 0)
		{
			dup2(val->in_fd, STDIN_FILENO);
			if (cmds->next)
				dup2(val->fd[1], STDOUT_FILENO);
			if (cmds->infile)
			{
				val->in = open(cmds->infile, O_RDONLY);
				if (val->in != -1)
					dup2(val->in, STDIN_FILENO);
			}
 			if (cmds->outfile)
			{
				if (cmds->num == 1)
					val->out = open(cmds->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
			else
				val->out = open(cmds->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				if (val->out != -1)
					dup2(val->out, STDOUT_FILENO);
			}
			if (cmds->next)
			{
				close(val->fd[0]);
				close(val->fd[1]);
			}
			if (val->in_fd != STDIN_FILENO)
				close(val->in_fd);
			write(1, "2\n", 2);
			check_f(cmds->args, env, my_p);
			write(1, "3\n", 2);
			exit(0);
		}
		else
		{
			waitpid(val->pid, NULL, 0);
			printf("\nwaitpidi tak\n");
			if (val->in_fd != STDIN_FILENO)
				close(val->in_fd);
			if (cmds->next)
			{
				close(val->fd[1]);
				val->in_fd = val->fd[0];
			}
		}
		//dup2(val->fd[0], out_fd);
		//close(out_fd);
		cmds = cmds->next;
	}
	write(1, "4\n", 2);
}
