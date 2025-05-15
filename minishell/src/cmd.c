#include "../includes/minishell.h"

char	*cmdfile(char *cmd, char **path, char **envp)
{
	char	*all;
	int		i;
	char	**back;

	i = 0;
	printf("\n%s\n", cmd);
	back = ft_split(cmd, ' ');
	if (!back || !*back)
		exit(127);
	while (path[i])
	{
		all = ft_strjoin(path[i], "/");
		if (back[0][0] != '/')
			all = ft_strjoin(all, back[0]);
		else
			all = ft_strjoin(all, ft_strrchr(back[0], '/') + 1);
		if (access(all, X_OK) == 0)
			execve(all, back, envp);
		free(all);
		i++;
	}
	free_split(back);
	perror("command not found");
	exit(127);
}
