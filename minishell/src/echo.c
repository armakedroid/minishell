#include "../includes/minishell.h"

void	ft_echo(char **argv)
{
	int		i;
	int		j;
	int		n;
	char	*str;
	char 	**back;

	n = 0;
	i = 1;
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
		n = ++i - 1;
	while (argv[i])
	{
		back  = ft_split(argv[i], ' ');
		j = 0;
		while (back[j])
		{
			if(back[j][0] == '$' && back[j][1])
			{
				str = getenv(back[j] + 1);
				if (str)
					printf("%s", str);
			}
			else
				printf("%s",back[j]);
			if (back[j + 1] || str)
				printf(" ");
			j++;
		}
		free_split(back);
		back = NULL;
		i++;
	}
	if (n != 1)
		printf("\n");
}
