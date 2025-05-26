#include "../includes/minishell.h"

void	ft_errors(int signal, char **back)
{
	char	*line;
	int	fd;
	int	i;

	i = 0;
	if ((signal == 127 && back[0][0] == '.') || (signal == 1 && !ft_strncmp(back[0], "cd", 3)))
	{
		printf("bash : %s: No such file or directory\n", back[0]);
		return(signal);
	}
	else if (signal == 127 && back[0][0] != '.')
	{
		printf("bash : %s: command not found\n", back[0]);
		return(127);
	}
	else if (signal == 126)
	{
		fd = open(back[0], O_RDONLY);
		if (fd == -1)
		{
			printf("bash: %s: Permission denied\n", back[0]);
			return(126);
		}
		line = get_next_line(fd);
		if (line && line[0] == '#' && line[1] == '!')
			printf("bash : %s: %s: bad interpreter: No such file or directory\n",back[0], line + 2);
		else
		{
			printf("126 -2 \n\n");
			printf("bash : %s: Permission denied\n", back[0]);
			return(126);
		}
		close(fd);
		free(line);
	}
	else if (signal == 139)
	{
		printf("Segmentation fault (core dumped)\n");
		return(139);
	}
	else if (signal == 100)
	{
		printf("bash : %s: too many arguments\n", back[0]);
		return(1);
	}
}
