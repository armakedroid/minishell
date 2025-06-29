/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:06:03 by argharag          #+#    #+#             */
/*   Updated: 2025/06/29 13:06:14 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc_u(char **line, char ***back)
{
	*back = ft_split(*line, '\n');
	if (!*back || !**back)
		return ;
}

char **export_without_arg(char **envp)
{
	char **cp;

	cp = ft_copy_env(envp);
	sort(cp);
	print_env(cp);
	free_split(cp);
	return (envp);
}

int exit_return(char **str)
{
	g_exit_status = ft_errors(2, &str[1], str[0]);
	free_split(str);
	return (1);
}

int exit_var_ut(t_mini *var, char ***str, ssize_t *k)
{
	if (ft_strlen(var->line) > 4)
	if (var->line[4] != ' ')
		return (2);
printf("exit\n");
(*str) = ft_split(var->line, ' ');
if (!(*str))
	return (1);
if (((*str) && !(*str)[1]) || !ft_strncmp((*str)[1], "$?", 2))
{
	free_split((*str));
	return (1);
}
while ((*str)[1][(*k)])
{
	if (ft_isdigit((*str)[1][(*k)]) || 
		(*str)[1][(*k)] == '-' || (*str)[1][(*k)] == '+')
		(*k)++;
	else
		break ;
}
return (0);
}

void	tok_first(int *i, char *line, t_tok_quote *tok)
{
	if (line[*i] == '\"' && (*tok).quote)
	{
		(*tok).quote = 0;
		(*tok).start = ++(*i);
	}
	else if (line[*i] == '\'' && (*tok).sng_qut)
	{
		(*tok).sng_qut = 0;
		(*tok).start = ++(*i);
	}
	else if (line[*i] == '\"' && !(*tok).quote)
	{
		(*tok).quote = 2;
		(*i)++;
	}
	else if (line[*i] == '\'' && !(*tok).sng_qut)
	{
		(*tok).sng_qut = 2;
		(*i)++;
	}
	else
		(*i)++;
}
