/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_fun.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:15:46 by argharag          #+#    #+#             */
/*   Updated: 2025/07/15 18:49:26 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_var(void *var)
{
	if (var)
	{
		free(var);
		var = NULL;
	}
}

void	free_parse(t_parse *var)
{
	free(var);
	var = NULL;
}

void	free_ut(t_output *cmd, char **envp, char **path)
{
	free_cmd(cmd);
	free_split(envp);
	free_split(path);
}

int	cd_utils_mod(char **str, char *home, char **envp)
{
	char	*str1;
	char	*str2;

	str1 = NULL;
	str2 = NULL;
	if (str[1] && str[1][0] != '-' && str[1][0] != '~')
	{
		home = ft_pwd(envp);
		update_smth(envp, "OLDPWD=", home);
		free_var(home);
		if (chdir(str[1]) == -1)
			return (1);
		home = ft_pwd(envp);
		update_smth(envp, "PWD=", home);
		if (ft_strchr(home, '.') || !ft_strncmp(get_my_env("PWD", envp),
				get_my_env("OLDPWD", envp), ft_strlen(get_my_env("OLDPWD",
						envp)) + 1))
		{
			cd_utils_mod_ut(&str1, &str2, str, home);
			update_smth(envp, "PWD=", str2);
		}
		return (free_var(home), free_var(str1), free_var(str2), 0);
	}
	return (cd_utils(str, envp, home));
}

void	var_f(t_mini *var)
{
	if (var->cmd->args[0] && !(ft_strncmp((*var).cmd->args[0], "cd", 3)))
	{
		(*var).cd_result = ft_cd((*var).cmd->args, (*var).env);
		if ((*var).cd_result == 100)
			g_exit_status = ft_errors(100, (*var).cmd->args, NULL);
		else if ((*var).cd_result == 1)
			g_exit_status = ft_errors1(1, (*var).cmd->args, NULL);
	}
	else if (var->cmd->args[0] && !(ft_strncmp((*var).cmd->args[0], "export",
				7)))
		(*var).env = ft_export((*var).env, (*var).cmd->args);
	else if (var->cmd->args[0] && ft_strncmp((*var).cmd->args[0], "unset",
			6) == 0)
		(*var).env = ft_unset((*var).env, (*var).cmd->args);
	else
		main_ut(&(*var));
	dup2((*var).stdout1, STDOUT_FILENO);
	dup2((*var).stdin1, STDIN_FILENO);
	close((*var).stdout1);
	close((*var).stdin1);
	if ((*var).fd)
		close((*var).fd);
}
