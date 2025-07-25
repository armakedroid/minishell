/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:15:08 by argharag          #+#    #+#             */
/*   Updated: 2025/06/26 20:18:11 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_ut(char **cmd, char *path, char **envp, int *exit_status)
{
	char	*all;
	char	*str;

	if (cmd[0][0] != '/')
	{
		all = ft_strjoin("/", cmd[0]);
		str = ft_strjoin(path, all);
		free_var(all);
	}
	else
		str = ft_strdup(cmd[0]);
	if (access(str, F_OK) == 0 && path)
	{
		if (access(str, X_OK) == 0)
		{
			execve(str, cmd, envp);
			perror("execve failed");
			free_var(str);
		}
		free_split(cmd);
		*exit_status = ft_errors126(126, cmd, NULL);
	}
	free_var(str);
	str = NULL;
}

int	cmdfile(char **cmd, char **path, char **envp, int *exit_status)
{
	int	i;

	i = 0;
	if (!cmd || !*cmd)
	{
		*exit_status = 127;
		return (1);
	}
	if (ft_strlen(cmd[0]) > 1 && cmd[0][0] == '.' && cmd[0][1] == '/')
	{
		if (access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd, envp);
		*exit_status = ft_errors(126, cmd, NULL);
	}
	else if (path && *path && cmd[0] && ft_strncmp(cmd[0], "", 1))
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
	char	*str;

	(void)envp;
	all = ft_strjoin(path, "/");
	if (cmd[0][0] != '/')
		str = ft_strjoin(all, cmd[0]);
	else
		str = ft_strjoin(all, ft_strrchr(cmd[0], '/') + 1);
	free_var(all);
	if (access(str, F_OK) == 0)
	{
		if (access(str, X_OK) == 0)
		{
			free_var(str);
			exit(0);
		}
		free_split(cmd);
		*exit_status = ft_errors126(126, cmd, NULL);
	}
	free_var(str);
	str = NULL;
	return (1);
}

int	cmd_unexit(char **cmd, char **path, char **envp, int *exit_status)
{
	int	i;

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
