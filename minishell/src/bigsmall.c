/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigsmall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:58:26 by argharag          #+#    #+#             */
/*   Updated: 2025/05/31 18:17:37 by argharag         ###   ########.fr       */
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
}

int m_pipe(t_output *back, int *df, int is_child)
{
	int	infile;
	int	outfile;

	if (is_child)
	{
		infile = open_fi(back->args, 0);
		if (infile == 1)
			return (1);
		if (dup2(infile, STDIN_FILENO) == -1)
			return (ft_errors(1, NULL, 0));
		if (dup2(df[1], STDOUT_FILENO) == -1)
			return (ft_errors(1, NULL, 0));
		close(df[0]);
		close(df[1]);
		close(infile);
	}
	else
	{
		outfile = open_fi(back->args, 1);
		if (outfile == 1)
			return (1);
		if (dup2(df[0], STDIN_FILENO) == -1)
			return (ft_errors(1, NULL, 0));
		if (dup2(outfile, STDOUT_FILENO) == -1)
			return (ft_errors(1, NULL, 0));
		close(df[0]);
		close(df[1]);
		close(outfile);
	}
	return (0);
}*/
