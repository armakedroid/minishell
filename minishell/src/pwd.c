#include "../includes/minishell.h"
void	ft_pwd(char **envp, char **back)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)))
		printf("%s\n",path);
}
