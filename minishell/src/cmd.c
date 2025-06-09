/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:15:08 by argharag          #+#    #+#             */
/*   Updated: 2025/06/09 21:56:52 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_ut(char **cmd, char *path, char **envp, int *exit_status)
{
	char	*all;

	all = ft_strjoin(path, "/");
	if (cmd[0][0] != '/')
		all = ft_strjoin(all, cmd[0]);
	else
		all = ft_strjoin(all, ft_strrchr(cmd[0], '/') + 1);
	if (access(all, F_OK) == 0)
	{
		if (access(all, X_OK) == 0)
			execve(all, cmd, envp);
		free_split(cmd);
		*exit_status = ft_errors126(126, cmd, NULL);
	}
	free(all);
	all = NULL;
}

int	cmdfile(char **cmd, char **path, char **envp, int *exit_status)
{
	int		i;

	i = 0;
	if (!cmd || !*cmd)
	{
		*exit_status = 127;
		return (1);
	}
	if (cmd[0][0] == '.' && cmd[0][1] == '/')
	{
		if (access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd, envp);
		*exit_status = ft_errors126(126, cmd, NULL);
	}
	else
	{
		while (path[i])
		{
			cmd_ut(cmd, path[i], envp, exit_status);
			i++;
		}
	}
	*exit_status = ft_errors(127, cmd, NULL);
	return (*exit_status);
}

int	cmd_ut_unex(char **cmd, char *path, char **envp, int *exit_status)
{
	char	*all;

	all = ft_strjoin(path, "/");
	if (cmd[0][0] != '/')
		all = ft_strjoin(all, cmd[0]);
	else
		all = ft_strjoin(all, ft_strrchr(cmd[0], '/') + 1);
	if (access(all, F_OK) == 0)
	{
		if (access(all, X_OK) == 0)
			return (0);
		free_split(cmd);
		*exit_status = ft_errors126(126, cmd, NULL);
	}
	free(all);
	all = NULL;
	return (1);
}

int	cmd_unexit(char **cmd, char **path, char **envp, int *exit_status)
{
	int		i;

	i = 0;
	if (!cmd || !*cmd)
	{
		*exit_status = 127;
		return (1);
	}
	if (cmd[0][0] == '.' && cmd[0][1] == '/')
	{
		if (access(cmd[0], X_OK) == 0)
			return (0);
		*exit_status = ft_errors126(126, cmd, NULL);
	}
	else
	{
		while (path[i])
		{
			if (!cmd_ut_unex(cmd, path[i], envp, exit_status))
				return (0);
			i++;
		}
	}
	*exit_status = ft_errors(127, cmd, NULL);
	return (*exit_status);
}