/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_ut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:48:41 by argharag          #+#    #+#             */
/*   Updated: 2025/07/02 19:32:26 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_wrd(t_token **token, t_output **tmp, int *i)
{
	char	*str;

	str = NULL;
	if ((*token)->type == WORD)
	{
		(*tmp)->args[*i] = ft_strdup((*token)->value);
		(*i)++;
	}
	else if ((*token)->next)
		parse_ut(&(*tmp), &(*token));
	else
	{
		str = "newline";
		g_exit_status = ft_errors(2, &str, NULL);
		return (1);
	}
	return (0);
}

void	parse_ut(t_output **tmp, t_token **token)
{
	if ((*token)->type == IN)
	{
		*token = (*token)->next;
		(*tmp)->infile = ft_strdup((*token)->value);
	}
	else if ((*token)->type == OUT)
	{
		*token = (*token)->next;
		(*tmp)->outfile = ft_strdup((*token)->value);
	}
	else if ((*token)->type == APPEND)
	{
		*token = (*token)->next;
		(*tmp)->outfile = ft_strdup((*token)->value);
		(*tmp)->num = 1;
	}
}

int	my_parse_ut(t_output **back, t_output **tmp, t_token **token, t_output **for_args)
{
	if (!(*back))
	{
		if ((*token)->next && (*token)->next->type == 5)
			*tmp = create_out(NULL, ft_strdup(TMP), NULL);
		else
			*tmp = create_out(NULL, NULL, NULL);
	}
	else
	{
		(*for_args) = (*back);
		while ((*for_args)->next)
			(*for_args) = (*for_args)->next;
		if (!((*for_args)->is_p))
			*tmp = create_out((*for_args)->args, (*for_args)->infile,
					(*for_args)->outfile);
		else
			*tmp = create_out(NULL, NULL, NULL);
	}
	if ((*token)->type == PIPE)
	{
		(*tmp)->is_p = 1;
		(*token) = (*token)->next;
		cmdfun(&(*back), *tmp);
		return (1);
	}
	return (0);
}

int	parse_heredoc(t_token **token)
{
	char	*str;

	str = NULL;
	if ((*token)->type == HEREDOC && (*token)->next)
	{
		if ((*token) && (*token)->next)
			(*token) = (*token)->next->next;
		else if ((*token) && !(*token)->next)
		{
			str = "newline";
			g_exit_status = ft_errors(2, &str, NULL);
			return (0);
		}
	}
	return (1);
}
