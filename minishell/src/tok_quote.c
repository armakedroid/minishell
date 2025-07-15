/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:57:14 by argharag          #+#    #+#             */
/*   Updated: 2025/07/15 19:51:53 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tok_sec(t_tok_quote *tok, t_token **token)
{
	(*tok).l = 0;
	if (tok_sec_ut(tok, token))
		return (1);
	while ((*tok).str[(*tok).l] && (*tok).str[(*tok).l] != '$')
		(*tok).l++;
	if ((*tok).l)
		(*tok).all1 = ft_substr((*tok).str, 0, (*tok).l);
	else
	{
		while ((*tok).str[(*tok).l] && (*tok).str[(*tok).l + 1]
			&& (*tok).str[(*tok).l + 1] == '$')
			(*tok).l++;
		(*tok).all1 = NULL;
	}
	if ((*tok).str && ft_strlen((*tok).str + (*tok).l) == 1)
		return (1);
	(*tok).all = ft_split((*tok).str + (*tok).l - !(!((*tok).l)), '$');
	if ((*tok).str[0] == '$')
		(*tok).quote = 0;
	else
		(*tok).quote = 1;
	(*tok).l = 0;
	return (0);
}

int	tok_quote4(t_tok_quote *tok, t_token **token, char **env)
{
	int	k;

	if (ft_strchr((*tok).str, '$') && (*tok).quote && (*tok).sng_qut == 1)
	{
		k = 0;
		if (tok_sec(&(*tok), token))
			return (1);
		while (((*tok).all)[(*tok).quote])
		{
			if (tok_quote3(&(*tok), env) == 1)
			{
				k = 1;
				break ;
			}
			tok->l = 0;
			(*tok).quote++;
		}
		if (!k)
			add_token(token, (*tok).all1, WORD);
		tok4_ut(tok);
	}
	else
		add_token(token, (*tok).str, WORD);
	return (0);
}

int	tok_quote5(t_tok_quote *tok, t_token **token, char *line, int **i)
{
	while ((line[*(*i)] && !is_space(line[*(*i)]) && !is_operator(line[*(*i)]))
		|| ((*tok).quote == 0 || (*tok).sng_qut == 0))
	{
		tok_first((*i), line, &(*tok));
		if (line[*(*i)] && line[*(*i) + 1] && line[*(*i)] == '\''
			&& !(*tok).quote && !(*tok).sng_qut)
		{
			add_token(token, ft_strdup("'"), WORD);
			(*(*i))++;
			(*tok).start = *(*i);
			while (line[*(*i)] && line[*(*i)] != '\'')
				(*(*i))++;
			add_token(token, B(line, (*tok).start, *(*i) - (*tok).start), WORD);
			(*(*i))++;
			add_token(token, ft_strdup("'"), WORD);
			(*(*i))++;
			if (!line[*(*i)] || line[*(*i)] == '\"')
				return (1);
			continue ;
		}
	}
	return (0);
}

int	tok_quote(char *line, int *i, t_token **token, char **env)
{
	t_tok_quote	tok;

	tok.start = *i;
	tok.quote = 1;
	tok.sng_qut = 1;
	tok.all = NULL;
	if (tok_quote5(&tok, token, line, &i))
		return (0);
	if ((line[tok.start] == '\"' && ((*i - tok.start) == 1 || !(*i
					- tok.start))))
		return (0);
	tok.str = ft_substr(line, tok.start, *i - tok.start - !(tok.quote % 2));
	if (tok.sng_qut == 2)
	{
		tok.all2 = ft_strtrim(tok.str, "'");
		free_var(tok.str);
		tok.str = tok.all2;
	}
	if (tok_quote4(&tok, token, env))
	{
		free_var(tok.str);
		return (0);
	}
	return (1);
}
