/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigsmall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:58:26 by argharag          #+#    #+#             */
/*   Updated: 2025/05/29 20:26:28 by apetoyan         ###   ########.fr       */
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
