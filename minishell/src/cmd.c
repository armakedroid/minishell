/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:15:08 by argharag          #+#    #+#             */
/*   Updated: 2025/06/05 19:31:26 by argharag         ###   ########.fr       */
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
		
		printf("es cmd_uti mej em\n");
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
	return (ft_errors(127, cmd, NULL));
}
