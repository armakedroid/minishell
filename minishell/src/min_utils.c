/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:28:34 by argharag          #+#    #+#             */
/*   Updated: 2025/06/22 18:27:54 by apetoyan         ###   ########.fr       */
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

void	check_f(char **back, char **envp, char **path, int flag)
{
	char	*line;

	line = NULL;
	if (ft_strncmp(back[0], "exit", 5) == 0)
		g_exit_status = 0;
	else if (!ft_strncmp(back[0], "echo", 5))
		g_exit_status = ft_echo(back, g_exit_status);
	else if (!ft_strncmp(back[0], "pwd", 4))
	{
		line = ft_pwd();
		if (line)
			printf("%s\n", line);
		free(line);
	}
	else if (!ft_strncmp(back[0], "env", 4))
		g_exit_status = ft_env(envp);
	else
	{
		if (flag)
			cmdfile(back, path, envp, &g_exit_status);
		else
			cmd_unexit(back, path, envp, &g_exit_status);
	}
	exit(g_exit_status);
}

int	main_main(t_mini *var)
{
	(*var).stdout1 = dup(STDOUT_FILENO);
	(*var).stdin1 = dup(STDIN_FILENO);
	(*var).line1 = readline("-----> minishell$ ");
	if (!(*var).line1)
		return (1);
	if (*(*var).line1)
		add_history((*var).line1);
	(*var).line = ft_strtrim((*var).line1, " ");
	free((*var).line1);
	if (space_token(&(*var)))
		return (2);
	if (!ft_strncmp((*var).line, "exit", 4))
	{
		if (exit_var(var))
		{
			free((*var).line);
			free_tokens((*var).token);
			return (1);
		}
	}
	if (parse_and_pipe(&(*var)))
		return (2);
	return (0);
}
