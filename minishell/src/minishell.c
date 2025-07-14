/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:48:13 by argharag          #+#    #+#             */
/*   Updated: 2025/07/14 18:21:51 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

void	handle_sigint(int sl)
{
	(void)sl;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	cmdfun(t_output **lst, t_output *new)
{
	t_output	*back;

	back = NULL;
	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	back = *lst;
	while (back->next)
		back = back->next;
	back->next = new;
}

t_output	*create_out(char **str, char *infile, char *outfile)
{
	t_output	*new;
	int			i;

	i = 0;
	new = ft_calloc(sizeof(t_output), 1);
	new->infile = infile;
	new->outfile = outfile;
	new->is_p = 0;
	new->num = 0;
	if (str)
		while (str[i])
			i++;
	new->args = ft_calloc((i + 1), sizeof(char *));
	i = -1;
	if (str)
	{
		while (str[++i])
			new->args[i] = ft_strdup(str[i]);
	}
	if (str && !infile && !outfile)
		new->args[i] = NULL;
	new->next = NULL;
	return (new);
}

t_parse	*parse(t_token *token)
{
	t_parse	*parse;

	parse = ft_calloc(1, sizeof(t_parse));
	while (token)
	{
		if (!parse_heredoc(&token))
			return (NULL);
		if (!token)
			return (parse);
		if (my_parse_ut(&(parse->back), &(parse->tmp), &token,
				&(parse->for_args)) == 1)
		{
			parse->i = 0;
			continue ;
		}
		if (parse_wrd(&token, &(parse->tmp), &(parse->i)) == 1)
		{
			parse->i = 1;
			return (NULL);
		}
		token = token->next;
		cmdfun(&(parse->back), parse->tmp);
	}
	return (parse);
}

int	exit_var(t_mini *var)
{
	char	**str;
	ssize_t	k;
	int		i;

	str = NULL;
	k = 0;
	i = exit_var_ut(var, &str, &k);
	if (i == 2)
		return (0);
	else if (i == 1)
		return (1);
	if (!ft_isdigit(ft_atoi(str[1])) && (ssize_t)(ft_strlen(str[1])) == k)
	{
		if (str[2])
		{
			g_exit_status = ft_errors(100, str, NULL);
			free_split(str);
			return (0);
		}
		g_exit_status = ft_atoi(str[1]);
		free_split(str);
		return (1);
	}
	return (exit_return(str));
}
