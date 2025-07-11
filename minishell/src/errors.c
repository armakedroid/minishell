/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:49:51 by argharag          #+#    #+#             */
/*   Updated: 2025/06/30 19:56:41 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_errors1(int signal, char **back, char *infile)
{
	if ((signal == 127 && back[0][0] == '.') || (signal == 1))
	{
		if (signal == 1)
		{
			if (infile)
				printf("bash : %s: No such file or directory\n", infile);
			else
				printf("bash : %s: No such file or directory\n", back[1]);
		}
		else
			printf("bash : %s: No such file or directory\n", back[0]);
		return (signal);
	}
	else if (signal == 127 && back[0][0] != '.')
	{
		printf("bash : %s: command not found\n", back[0]);
		return (127);
	}
	return (signal);
}

int	ft_errors126(int signal, char **back, char *infile)
{
	char	*line;
	int		fd;

	(void)infile;
	if (signal == 126)
	{
		fd = open(back[0], O_RDONLY);
		if (fd == -1)
			return (printf("bash: %s: Permission denied\n", back[0]), 126);
		line = get_next_line(fd);
		if (line && line[0] == '#' && line[1] == '!')
		{
			printf("bash : %s: %s: ", back[0], line + 2);
			printf("bad interpreter: No such file or directory\n");
		}
		else
			return (printf("bash : %s: Permission denied\n", back[0]), 126);
		close(fd);
		free(line);
	}
	return (126);
}

int	ft_errors_139(int signal, char **back, char *infile)
{
	if (signal == 139)
	{
		printf("Segmentation fault (core dumped)\n");
		return (139);
	}
	else if (signal == 2)
	{
		if (infile)
		{
			if (ft_strncmp(infile, "exit", 4))
				printf("bash: syntax error near unexpected token `%s'\n",
					*back);
			else
				printf("bash: %s: %s: numeric argument required\n", infile,
					*back);
		}
		else
			printf("bash: syntax error near unexpected token `%s'\n", *back);
		return (2);
	}
	return (0);
}

int	ft_errors(int signal, char **back, char *infile)
{
	int	i;

	if (signal == 127)
		return (ft_errors1(signal, back, infile));
	else if (signal == 126)
		return (ft_errors126(signal, back, infile));
	else if (signal == 130 || signal == 131)
	{
		printf("\n");
		return (signal);
	}
	else if (signal == 100)
	{
		printf("bash : %s: too many arguments\n", back[0]);
		return (1);
	}
	i = ft_errors_139(signal, back, infile);
	if (i == 2)
		return (2);
	else if (i == 139)
		return (139);
	return (signal);
}
