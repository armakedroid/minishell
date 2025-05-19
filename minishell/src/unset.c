/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:36:18 by argharag          #+#    #+#             */
/*   Updated: 2025/05/12 19:36:21 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_unset(char **envp, char **back)
{
	int	i;
	int	j;
	// char *item;

	i = 0;
	if (have_a_var(envp, back) == -1)
	{
		printf("unset: %s: invalid parameter name\n", back[1]);
		return (envp);
	}
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		j--;
		if (ft_strncmp(back[1], envp[i], j) == 0)
		{
			while (envp[i + 1])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			envp[i] = NULL;
			return (envp);
		}
		i++;
	}
	return (envp);
}
