/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:36:26 by argharag          #+#    #+#             */
/*   Updated: 2025/05/12 19:36:30 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n",envp[i]);
		i++;
	}
}
