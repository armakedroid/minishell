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
	int	start = *i;
	int	quote = 0;

	while (line[*i] && !is_space(line[*i]) && !is_operator(line[*i]))
	{
		if (line[*i] == '\"' && !quote)
			quote = 1, start = ++(*i);
		else if (line[*i] == '\"' && quote)
			quote = 0, (*i)++;
		else
			(*i)++;
	}
	if ((line[start] == '\"' && (*i - start) == 1) || !(*i - start))
		return (0);
	add_token(token, ft_substr(line, start, *i - start), WORD);
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
			continue;
		if (tok_quote(line, &i, &token))
			continue;
	}
	return (token);
}
