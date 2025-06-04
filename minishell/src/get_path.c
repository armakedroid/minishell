#include "../includes/minishell.h"

char	*get_path(char **env)
{
	char	*back;
	int		i;
	int		e;
	int		m;

	e = 0;
	m = 5;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			e = ft_strlen(env[i] + 5);
			back = malloc((e + 1) * sizeof(char));
			e = 0;
			while (env[i][m])
			{
				back[e] = env[i][m];
				e++;
				m++;
			}
			return (back);
		}
		i++;
	}
	return (NULL);
}
