/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:02:47 by argharag          #+#    #+#             */
/*   Updated: 2025/06/30 19:09:32 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_my_env(char *str, char **env)
{
	int		i;
	char	*all;

	all = ft_strjoin(str, "=");
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(all, env[i], ft_strlen(all)))
			break ;
		i++;
	}
	if (!env[i])
		return (free(all), NULL);
	free(all);
	return (env[i] + ft_strlen(str) + 1);
}

void	echo_utils(char **back, int j, int i, char **argv)
{
	char	*str;

	str = NULL;
	if (back[j][0] == '\'' || back[j][ft_strlen(back[j]) - 1] == '\'')
	{
		if (ft_strlen(back[j]) != 1)
			str = ft_strtrim(back[j], "'");
		else
			str = ft_strdup("'");
		free(back[j]);
		back[j] = str;
		printf("%s", back[j]);
	}
	else
	{
		if (back[j] && back)
			printf("%s", back[j]);
		else
			write(1, "\n", 1);
	}
	if ((back[j + 1]) || back[j][0] != '\'')
		if ((argv[i + 1] && argv[i + 1][0] != '\'') || (back[j + 1]
				&& back[j + 1][0] != '\''))
			printf(" ");
}

int	ft_echo(char **argv, int signal, char **env)
{
	int		i;
	int		j;
	int		n;
	char	*str;
	char	**back;

	n = 0;
	i = 1;
	if (argv[1] && ft_strncmp(argv[1], "-n", 3) == 0)
		n = ++i - 1;
	while (argv[i])
	{
		back = ft_split(argv[i], ' ');
		j = -1;
		while (back[++j])
			echo_utils(back, j, i, argv);
		free_split(back);
		back = NULL;
		i++;
	}
	if (n != 1)
		printf("\n");
	return (0);
}
