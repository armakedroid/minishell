/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:35:53 by argharag          #+#    #+#             */
/*   Updated: 2025/06/30 20:09:06 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_old_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD=", 7))
			return (ft_strdup(envp[i] + 7));
		i++;
	}
	return (NULL);
}

int	cd_minus_utils(char *home, char **envp)
{
	char *str;

	str = ft_pwd();
	if (home)
	{
		update_smth(envp, "OLDPWD=", str);
		printf("%s\n", home);
		if (chdir(home) == -1)
		{
			free(str);
			return (1);
		}
		free(home);
		update_smth(envp, "PWD=", str);
	}
	if (str)
		free(str);
	return (0);
}

int	cd_utils(char **str, char **envp, char *home)
{
	char *str1;

	str1 = NULL;
	if (str[2])
	return (100);
	if (str[1][0] == '-' && ft_strlen(str[1]) == 1)
	{
		home = get_old_path(envp);
		if (cd_minus_utils(home, envp))
		return (1);
		else
		return (0);
	}
	str1 = ft_pwd();
	update_smth(envp, "OLDPWD=", str1);
	if (str[1][0] == '~')
		if (home)
			if (chdir(home) == -1 || chdir(str[1] + 2) == -1)
			{
				free(str1);
				return (1);
			}
	if (str1)
		free(str1);
	return (0);
}

int	ft_cd_utils(char *home, char **envp)
{
	char	*str;

	str = ft_pwd();
	if (home)
	{
		update_smth(envp, "OLDPWD=", str);
		if (chdir(home) == -1)
		{
			free(str);
			return (1);
		}
		update_smth(envp, "PWD=", str);
	}
	if (str)
		free(str);
	return (0);
}

int	ft_cd(char **str, char **envp)
{
	char	*home;

	home = get_home(envp);
	if (!str[1] || (str[1][0] == '~' && !str[1][1]))
	{
		if (ft_cd_utils(home, envp))
			return (1);
		return (0);
	}
	else if (str[1])
	{
		if (str[1] && str[1][0] != '-' && str[1][0] != '~')
		{
			home = ft_pwd();
			update_smth(envp, "OLDPWD=", home);
			free(home);
			if (chdir(str[1]) == -1)
				return (1);
			home = ft_pwd();
			update_smth(envp, "PWD=", home);
			free(home);
			return (0);
		}
		return (cd_utils(str, envp, home));
	}
	return (1);
}
