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

int	small(char **back)
{
	int	i;
	int	j;
	int fd;

	i = 0;
	while (back[i])
	{
		j = 0;
		while (back[i][j])
		{
			if (back[i][j] == '<')
				break;
			j++;
		}
		i++;
	}
	fd = open(back[i + 1], O_RDONLY, 0444);
	if (!fd)
		ft_errors(127, back);
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_errors(127, back);
	return (0);
}

int	big_app(char **back)
{
	int	i;
	int	j;
	int fd;

	i = 0;
	while (back[i])
	{
		j = 0;
		while (back[i][j] && back[i][j + 1])
		{
			if (back[i][j] == '>' && back[i][j + 1] == '>')
				break;
			j++;
		}
		i++;
	}
	fd = open(back[i + 1], O_WRONLY | O_CREAT, 0666);
	if (!fd)
		ft_errors(127, back);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_errors(127, back);
	return (0);
}

int	big_crt(char **back)
{
	int	i;
	int	j;
	int fd;

	i = 0;
	while (back[i])
	{
		j = 0;
		while (back[i][j])
		{
			if (back[i][j] == '>')
				break;
			j++;
		}
		i++;
	}
	fd = open(back[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (!fd)
		ft_errors(127, back);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_errors(127, back);
	return (0);
}
