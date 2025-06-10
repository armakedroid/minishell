/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigsmall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:58:26 by argharag          #+#    #+#             */
/*   Updated: 2025/06/10 22:24:33 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	small(t_output *back, int *fd)
{
	int	dup_res;

	if (back->infile)
	{
		*fd = open(back->infile, O_RDONLY, 0444);
		if (*fd == -1)
			return (ft_errors1(1, back->args, back->infile));
	}
	dup_res = dup2(*fd, STDIN_FILENO);
	if (dup_res == -1)
		return (ft_errors1(127, back->args, NULL));
	close(*fd);
	return (0);
}
void	here_doc_u(char **line, char ***back)
{
	*back = ft_split(*line, '\n');
	if (!*back || !**back)
		return ;
}

void	heredoc(const char *li)
{
	char	*line;
	int		fd;
	char	**back;

	fd = open(TMP, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line || !*line)
			break ;
		if (*line != '\n')
		{
			here_doc_u(&line, &back);
			if (ft_strncmp(back[0], li, sizeof(back[0])) == 0)
			{
				free(line);
				break ;
			}
		}
		write(fd, line, strlen(line));
		free(line);
	}
	close(fd);
}

int	big_crt(t_output *back, int *fd)
{
	int	dup_res;

	if (back->outfile && back->num == 1)
	{
		*fd = open(back->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (*fd == -1)
			return (ft_errors1(1, back->args, NULL));
	}
	else if (back->outfile)
	{
		*fd = open(back->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (*fd == -1)
			return (ft_errors1(1, back->args, NULL));
	}
	dup_res = dup2(*fd, STDOUT_FILENO);
	if (dup_res == -1)
		return (ft_errors1(127, back->args, NULL));
	close(*fd);
	return (0);
}
/*
 int	open_fi(char *file, int flag)
{
	int	fd;
	int	out_fd;
	int	input_fd;

	if (flag == 0)
		fd = open(file, O_RDONLY, 0444);
	else if (flag == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		return(ft_errors_1(1, NULL, 1));
	if (fd == -1)
		return(ft_errors_1(1, NULL, 1));
	return (fd);
}*/
/*
void	my_pipe(t_output *cmds, t_pipe *val, char **env, char **my_p)
{
	out_fd = dup(STDOUT_FILENO);
	input_fd = dup(STDIN_FILENO);
	val->in_fd = input_fd;
	val->out = out_fd;
	print_cmd(cmds);
	while (cmds)
	{
		if (cmds->next)
		{
			pipe(val->fd);
			printf("0\n");
		}
		val->pid = fork();
		printf("1\n");
		if (val->pid == 0)
		{
			printf("2\n");
			dup2(val->in_fd, STDIN_FILENO);
			printf("my args = %s\n",cmds->next->args[0]);
			if (cmds->next)
				dup2(val->fd[1], STDOUT_FILENO);
			if (cmds->infile)
			{
				val->in = open(cmds->infile, O_RDONLY);
				if (val->in != -1)
				{
					dup2(val->in, STDIN_FILENO);
					printf("4\n");
				}
			}
			if (cmds->outfile)
			{
				if (cmds->num == 1)
					val->out =
						open(cmds->outfile, O_RDWR | O_CREAT | O_APPEND, 0666);
				else
					val->out =
						open(cmds->outfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
				if (val->out != -1)
					dup2(val->out, STDOUT_FILENO);
				printf("5\n");
			}
			if (cmds->next)
			{
//				dup2(val->fd[0], STDIN_FILENO);
				close(val->fd[0]);
				close(val->fd[1]);
			}
			if (val->in_fd != STDIN_FILENO)
			{
				printf("6\n");
				close(val->in_fd);
			}
			printf("\nhasa stex\n");
			print_str(cmds->args, "args");
			check_f(cmds->args, env, my_p);
			exit(0);
		}
		else
		{
			printf("11\n");
			waitpid(val->pid, NULL, 0);
			if (val->in_fd != input_fd)
				close(val->in_fd);
			if (cmds->next)
			{
				close(val->fd[1]);
				val->in_fd = val->fd[0];
			}
		}
		printf("14\n");
		printf("15\n");
		printf("16\n");
		// if (cmds->next && !cmds->next->next)
		// {
		// 	printf("cmds->next chka\n");
		// 	val->in_fd = val->fd[0];
		// 	dup2(out_fd, val->out);
		// 	close(out_fd);
		// }
		printf("barev es pipen em\n");
		cmds = cmds->next;
	}
	dup2(input_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	close(input_fd);
	close(out_fd);
}
	*/

