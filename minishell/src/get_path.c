/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:40:06 by argharag          #+#    #+#             */
/*   Updated: 2025/06/05 18:41:02 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char **env)
{
	char	*back;
	int		i;
	int		e;
	int		m;

	e = 0;
	m = 5;
	i = 0;
	while (env[i++])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			e = ft_strlen(env[i] + 5);
			back = malloc((e + 1) * sizeof(char));
			e = 0;
			while (env[i][m])
			{
				back[e++] = env[i][m];
				m++;
			}
			return (back);
		}
	}
	return (NULL);
}
