/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:48:13 by argharag          #+#    #+#             */
/*   Updated: 2025/05/14 19:41:32 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <sys/wait.h>
#include "../includes/minishell.h"

char **command_s(char *line)
{
	char	**back;
	back = ft_split(line, ' ');
	if (!back)
		return (NULL);
	return (back);
}

void check_f(char **back, char **envp)
{
	if (ft_strncmp(back[0], "echo", 4) == 0)
		ft_echo(back);
	else if (ft_strncmp(back[0], "pwd", 3) == 0)
		ft_pwd(envp, back);
	else if (ft_strncmp(back[0], "export", 6) == 0)
		printf("es exportn em\n");
	else if (ft_strncmp(back[0], "unset", 5) == 0)
		ft_unset(envp, back);
	else if (ft_strncmp(back[0], "env", 3) == 0)
		ft_env(envp);
	else
		write(1, "bash: command not found\n", 25);
	exit(1);
	// wait(NULL);
}

void free_split(char **back)
{
	int	i;

	i = 0;
	while (back[i])
	{
		free(back[i]);
		i++;
	}
	free(back);
}

void handle_sigint(int x)
{
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**back;
	int		pordz;
	pid_t	cha;

	if (argc != 1)
		return (write(1, "Error: You must run only ./minishell\n", 37));
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("minishell $ ");
		if (!line)
			break;
		if (*line)
			add_history(line);
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break;
		}
		back = command_s(line);
		if (!back)
			exit (1);
		if (!(ft_strncmp(back[0], "cd", 3)))
			ft_cd(envp, back);
		else
		{
			cha = fork();
			if (cha == 0)
				check_f(back, envp);
		}
		wait(NULL);
		rl_redisplay();
	}
	free(line);
	free_split(back);
	return (0);
}