int cmd_count(t_output *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		if (cmds->is_p)
			count++;
		cmds = cmds->next;
	}
	return (count + 1);
}

int	my_pipe(t_output *cmds, t_pipe *val, char **env, char **my_p)
{
	int		saved_stdin;
	int		saved_stdout;
	int		in_fd;
	int		**fd;
	// pid_t	pid;
	int		errors;
	int		errors1;
	int		inf;
	int		flags;
	int		outf;
	pid_t	*pid;
	int		a;
	int		cmd_nbr;
	t_output	*str;

	errors = 0;
	errors1 = 0;
	a = 0;
	cmd_nbr = cmd_count(cmds);
	in_fd = cmd_nbr - 1;
	pid = malloc(sizeof(pid_t) * cmd_nbr);
	fd = malloc(sizeof(int*) * (cmd_nbr - 1));
	while (in_fd > 0)
	{
		fd[in_fd - 1] = malloc(sizeof(int) * 2);
		in_fd--;
	}
	in_fd = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	str = cmds;
	while (str->next)
		str = str->next;
	inf = open("/dev/null", O_RDWR, 0666);
	dup2(inf, STDOUT_FILENO);
	pid[a] = fork();
	if (pid[a] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid[a] == 0)
		check_f(str->args, env, my_p, 0);
	else
	{
		waitpid(pid[a], &errors, 0);
		if (errors)
			errors1 = WEXITSTATUS(errors);
		if (errors1)
		{
			dup2(saved_stdout, STDOUT_FILENO);
			ft_errors(errors1, str->args, NULL);
			close(inf);
			return (errors1);
		}
	}
	if (inf)
		close(inf);
	dup2(saved_stdout, STDOUT_FILENO);
	str = cmds;
	in_fd = saved_stdin;
	errors = 0;
	errors1 = 0;
	while (cmds)
	{
		while (cmds->next && !(cmds->is_p))
			cmds = cmds->next;
		if (cmds->next)
			if (pipe(fd[a]) == -1)
				perror("pipe");
		pid[a] = fork();
		if (pid[a] == 0)
		{
			dup2(in_fd, STDIN_FILENO);
			if (cmds->next)
				dup2(fd[a][1], STDOUT_FILENO);
			if (cmds->infile)
			{
				inf = open(cmds->infile, O_RDONLY);
				if (inf == -1)
					perror(cmds->infile), exit(EXIT_FAILURE);
				dup2(inf, STDIN_FILENO);
				close(inf);
			}
			if (cmds->outfile)
			{
				if (cmds->num == 1)
					flags = (O_RDWR | O_CREAT | O_APPEND);
				else
					flags = (O_RDWR | O_CREAT | O_TRUNC);
				outf = open(cmds->outfile, flags, 0666);
				if (outf == -1)
					perror(cmds->outfile), exit(EXIT_FAILURE);
				dup2(outf, STDOUT_FILENO);
				close(outf);
			}
			if (cmds->next)
			{
				close(fd[a][0]);
				close(fd[a][1]);
			}
			if (in_fd != saved_stdin)
				close(in_fd);
			check_f(cmds->args, env, my_p, 1);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (in_fd != saved_stdin)
				close(in_fd);
			if (cmds->next)
			{
				close(fd[a][1]);
				in_fd = fd[a][0];
			}
			a++;
		}
		cmds = cmds->next;
	}
	in_fd = cmd_nbr;
	while (in_fd > 0 && str)
	{
		waitpid(pid[in_fd % cmd_nbr], &errors, 0);
		if (errors && str->is_p)
			errors1 = WEXITSTATUS(errors);
		if (errors1)
		{
			ft_errors(errors1, str->args, NULL);
			errors1 = 0;
		}
		in_fd--;
		str = str->next;
	}
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (errors1);
}
