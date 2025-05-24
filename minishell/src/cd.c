/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:35:53 by argharag          #+#    #+#             */
/*   Updated: 2025/05/20 19:23:16 by argharag         ###   ########.fr       */
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

int	ft_cd(t_token *token, char **envp)
{
	char *home;
	t_token *tmp;

	tmp = token->next;
	if (tmp)
	{
		if (tmp->next)
			return (100);
		if (tmp->value[0] == '-' && ft_strlen(tmp->value) == 1)
			return (chdir(get_old_path(envp)));
		update_smth(envp, "OLDPWD=", ft_pwd(envp)); 	// env-i mej OLDPWD-in khavasercnenq ays pahi pwd-n, vorpeszi "-" nshani depqum karoxananq het gnal hin pwd-in
		if (chdir(tmp->value) == -1)
			return (1);								    // kpoxenq pwd-n
		update_smth(envp, "PWD=", ft_pwd(envp)); 		// env-i mej PWD-in khavasercnenq ays pahi pwd-n
		return (0);
	}
	else
	{
		home = get_home(envp);
		if (home)
		{
			update_smth(envp, "OLDPWD=", ft_pwd(envp));
			if (chdir(home) == -1)
				return (1);
			update_smth(envp, "PWD=", ft_pwd(envp));
			return (0);
		}
	}
	return (1);
}
