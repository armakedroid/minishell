/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:35:46 by argharag          #+#    #+#             */
/*   Updated: 2025/05/12 19:35:53 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_home(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME=", 5))
			return envp[i] + 5;
		i++;
	}
	return (NULL);
}

int	ft_cd(char **envp, char **back)
{
	char *home;

	printf("back = %s\n", back[1]);
	if (back[1])
		return (chdir(back[1]));
	else {
		home = get_home(envp);
		if (home)
			return (chdir(home));
	}
	return (1);
}
