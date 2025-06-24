/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:36:13 by argharag          #+#    #+#             */
/*   Updated: 2025/06/24 21:48:38 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_smth(char **envp, char *var, char *value)
{
	int		i;
	char	*new;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, ft_strlen(var)))
			break ;
		i++;
	}
	if (envp[i])
	{
		free(envp[i]);
		if (value)
		{
			new = ft_strjoin(var, value);
			envp[i] = new;
		}
		else
			envp[i] = NULL;
	}
}

void	sort(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[j + 1])
		{
			if (ft_strncmp(envp[j], envp[j + 1], 100000) > 0)
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][ft_strlen(envp[i]) - 1] == '=')
			printf("declare -x %s''\n", envp[i]);
		else
			printf("declare -x %s\n", envp[i]);
		i++;
	}
}

char	**helper_ex(char **envp, char **back)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i])
		i++;
	env = malloc((i + 2) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = ft_strdup(back[1]);
	env[i + 1] = NULL;
	free_split(envp);
	return (env);
}

char	**ft_export(char **envp, char **back)
{
	int		i;
	char	*tmp;
	char	**cp;

	i = 0;
	if (!back[1])
	{
		cp = ft_copy_env(envp);
		sort(cp);
		print_env(cp);
		free_split(cp);
		return (envp);
	}
	else if (have_a_var(envp, back))
	{
		while (back[1][i] && back[1][i] != '=')
			i++;
		if (back[1][i])
		{
			tmp = ft_substr(back[1], 0, i);
			update_smth(envp, tmp, back[1] + i);
			free(tmp);
		}
		return (envp);
	}
	return (helper_ex(envp, back));
}
