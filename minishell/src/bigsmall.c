/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigsmall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:58:26 by argharag          #+#    #+#             */
/*   Updated: 2025/06/08 19:52:09 by argharag         ###   ########.fr       */
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
void here_doc_u(char **line, char ***back)
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
void my_pipe(t_output *cmds, t_pipe *val, char **env, char **my_p)
{
	int	out_fd;
	int	input_fd;

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
void my_pipe(t_output *cmds, t_pipe *val, char **env, char **my_p)
{
    int  saved_stdin;
    int  saved_stdout; 
    int  in_fd;
    int  fd[2];
    pid_t pid;
    
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	in_fd = saved_stdin;
    while (cmds)
    {
        if (cmds->next)
            if (pipe(fd) == -1)
                perror("pipe");
        
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            dup2(in_fd, STDIN_FILENO);
            if (cmds->next)
                dup2(fd[1], STDOUT_FILENO);
            if (cmds->infile)
            {
                int inf = open(cmds->infile, O_RDONLY);
                if (inf == -1)
                    perror(cmds->infile), exit(EXIT_FAILURE);
                dup2(inf, STDIN_FILENO);
                close(inf);
            }
            if (cmds->outfile)
            {
                int flags = (cmds->num == 1)
                          ? (O_RDWR | O_CREAT | O_APPEND)
                          : (O_RDWR | O_CREAT | O_TRUNC);
                int outf = open(cmds->outfile, flags, 0666);
                if (outf == -1)
                    perror(cmds->outfile), exit(EXIT_FAILURE);
                dup2(outf, STDOUT_FILENO);
                close(outf);
            }
            if (cmds->next)
            {
                close(fd[0]);
                close(fd[1]);
            }
            if (in_fd != saved_stdin)
                close(in_fd);
            check_f(cmds->args, env, my_p);
            exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(pid, NULL, 0);
            if (in_fd != saved_stdin)
                close(in_fd);
            if (cmds->next)
            {
				close(fd[1]);
                in_fd = fd[0];
            }
        }
        
        cmds = cmds->next;
    }
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}
