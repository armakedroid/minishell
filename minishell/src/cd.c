/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:35:53 by argharag          #+#    #+#             */
/*   Updated: 2025/05/27 19:03:12 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// get_home funkcian vorpeszi ete cd-i dimac path chlini inqy gna HOME
char *get_home(char **envp)
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

// get_old_path funkcian vorpeszi ete cd-i dimac lini "-" nshany inqy gna hin PATH-in
char *get_old_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD=", 7))
			return envp[i] + 7;
		i++;
	}
	return (NULL);
}

int	ft_cd(char **str, char **envp)
{
	char *home;

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
		if (str[2])
			return (100);
		if (str[1][0] == '-' && ft_strlen(str[1]) == 1)
			return (chdir(get_old_path(envp)));
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
		else if (chdir(str[1]) == -1)
			return (1);
		update_smth(envp, "PWD=", ft_pwd(envp));
		return (0);
	}
	return (1);
}
