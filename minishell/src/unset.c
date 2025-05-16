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

void	ft_unset(char **envp, char **back)
{
	int	i;

	i = 0;
	printf("%s\n\n",back[1]);
	while (envp[i])
	{
		if (ft_strncmp(back[1], envp[i], ft_strlen(back[1])) == 0)
		{
			while (envp[i + 1])
			{
				printf("barev");
				envp[i] = envp[i + 1];
				i++;
			}
			envp[i] = NULL;
			return ;
		}
		i++;
	}
}
