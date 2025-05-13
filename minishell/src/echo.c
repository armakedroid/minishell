#include "../includes/minishell.h"

void	ft_echo(char **argv)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	if (argv[0] && ft_strncmp(argv[0], "-n", 2) == 0)
	{
		i++;
		n = 1;
	}
	while (argv[i])
	{
		printf("%s",argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
}
