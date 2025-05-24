#include "../includes/minishell.h"

char	*ft_pwd(char **envp)
{
	char	path[1024];

	if (!getcwd(path, sizeof(path)))
		return (NULL);
	return (ft_strdup(path));
}
