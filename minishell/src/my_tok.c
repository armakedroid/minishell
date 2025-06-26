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

int	tok_for_dol_2(char *str, char **env)
{
	if (str[0] == '?' && !str[1])
		return (1);
	else if (get_my_env(str, env))
		return (1);
	return (0);
}

char	*tok_for_dol(char *str, char **env)
{
	if (str[0] == '?' && !str[1])
		return (ft_itoa(g_exit_status));
	else if (get_my_env(str, env))
		return (ft_strdup(get_my_env(str, env)));
	return (NULL);
}

int	tok_quote(char *line, int *i, t_token **token, char **env)
{
	int		start;
	int		quote;
	int		sng_qut;
	int		count;
	int		l;
	int		j;
	char	*str;
	char	**all;
	char	*all1_h;
	char	*all1;
	char	*all2;
	int		is_echo;

	start = *i;
	quote = 1;
	sng_qut = 1;
	count = 0;
	is_echo = 0;
	all = NULL;
	while ((line[*i] && !is_space(line[*i]) && !is_operator(line[*i]))
		|| (quote == 0 || sng_qut == 0))
	{
		if (line[*i] == '\"' && quote)
		{
			quote = 0;
			start = ++(*i);
		}
		else if (line[*i] == '\'' && sng_qut)
		{
			sng_qut = 0;
			start = ++(*i);
		}
		else if (line[*i] == '\"' && !quote)
		{
			quote = 2;
			(*i)++;
		}
		else if (line[*i] == '\'' && !sng_qut)
		{
			sng_qut = 2;
			(*i)++;
		}
		else
			(*i)++;
		if (line[*i] && line[*i + 1] && line[*i] == '\'' && !quote && !sng_qut)
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
	if (sng_qut == 2)
	{
		all2 = ft_strtrim(str, "'");
		free(str);
		str = all2;
	}
	if (ft_strchr(str, '$') && quote && sng_qut == 1)
	{
		l = 0;
		if (ft_strlen(str) == 1)
		{
			add_token(token, ft_strdup("$"), WORD);
			return (0);
		}
		while (str[l] && str[l] != '$')
			l++;
		if (l)
			all1 = ft_substr(str, 0, l);
		else
		{
			while (str[l] && str[l + 1] && str[l + 1] == '$')
				l++;
			all1 = NULL;
		}
		if (str && ft_strlen(str + l) == 1)
			return (0);
		all = ft_split(str + l - !(!(l)), '$');
		if (str[0] == '$')
			quote = 0;
		else
			quote = 1;
		l = 0;
		while (all[quote])
		{
			while (all[quote][l])
			{
				if (all[quote][l] && (!ft_isalpha(all[quote][l])
						&& all[quote][l] != '?' && all[quote][l] != '_'))
					break ;
				l++;
			}
			if (!l)
				return (0);
			if (tok_for_dol_2(ft_substr(all[quote], 0, l), env))
				all1_h = ft_strjoin(all1, tok_for_dol(ft_substr(all[quote], 0,
								l), env));
			else
				all1_h = ft_strjoin(all1, " ");
			free(all1);
			all1 = all1_h;
			j = l;
			if (!all1_h)
				return (0);
			while (all[quote][l])
				l++;
			if (j != l)
				all1_h = ft_strjoin(all1, ft_substr(all[quote], j, l - j));
			all1 = all1_h;
			quote++;
		}
		add_token(token, all1, WORD);
		if (str)
		{
			free(str);
			str = NULL;
		}
		if (all)
		{
			free_split(all);
			all = NULL;
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
