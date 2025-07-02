/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_tok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:21:47 by argharag          #+#    #+#             */
/*   Updated: 2025/07/02 20:10:38 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tok_oper(char *line, int *i, t_token **token)
{
	if (line[*i] == '|')
		add_token(token, ft_strdup("|"), PIPE);
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_token(token, ft_strdup(">>"), APPEND);
		(*i)++;
	}
	else if (line[*i] == '>')
		add_token(token, ft_strdup(">"), OUT);
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_token(token, ft_strdup("<<"), HEREDOC);
		(*i)++;
	}
	else if (line[*i] == '<')
		add_token(token, ft_strdup("<"), IN);
	else
		return (0);
	(*i)++;
	return (1);
}

int	tok_for_dol_2(char *str, char **env)
{
	if (str[0] == '?' && !str[1])
		return (1);
	else if (get_my_env(str, env))
		return (1);
	return (0);
}

char	*tok_for_dol(char *str, char **env)
{
	char	*str1;

	if (str[0] == '?' && !str[1])
		return (ft_itoa(g_exit_status));
	else
	{
		str1 = get_my_env(str, env);
		if (str1)
			return (str1);
	}
	return (NULL);
}

t_token	*my_tok(char *line, char **env)
{
	int		i;
	int		start;
	t_token	*token;

	i = 0;
	start = 0;
	token = NULL;
	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		if (tok_oper(line, &i, &token))
			continue ;
		else if (tok_quote(line, &i, &token, env))
			continue ;
	}
	return (token);
}
