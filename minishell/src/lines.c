/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:20:11 by argharag          #+#    #+#             */
/*   Updated: 2025/07/14 18:25:08 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_pipe_while(t_pipes *m_p)
{
	while (m_p->a < m_p->cmd_nbr)
	{
		if (m_p->str)
			m_p->str = m_p->str->next;
		while (m_p->str && m_p->str->next && !(m_p->str->is_p))
			m_p->str = m_p->str->next;
		m_p->in_fd = waitpid((m_p->pid)[m_p->a], &m_p->errors, 0);
		if (m_p->errors)
			m_p->errors1 = WEXITSTATUS(m_p->errors);
		if (m_p->errors1)
		{
			ft_errors(m_p->errors1, m_p->str->args, NULL);
			m_p->errors1 = 0;
		}
		m_p->a++;
	}
}

void	tok4_ut(t_tok_quote *tok)
{
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

int	tok_sec_ut(t_tok_quote *tok, t_token **token)
{
	if (ft_strlen((*tok).str) == 1)
	{
		add_token(token, ft_strdup("$"), WORD);
		return (1);
	}
	return (0);
}
