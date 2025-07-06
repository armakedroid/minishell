/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:57:14 by argharag          #+#    #+#             */
/*   Updated: 2025/07/06 19:01:18 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tok_sec(t_tok_quote *tok, t_token **token)
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

int	tok_quote3(t_tok_quote *tok, char **env)
{
	char	*str_sub;
	char	*str_dol;
	char	*str_for_dol;

	str_sub = NULL;
	if (!(tok->all1))
		str_dol = ft_calloc(1, 1);
	else
		str_dol = ft_strdup(tok->all1);
	while ((tok->all)[tok->quote][tok->l])
	{
		if ((tok->all)[tok->quote][tok->l]
			&& (!ft_isalpha((tok->all)[tok->quote][tok->l])
				&& (tok->all)[tok->quote][tok->l] != '?'
				&& (tok->all)[tok->quote][tok->l] != '_'))
			break ;
		(tok->l)++;
	}
	if (!tok->l)
	{
		free_var(str_dol);
		return (1);
	}
	str_sub = B((tok->all)[tok->quote], 0, tok->l);
	if (D(str_sub, env))
	{
		free_var(str_sub);
		str_sub = B((tok->all)[tok->quote], 0, tok->l);
		str_for_dol = A(str_sub, env);
		tok->all1_h = C(str_dol, str_for_dol);
		free_var(str_sub);
		free_var(str_for_dol);
		str_sub = NULL;
	}
	else
		tok->all1_h = ft_strdup("");
	free_var(tok->all1);
	tok->all1 = tok->all1_h;
	tok->j = tok->l;
	if (!tok->all1_h || !*(tok->all1_h))
	{
		free_var(str_dol);
		free_var(str_sub);
		return (2);
	}
	while (tok->all[tok->quote][tok->l])
		tok->l++;
	if (tok->j != tok->l)
	{
		str_sub = B((tok->all)[tok->quote], tok->j, tok->l - tok->j);
		str_for_dol = tok->all1;
		tok->all1_h = C(str_for_dol, str_sub);
		free_var(str_for_dol);
	}
	free_var(str_dol);
	free_var(str_sub);
	tok->all1 = tok->all1_h;
	return (0);
}

int	tok_quote4(t_tok_quote *tok, t_token **token, char **env)
{
	if (ft_strchr((*tok).str, '$') && (*tok).quote && (*tok).sng_qut == 1)
	{
		int	k;

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
		print_token(*token);
		free_var(tok.str);
		return (0);
	}
	return (1);
}
