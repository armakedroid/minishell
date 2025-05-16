/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:36:13 by argharag          #+#    #+#             */
/*   Updated: 2025/05/14 22:42:23 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Update_smth funkcian katarum e popoxutyun envp-i mej
// Yndunum e 3 arjeq` 
// 1. envp, 
// 2. var (tesqy partadir ayspes "PATH=", "PWD="), 
// 3. value (inch petq e lini)
void update_smth(char **envp, char *var, char *value)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		if (!ft_strncmp(envp[i], var, ft_strlen(var)))
			break;
		i++;
	}
	if (envp[i])
	{
		if (value)
			envp[i] = ft_strjoin(var, value);
		else
			envp[i] = NULL;

	}
}

char **ft_export(char **envp, char **back)
{
	int	i;
	char *tmp;
	char **env;

	i = 0;
	if (have_a_var(envp, back))
	{
		// If-i mej mtnum e en jamanak ete envp-i mej ka arden ayd popoxakany
		while (back[1][i] && back[1][i] != '=')
			i++;
		if (back[1][i])
		{
			tmp = ft_substr(back[1], 0, i);
			update_smth(envp, tmp, back[1] + i);
			free(tmp);
		}
		return (envp);
	}
	i = 0;
	while (envp[i])
		i++;
	env = malloc((i + 1) * sizeof(char *));
	i = 0;
	while(envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = ft_strdup(back[1]);
	env[i + 1] = NULL;
	return (env);
}