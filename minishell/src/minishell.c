/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:48:13 by argharag          #+#    #+#             */
/*   Updated: 2025/06/23 21:20:17 by apetoyan         ###   ########.fr       */
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
	new = malloc(sizeof(t_output));
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

t_output	*parse(t_token *token)
{
	t_parse	parse;

	parse.back = NULL;
	parse.tmp = NULL;
	parse.i = 0;
	while (token)
	{
		if (!token)
			return (parse.back);
		if (!parse_heredoc(&token))
			return (NULL);
		if (!token)
			return (parse.back);
		if (my_parse_ut(&parse.back, &parse.tmp, &token, &parse.for_args) == 1)
		{
			parse.i = 0;
			continue ;
		}
		if (parse_wrd(&token, &parse.tmp, &parse.i) == 1)
		{
			parse.i = 1;
			return (NULL);
		}
		token = token->next;
		cmdfun(&parse.back, parse.tmp);
	}
	return (parse.back);
}

int	exit_var(t_mini *var)
{
	char	**str;
	ssize_t	k;

	k = 0;
	if (ft_strlen(var->line) > 4)
		if (var->line[4] != ' ')
			return (0);
	printf("exit\n");
	str = ft_split(var->line, ' ');
	if (!str)
		return (1);
	if (str && !str[1])
	{
		free_split(str);
		return (1);
	}
	if (!ft_strncmp(str[1], "$?", 2))
	{
		free_split(str);
		return (1);
	}
	while (str[1][k])
	{
		if (ft_isdigit(str[1][k]) || str[1][k] == '-' || str[1][k] == '+')
			k++;
		else
			break ;
	}
	if (!ft_isdigit(ft_atoi(str[1]))
		&& (ssize_t)(ft_strlen(str[1])) == k)
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
	g_exit_status = ft_errors(2, &str[1], str[0]);
	free_split(str);
	return (1);
}
