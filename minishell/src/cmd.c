#include "../includes/minishell.h"

char	*cmdfile(char **cmd, char **path, char **envp)
{
	char	*all;
	char	*all1;
	int		i;	

	i = 0;
	// back = ft_split(cmd, ' ');
	if (!cmd || !*cmd)
		exit(127);
	if (cmd[0][0] == '.' && cmd[0][1] == '/')
	{
		if (access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd, envp);
		else
		{
			ft_errors(126, cmd);
			exit(126);
		}
	}
	else
	{
		while (path[i])
		{
			all = ft_strjoin(path[i], "/");
			if (cmd[0][0] != '/')
				all = ft_strjoin(all, cmd[0]);
			else
				all = ft_strjoin(all, ft_strrchr(cmd[0], '/') + 1);
			if (access(all, F_OK) == 0)
			{
				if (access(all, X_OK) == 0)
					execve(all, cmd, envp);
				else
				{
					ft_errors(126, cmd);
					free_split(cmd);
					exit(126);
				}
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
	ft_errors(127, cmd);
	//free_split(back);
	exit(127);
}
