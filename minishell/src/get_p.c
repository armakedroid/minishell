#include "minishell.h"

char *get_p(char **back, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}
