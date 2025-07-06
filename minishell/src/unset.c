/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:35:22 by argharag          #+#    #+#             */
/*   Updated: 2025/06/30 20:23:24 by apetoyan         ###   ########.fr       */
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
	int		i;
	int		j;

	if (!back || !back[1])
		return (envp);
	if (have_a_var(envp, back) == -1)
		return (envp);

	i = 0;
	while (envp[i])
	{
		if (mykey(envp[i], back[1]))
		{
			free(envp[i]);
			j = i;
			while (envp[j + 1])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			envp[j] = NULL;
			break ;
		}
		i++;
	}
	return (envp);
}
