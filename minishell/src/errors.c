#include "../includes/minishell.h"

int	ft_errors(int signal, char **back, char *infile)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	if ((signal == 127 && back[0][0] == '.') || (signal == 1))
	{
		if (signal == 1)
		{
			if (infile)
				printf("bash : %s: No such file or directory\n", infile);
			else
				printf("bash : %s: No such file or directory\n", back[1]);

		}
		else
			printf("bash : %s: No such file or directory\n", back[0]);
		return (signal);
	}
	else if (signal == 127 && back[0][0] != '.')
	{
		printf("bash : %s: command not found\n", back[0]);
		return (127);
	}
	else if (signal == 126)
	{
		fd = open(back[0], O_RDONLY);
		if (fd == -1)
		{
			printf("bash: %s: Permission denied\n", back[0]);
			return (126);
		}
		line = get_next_line(fd);
		if (line && line[0] == '#' && line[1] == '!')
		{
			printf("bash : %s: %s: ", back[0], line + 2);
			printf("bad interpreter: No such file or directory\n");
		}
		else
		{
			printf("bash : %s: Permission denied\n", back[0]);
			return (126);
		}
		close(fd);
		free(line);
	}
	else if (signal == 139)
	{
		printf("Segmentation fault (core dumped)\n");
		return (139);
	}
	else if (signal == 100)
	{
		printf("bash : %s: too many arguments\n", back[0]);
		return (1);
	}
	else if (signal == 2 && !back)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (2);
	}
	return (signal);
}
