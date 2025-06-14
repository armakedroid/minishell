/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:35:22 by argharag          #+#    #+#             */
/*   Updated: 2025/06/14 21:29:58 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mykey(char *env, char *key)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (ft_strncmp(env, key, i) == 0 && (int)ft_strlen(key) == i);
}

char	**ft_unset(char **envp, char **back)
{
	int	i;

	i = 0;
	if (have_a_var(envp, back) == -1)
	{
		printf("unset: %s: invalid parameter name\n", back[1]);
		return (envp);
	}
	while (envp[i])
	{
		if (mykey(envp[i], back[1]))
		{
			while (envp[i + 1])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			envp[i] = NULL;
			break;
		}
		i++;
	}
	return (envp);
}
