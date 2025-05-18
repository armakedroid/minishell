#include "../includes/minishell.h"

char	*cmdfile(char *cmd, char **path, char **envp)
{
	char	*all;
	char	*all1;
	int		i;	
	char	**back;

	i = 0;
	back = ft_split(cmd, ' ');
	if (!back || !*back)
		exit(127);
	if (back[0][0] == '.' && back[0][1] == '/')
	{
		if (access(back[0], X_OK) == 0)
			execve(back[0], back, envp);
		else
			ft_errors(126, back);
	}
	else
	{
		while (path[i])
		{
			all = ft_strjoin(path[i], "/");
			if (back[0][0] != '/')
				all = ft_strjoin(all, back[0]);
			else
				all = ft_strjoin(all, ft_strrchr(back[0], '/') + 1);
			if (access(all, F_OK) == 0)
			{
				if (access(all, X_OK) == 0)
					execve(all, back, envp);
				else
					ft_errors(126, back);
			}
			free(all);
			all = NULL;
			i++;
		}
	}
	/*if (back[0][0] == '.' && back[0][1] == '/')
		perror(cmd);
	else
	{
		all = ft_strjoin("bash: command not found: ", cmd);
		all1 = ft_strjoin(all, "\n");
		ft_putstr_fd(all1, 2);
		free(all);
		free(all1);
		free(all);
	}*/
	ft_errors(127, back);
	free_split(back);
	exit(127);
}
