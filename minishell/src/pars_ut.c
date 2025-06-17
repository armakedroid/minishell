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
