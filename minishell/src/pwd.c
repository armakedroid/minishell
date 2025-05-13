#include "../includes/minishell.h"
void	ft_pwd(char **envp, char **back)
{
	int	i;
	char	path[1024];

	i = 0;
	if (getcwd(path, sizeof(path)));
		printf("%s\n",path);
}
