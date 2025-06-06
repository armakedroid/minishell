/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:35:53 by argharag          #+#    #+#             */
/*   Updated: 2025/06/06 18:07:15 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_home(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_old_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD=", 7))
			return (envp[i] + 7);
		i++;
	}
	return (NULL);
}

int	cd_utils(char **str, char **envp, char *home)
{
	if (str[2])
		return (100);
	if (str[1][0] == '-' && ft_strlen(str[1]) == 1)
	{
		home = get_old_path(envp);
		if (home)
		{
			update_smth(envp, "OLDPWD=", ft_pwd(envp));
			printf("%s\n", home);
			if (chdir(home) == -1)
				return (1);
			update_smth(envp, "PWD=", ft_pwd(envp));
			return (0);
		}
	}
	update_smth(envp, "OLDPWD=", ft_pwd(envp));
	if (str[1][0] == '~')
	{
		if (home)
		{
			if (chdir(home) == -1)
				return (1);
			if (chdir(str[1] + 2) == -1)
				return (1);
		}
	}
	return (0);
}

int	ft_cd(char **str, char **envp)
{
	char	*home;

	home = get_home(envp);
	if (!str[1] || (str[1][0] == '~' && !str[1][1]))
	{
		if (home)
		{
			update_smth(envp, "OLDPWD=", ft_pwd(envp));
			if (chdir(home) == -1)
				return (1);
			update_smth(envp, "PWD=", ft_pwd(envp));
			return (0);
		}
	}
	else if (str[1])
	{
		if (str[1] && str[1][0] != '-' && str[1][0] != '~')
		{
			update_smth(envp, "OLDPWD=", ft_pwd(envp));
			if (chdir(str[1]) == -1)
				return (1);
			update_smth(envp, "PWD=", ft_pwd(envp));
			return (0);
		}
		return(cd_utils(str, envp, home));
	}
	return (1);
}
