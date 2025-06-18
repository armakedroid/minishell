#include "../includes/minishell.h"

int	tok_oper(char *line, int *i, t_token **token)
{
	if (line[*i] == '|')
		add_token(token, ft_strdup("|"), PIPE);
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_token(token, ft_strdup(">>"), APPEND);
		(*i)++;
	}
	else if (line[*i] == '>')
		add_token(token, ft_strdup(">"), OUT);
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_token(token, ft_strdup("<<"), HEREDOC);
		(*i)++;
	}
	else if (line[*i] == '<')
		add_token(token, ft_strdup("<"), IN);
	else
		return (0);
	(*i)++;
	return (1);
}

int	tok_quote(char *line, int *i, t_token **token)
{
	int	start;
	int	quote;
	int	sng_qut;

	start = *i;
	quote = 1;
	sng_qut = 0;
	while (line[*i] && !is_space(line[*i]) && !is_operator(line[*i]))
	{
		if (line[0] == '\'')
			sng_qut = 1;
		if (line[*i] == '\"' && quote && !sng_qut)
		{
			quote = 0;
			start = ++(*i);
		}
		else if (line[*i] == '\"' && !quote && !sng_qut)
		{
			quote = 2;
			(*i)++;
		}
		else
			(*i)++;
		if (line[*i] && line[*i + 1] && line[(*i)] == '\'' && !quote
			&& !sng_qut)
		{
			add_token(token, ft_strdup("'"), WORD);
			(*i)++;
			start = *i;
			while (line[*i] && line[*i] != '\'')
				(*i)++;
			add_token(token, ft_substr(line, start, *i - start), WORD);
			(*i)++;
			add_token(token, ft_strdup("'"), WORD);
			(*i)++;
			if (!line[*i] || line[*i] == '\"')
				return (1);
			continue ;
		}
	}
	if ((line[start] == '\"' && ((*i - start) == 1 || !(*i - start))))
		return (0);
	add_token(token, ft_substr(line, start, *i - start - !(quote % 2)), WORD);
	return (1);
}

t_token	*my_tok(char *line)
{
	int		i;
	int		start;
	t_token	*token;

	i = 0;
	start = 0;
	token = NULL;
	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		if (tok_oper(line, &i, &token))
			continue ;
		else if (tok_quote(line, &i, &token))
			continue ;
	}
	return (token);
}
