/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_ut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:48:41 by argharag          #+#    #+#             */
/*   Updated: 2025/06/17 19:06:14 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
int my_parse_ut(t_output **back, t_output **tmp, t_token **token, int *i, t_output **for_args)
{
if (!(*back))
	*tmp = create_out(NULL, NULL, NULL);
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
*i = 0;
return (1);
}
return (0);
}