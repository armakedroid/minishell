#include "../includes/minishell.h"

void	ft_errors(int signal, char **back)
{
	char	*line;
	int	fd;
	int	i;

	i = 0;
	if (signal == 127 && back[0][0] != '.')
	{
		printf("bash : %s: command not found", back[0]);
		return ;
	}
	else if (signal == 127 && back[0][0] == '.')
	{
		printf("bash : %s: No such file or directory", back[0]);
		return ;
	}
	else if (signal == 126)
	{
		fd = open(back[0], O_RDONLY);
		line = get_next_line(fd);
		if (line[0] == '#' && line[1] == '!')
			printf("bash : %s: %s: bad interpreter: No such file or directory",back[0], line + 2);
		else
			printf("bash : %s: Permission denied", back[0]);
		close(fd);
		free(line);
		return ;
	}
}
