/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigsmall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:58:26 by argharag          #+#    #+#             */
/*   Updated: 2025/05/22 21:25:10 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	small(t_output *back)
{
	int	i;
	int	j;
	int fd;

	i = 0;
	while (back->args[i])
	{
		j = 0;
		while (back->args[i][j])
		{
			if (back->args[i][j] == '<')
				break;
			j++;
		}
		i++;
	}
	fd = open(back->args[i + 1], O_RDONLY, 0444);
	if (!fd)
		ft_errors(127, back->args);
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_errors(127, back->args);
	return (0);
}

int	big_app(t_output *back)
{
	int	i;
	int	j;
	int fd;

	i = 0;
	while (back->args[i])
	{
		j = 0;
		while (back->args[i][j] && back->args[i][j + 1])
		{
			if (back->args[i][j] == '>' && back->args[i][j + 1] == '>')
				break;
			j++;
		}
		i++;
	}
	fd = open(back->args[i + 1], O_WRONLY | O_CREAT, 0666);
	if (!fd)
		ft_errors(127, back->args);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_errors(127, back->args);
	return (0);
}

int	big_crt(t_output *back)
{
	int	i;
	int	j;
	int fd;

	i = 0;
	while (back->args[i])
	{
		printf("args = %s\n", back->args[i]);
		j = 0;
		while (back->args[i][j])
		{
			if (back->args[i][j] == '>')
				break;
			j++;
		}
		i++;
	}
	if (back->outfile)
	{
		fd = open(back->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			return ft_errors(127, back->args);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return ft_errors(127, back->args);
	}
	return (0);
}
