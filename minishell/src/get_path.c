/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:40:06 by argharag          #+#    #+#             */
/*   Updated: 2025/07/14 18:21:36 by apetoyan         ###   ########.fr       */
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
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			e = ft_strlen(env[i] + 5);
			back = ft_calloc((e + 1) * sizeof(char), 1);
			e = 0;
			while (env[i][m])
			{
				back[e++] = env[i][m];
				m++;
			}
			return (back);
		}
		i++;
	}
	return (NULL);
}

char	*get_home(char **envp)
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
