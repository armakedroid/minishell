/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:43:30 by apetoyan          #+#    #+#             */
/*   Updated: 2025/05/28 21:00:12 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	have_a_var(char **envp, char **back)
{
	int	i;
	int	j;

	i = 0;
	while (back[1][i])
	{
		if (back[1][i] == '=')
			break ;
		i++;
	}
	if (back[1][i] == '=' && !ft_strncmp(back[0], "unset", 5))
		return (-1);
	j = 0;
	while (envp[j])
	{
		if (!ft_strncmp(envp[j], back[1], i))
			return (1);
		j++;
	}
	return (0);
}
