#include "../includes/minishell.h"

void	ft_echo(char **argv)
{
	int	i;
	int	n;

	n = 0;
	i = 1;
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
		n = ++i - 1;
	while (argv[i])
	{
		printf("%s",argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (n != 1)
		printf("\n");
}
