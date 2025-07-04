/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:45:16 by argharag          #+#    #+#             */
/*   Updated: 2025/07/03 19:18:56 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	if (tokens)
	{
		while (tokens)
		{
			next = tokens->next;
			if (tokens->value)
				free(tokens->value);
			if (tokens)
				free(tokens);
			tokens = next;
		}
	}
}

void	free_split(char **back)
{
	int	i;

	if (!back)
		return ;
	i = 0;
	while (back[i])
	{
		free_var(back[i]);
		i++;
	}
	free(back);
}

void	free_cmd(t_output *cmd)
{
	// t_output	*next;

	// while (cmd)
	// {
		// next = cmd->next;
		if (cmd->args && cmd->args[0])
			free_split(cmd->args);
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		free(cmd);
		// cmd = next;
	// }
}

void	free_var(void *var)
{
	if (var)
		free(var);
}

void	free_parse(t_parse *var)
{
	free(var);
}
