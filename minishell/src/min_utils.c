/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:28:34 by argharag          #+#    #+#             */
/*   Updated: 2025/06/16 21:28:59 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 11))
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}

char	**command_s(char *line)
{
	char	**back;

	back = ft_split(line, ' ');
	if (!back)
		return (NULL);
	return (back);
}

void	check_f(char **back, char **envp, char **path, int flag, int *g_exit_status)
{
	char	*line;

	line = NULL;
	if (ft_strncmp(back[0], "exit", 5) == 0)
		*g_exit_status = 0;
	else if (!ft_strncmp(back[0], "echo", 5))
		*g_exit_status = ft_echo(back, *g_exit_status);
	else if (!ft_strncmp(back[0], "pwd", 4))
	{
		line = ft_pwd(envp);
		if (line)
			printf("%s\n", line);
		free(line);
	}
	else if (!ft_strncmp(back[0], "env", 4))
		*g_exit_status = ft_env(envp);
	else
	{
		if (flag)
			cmdfile(back, path, envp, &*g_exit_status);
		else
			cmd_unexit(back, path, envp, &*g_exit_status);
	}
	exit(*g_exit_status);
}

