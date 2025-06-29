/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:57:14 by argharag          #+#    #+#             */
/*   Updated: 2025/06/29 13:57:35 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int tok_sec(t_tok_quote *tok,t_token **token)
{
	(*tok).l = 0;
	if (ft_strlen((*tok).str) == 1)
	{
		add_token(token, ft_strdup("$"), WORD);
		return (1);
	}
	while ((*tok).str[(*tok).l] && (*tok).str[(*tok).l] != '$')
		(*tok).l++;
	if ((*tok).l)
		(*tok).all1 = ft_substr((*tok).str, 0, (*tok).l);
	else
	{
		while ((*tok).str[(*tok).l] && (*tok).str[(*tok).l + 1] && (*tok).str[(*tok).l + 1] == '$')
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

int tok_quote3(t_tok_quote *tok, char **env)
{
	while ((*tok).all[(*tok).quote][(*tok).l])
	{
		if ((*tok).all[(*tok).quote][(*tok).l] && (!ft_isalpha((*tok).all[(*tok).quote][(*tok).l])
				&& (*tok).all[(*tok).quote][(*tok).l] != '?' && (*tok).all[(*tok).quote][(*tok).l] != '_'))
			break ;
		(*tok).l++;
	}
	if (!(*tok).l)
		return (1);
	if (tok_for_dol_2(ft_substr((*tok).all[(*tok).quote], 0, (*tok).l), env))
		(*tok).all1_h = ft_strjoin((*tok).all1, tok_for_dol(ft_substr((*tok).all[(*tok).quote], 0,
						(*tok).l), env));
	else
		(*tok).all1_h = ft_strjoin((*tok).all1, " ");
	free((*tok).all1);
	(*tok).all1 = (*tok).all1_h;
	(*tok).j = (*tok).l;
	if (!(*tok).all1_h)
		return (1);
	while ((*tok).all[(*tok).quote][(*tok).l])
		(*tok).l++;
	if ((*tok).j != (*tok).l)
		(*tok).all1_h = ft_strjoin((*tok).all1, ft_substr((*tok).all[(*tok).quote], (*tok).j, (*tok).l - (*tok).j));
	(*tok).all1 = (*tok).all1_h;
	return (0);
}

int	tok_quote4(t_tok_quote *tok, t_token **token, char **env)
{
	if (ft_strchr((*tok).str, '$') && (*tok).quote && (*tok).sng_qut == 1)
	{
		if(tok_sec(&(*tok), token))
			return (1);
		while ((*tok).all[(*tok).quote])
		{
			tok_quote3(&(*tok), env);
			(*tok).quote++;
		}
		add_token(token, (*tok).all1, WORD);
		if ((*tok).str)
		{
			free((*tok).str);
			(*tok).str = NULL;
		}
		if ((*tok).all)
		{
			free_split((*tok).all);
			(*tok).all = NULL;
		}
	}
	else
		add_token(token, (*tok).str, WORD);
	return(0);
}

int tok_quote5(t_tok_quote *tok, t_token **token, char *line, int **i)
{
	while ((line[*(*i)] && !is_space(line[*(*i)]) && !is_operator(line[*(*i)]))
	|| ((*tok).quote == 0 || (*tok).sng_qut == 0))
	{
	tok_first((*i), line, &(*tok));
	if (line[*(*i)] && line[*(*i) + 1] && line[*(*i)] == '\'' && 
		!(*tok).quote && !(*tok).sng_qut)
	{
		add_token(token, ft_strdup("'"), WORD);
		(*(*i))++;
		(*tok).start = *(*i);
		while (line[*(*i)] && line[*(*i)] != '\'')
			(*(*i))++;
		add_token(token, ft_substr(line, (*tok).start, *(*i) - (*tok).start), WORD);
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
	t_tok_quote tok;

	tok.start = *i;
	tok.quote = 1;
	tok.sng_qut = 1;
	tok.all = NULL;
	if(tok_quote5(&tok, token, line, &i))
		return (0);
	if ((line[tok.start] == '\"' && ((*i - tok.start) == 1 || !(*i - tok.start))))
		return (0);
	tok.str = ft_substr(line, tok.start, *i - tok.start - !(tok.quote % 2));
	if (tok.sng_qut == 2)
	{
		tok.all2 = ft_strtrim(tok.str, "'");
		free(tok.str);
		tok.str = tok.all2;
	}
	if(tok_quote4(&tok, token, env))
		return (0);
	return (1);
}
