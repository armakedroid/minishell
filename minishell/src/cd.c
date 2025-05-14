/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:35:53 by argharag          #+#    #+#             */
/*   Updated: 2025/05/14 22:43:59 by apetoyan         ###   ########.fr       */
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
			return envp[i] + 5;
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

int	ft_cd(char **envp, char **back)
{
	char *home;

	if (back[1])
	{
		// nerqevi ifi mej kmtni en jamanak ete grenq "cd -", aysinqn het gna ira hin PATH-in
		if (back[1][0] == '-' && ft_strlen(back[1]) == 1)
			return (chdir(get_old_path(envp)));
		update_smth(envp, "OLDPWD=", ft_pwd(envp, back)); 	// env-i mej OLDPWD-in khavasercnenq ays pahi pwd-n, vorpeszi "-" nshani depqum karoxananq het gnal hin pwd-in
		chdir(back[1]); 									// kpoxenq pwd-n
		update_smth(envp, "PWD=", ft_pwd(envp, back)); 		// env-i mej PWD-in khavasercnenq ays pahi pwd-n
		return (0);
	}
	else
	{
		home = get_home(envp);
		if (home)
		{
			update_smth(envp, "OLDPWD=", ft_pwd(envp, back));
			chdir(home);
			update_smth(envp, "PWD=", ft_pwd(envp, back));
			return (0);
		}
	}
	return (1);
}
