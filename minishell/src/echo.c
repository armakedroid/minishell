#include "../includes/minishell.h"

// static int	need_change(char *back)
// {
// 	int	i;

// 	i = 0;
// 	if (back[0] == '\"')
// 	{
// 		if (back[1] && back[1] == '\'')
// 			return (1);
// 	}
// 	return (0);
// }

// char *get_my_env(char *str, char **env)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (env[i])
// 	{
// 		j = 0;
// 		while (env[i][j])
// 		{
// 			if (ft_strncmp())
// 		}
// 	}
// }

int	ft_echo(char **argv, int signal)
{
	int		i;
	int		j;
	int		n;
	char	*str;
	char	**back;

	n = 0;
	i = 1;
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
		n = ++i - 1;
	while (argv[i])
	{
		back = ft_split(argv[i], ' ');
		j = 0;
		while (back[j])
		{
			if (back[j][0] == '\'' || back[j][ft_strlen(back[j]) - 1] == '\'')
			{
				str = ft_strtrim(back[j], "'");
				free(back[j]);
				back[j] = str;
				printf("%s", back[j]);
			}
			else if (back[j][0] == '\"' || back[j][ft_strlen(back[j])
				- 1] == '\"')
			{
				str = ft_strtrim(back[j], "\"");
				free(back[j]);
				back[j] = ft_strdup(str);
				free(str);
				if (back[j][0] == '$' && back[j][1])
				{
					if (back[j][1] == '?')
					{
						printf("%d\n", signal);
						return (0);
					}
					str = getenv(back[j] + 1);
					if (str)
						printf("%s", str);
				}
				else
					printf("%s", back[j]);
			}
			else
			{
				if (back[j][0] == '$' && back[j][1])
				{
					if (back[j][1] == '?')
					{
						printf("%d\n", signal);
						return (0);
					}
					str = getenv(back[j] + 1);
					if (str)
						printf("%s", str);
				}
				else
					printf("%s", back[j]);
			}
			if (back[j + 1] || str)
				printf(" ");
			j++;
		}
		free_split(back);
		back = NULL;
		i++;
	}
	if (n != 1)
		printf("\n");
	return (0);
}
