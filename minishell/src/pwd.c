/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:34:51 by argharag          #+#    #+#             */
/*   Updated: 2025/07/15 19:31:30 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_pwd(char **env)
{
	char	path[1024];
	char	*str;
	char	*str1;

	str = NULL;
	if (!getcwd(path, sizeof(path)))
	{
		str = get_my_env("PWD", env);
		str1 = ft_strdup(str);
		return (str1);
	}
	return (ft_strdup(path));
}

void	cd_utils_mod_ut(char **str1, char **str2, char **str, char *home)
{
	printf("cd: error retrieving current directory: getcwd: ");
	printf("cannot access parent directories: ");
	printf("No such file or directory\n");
	*str1 = ft_strjoin(home, "/");
	*str2 = ft_strjoin(*str1, str[1]);
}

int	foo(char *line, char c)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (line[i])
	{
		if (line[i] == c)
			start = !(start);
		if (start)
		{
			i++;
			continue ;
		}
		i++;
	}
	if (start)
		return (1);
	return (0);
}
