/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:48:13 by argharag          #+#    #+#             */
/*   Updated: 2025/05/23 21:18:28 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <sys/wait.h>
#include "../includes/minishell.h"

int is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}

char **command_s(char *line)
{
	char	**back;
	back = ft_split(line, ' ');
	if (!back)
		return (NULL);
	return (back);
}

void check_f(char **back, char **envp, char **path)
{
	char	*line;
	int	i;

	i = 0;
	line = NULL;
	if (ft_strncmp(back[0], "echo", 5) == 0)
		ft_echo(back);
	else if (ft_strncmp(back[0], "pwd", 4) == 0)
		printf("%s\n", ft_pwd(envp, back));
	else if (ft_strncmp(back[0], "export", 7) == 0)
		envp = ft_export(envp, back);
	else if (!ft_strncmp(back[0], "env", 4))
		ft_env(envp);
	else
	{
		while (back[i])
		{
			line = ft_strjoin(line, back[i]);
			if (back[i + 1])
				line = ft_strjoin(line, " ");
			i++;
		}
		cmdfile(line, path, envp);
	}
	exit(0);
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

char	**ft_copy_env(char **envp)
{
	char	**tmp;
	char	*shl;
	int		i;

	i = 0;
	while(envp[i])
		i++;
	tmp = malloc((i) * sizeof(char *));
	i = 0;
	while(envp[i])
	{
		// if (!ft_strncmp(envp[i], "SHLVL=", 7))
		// 	envp[i] = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(envp[i] + 6) + 1));
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

t_token *create_t(char *str, int i)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(str);
	token->type = i;
	token->next = NULL;
	return (token);
}

void add_token(t_token **token, char *str, int i)
{
	t_token	*new;

	new = create_t(*token, str);
	//es funkciayum sax tokennery kpcnum enq irar
}

t_token *my_tok(char *line)
{
	int	i;
	int	start;
	t_token	*token;

	i = 0;
	start = 0;
	token = NULL;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '|')
		{
			add_token(&token, "|" ,PIPE);
			i++;
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
			{
				add_token(&token, ">>", APPEND);
				i += 2;
			}
			else
			{
				add_token(&token, ">", OUT);
				i++;
			}
		}
		else if (line[i] == '<')
		{
			if (line[i + 1] == '<')
			{
				add_token(&token, "<<", HEREDOC)
				i += 2;
			}
			else
			{
				add_token(&token, "<", IN);
				i++;
			}
		}
		else if (line[i] == '|')
		{
			add_token(&token, "|", PIPE);
			i++;
		}
		else
		{
			start = i;
			while (line[i] && !is_operator(line[i]) && !is_space(line[i]))
				i++;
			add_token(&token, ft_substr(line, start, i - start), WORD);
		}
	}
	return (token);
}

int main(int argc, char **argv, char **envp)
{
	t_token	*token;
	char	*line;
	char	**back;
	char	**env;
	pid_t	cha;
	char	*path;
	static int		signal1;
	char	**my_p;

	if (argc != 1)
		return (write(1, "Error: You must run only ./minishell\n", 37));
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	env = ft_copy_env(envp);
	path = get_path(envp);
	my_p = ft_split(path, ':');
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		if (*line)
			add_history(line);
		token = my_tok(line);
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break;
		}
		back = command_s(line);
		if (!back)
			exit (1);
		if (!(ft_strncmp(back[0], "cd", 3)))
			ft_cd(env, back);
		else if (!(ft_strncmp(back[0], "export", 7)))
			env = ft_export(env, back);
		else if (ft_strncmp(back[0], "unset", 6) == 0)
			env = ft_unset(env, back);
		else
		{
			cha = fork();
			if (cha == 0)
				check_f(back, env, my_p);
		}
		waitpid(cha, &signal1,0);
		signal1 = signal1 / 256;
		if (ft_strncmp(back[0], "$?", 3) == 0)
			printf("%d\n",signal1);
		/*ft_errors(signal1, back);*/
		rl_redisplay();
	}
	//free(line);
	free_split(back);
	return (0);
}
