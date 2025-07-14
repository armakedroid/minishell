/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:33:05 by argharag          #+#    #+#             */
/*   Updated: 2025/07/14 18:23:00 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tok_quote3_more(char **str_dol, char **str_sub, t_tok_quote *tok)
{
	if (!(tok->all1))
		*str_dol = ft_calloc(1, 1);
	else
		*str_dol = ft_strdup(tok->all1);
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
		free_var(*str_dol);
		return (1);
	}
	*str_sub = B((tok->all)[tok->quote], 0, tok->l);
	return (0);
}

int	tok_quote3_ut(t_tok_quote *tok, char **str_for_dol, char **str_dol,
		char **str_sub)
{
	free_var(tok->all1);
	tok->all1 = tok->all1_h;
	tok->j = tok->l;
	if (!tok->all1_h || !*(tok->all1_h))
	{
		free_var(*str_dol);
		free_var(*str_sub);
		return (2);
	}
	while (tok->all[tok->quote][tok->l])
		tok->l++;
	if (tok->j != tok->l)
	{
		*str_sub = B((tok->all)[tok->quote], tok->j, tok->l - tok->j);
		*str_for_dol = tok->all1;
		tok->all1_h = C(*str_for_dol, *str_sub);
		free_var(*str_for_dol);
	}
	free_var(*str_dol);
	free_var(*str_sub);
	tok->all1 = tok->all1_h;
	return (0);
}

int	tok_quote3(t_tok_quote *tok, char **env)
{
	char	*str_sub;
	char	*str_dol;
	char	*str_for_dol;

	str_dol = NULL;
	str_for_dol = NULL;
	str_sub = NULL;
	if (tok_quote3_more(&str_dol, &str_sub, tok))
	{
		return (1);
	}
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
	return (tok_quote3_ut(tok, &str_for_dol, &str_dol, &str_sub));
}
