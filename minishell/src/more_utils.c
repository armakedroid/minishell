#include "../includes/minishell.h"

char	**ft_copy_env(char **envp)
{
	char	**tmp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	tmp = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "SHLVL=", 7))
			envp[i] = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(envp[i] + 6) + 1));
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

t_token	*create_t(char *str, int i)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = str;
	token->type = i;
	token->q_type = DOUBLE;
	if (str[0] == '\'')
		token->q_type = SINGLE;
	token->next = NULL;
	return (token);
}

void	ft_lstadd_back1(t_token **lst, t_token *new)
{
	t_token	*back;

	back = NULL;
	if (!lst || !new)
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

void	add_token(t_token **token, char *str, int i)
{
	t_token	*new;

	new = create_t(str, i);
	if (!new)
		return ;
	if (!*token)
		*token = new;
	else
		ft_lstadd_back1(token, new);
}

void initialization(t_mini *var, char **envp)
{
	(*var).env = ft_copy_env(envp);
	(*var).path = get_path((*var).env);
	(*var).my_p = ft_split((*var).path, ':');
	(*var).fd = 0;
}