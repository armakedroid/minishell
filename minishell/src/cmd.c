#include "../includes/minishell.h"

int	cmdfile(char **cmd, char **path, char **envp, int *exit_status)
{
	char	*all;
	int		i;

	i = 0;
	if (!cmd || !*cmd)
	{
		*exit_status = 127;
		return (1);
	}
	if (cmd[0][0] == '.' && cmd[0][1] == '/')
	{
		if (access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd, envp);
		*exit_status = ft_errors(126, cmd, NULL);
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
				free_split(cmd);
				*exit_status = ft_errors(126, cmd, NULL);
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
	return (ft_errors(127, cmd, NULL));
	// free_split(back);
}
