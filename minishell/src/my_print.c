#include "../includes/minishell.h"

void	print_str(char **str, char *type)
{
	int	i;

	i = 0;
	if (str || *str)
	{
		while (str[i])
		{
			printf("%s = %s\n", type, str[i]);
			i++;
		}
	}
}

void	print_cmd(t_output *token)
{
	t_output	*tmp;
	char		*str;
	int			i;

	i = 0;
	str = NULL;
	if (!token)
		return ;
	while (token->args[i])
	{
		str = ft_strjoin(str, token->args[i]);
		i++;
	}
	if (token)
	{
		tmp = token;
		while (tmp)
		{
			printf("infile: %s, outfile: %s, is_p: %d, next: %d, ", tmp->infile,
				tmp->outfile, tmp->is_p, !(!(tmp->next)));
			print_str(tmp->args, "args");
			printf("\n");
			tmp = tmp->next;
		}
	}
}

void	print_token(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	tmp = token;
	while (tmp)
	{
		printf("token value: %s, token type: %d, token quote: %d\n", tmp->value,
			tmp->type, tmp->q_type);
		tmp = tmp->next;
	}
}
