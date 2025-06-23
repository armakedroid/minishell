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

void	tok_for_dol(char *str, t_token **token, char **env)
{
	if (str[1] == '?' && !str[2])
		add_token(token, ft_itoa(g_exit_status), WORD);
	else if (get_my_env(str + 1, env))
		add_token(token, ft_strdup(get_my_env(str + 1, env)), WORD);
}

int	tok_quote(char *line, int *i, t_token **token, char **env)
{
	int		start;
	int		quote;
	int		sng_qut;
	int		count;
	char	*str;

	start = *i;
	quote = 1;
	sng_qut = 0;
	count = 0;
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
	str = ft_substr(line, start, *i - start - !(quote % 2));
	if (!ft_strncmp(str, "$", 1))
	{
		quote = 1;
		sng_qut = 0;
		while (str[sng_qut])
		{
			if (str[sng_qut] == '$')
				count++;
			sng_qut++;
		}
		tok_for_dol(str, token, env);
		count--;
		while (count > 0)
		{
			if (ft_strchr(str + 1, '$'))
			{
				while (str[quote] && str[quote] != '$')
					quote++;
				tok_for_dol(str + quote, token, env);
			}
			count--;
		}
		if (str)
		{
			free(str);
			str = NULL;
		}
	}
	else
		add_token(token, str, WORD);
	return (1);
}

t_token	*my_tok(char *line, char **env)
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
		else if (tok_quote(line, &i, &token, env))
			continue ;
	}
	return (token);
}
