/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:13:08 by argharag          #+#    #+#             */
/*   Updated: 2025/03/21 20:47:31 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include "libft/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <errno.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40
# endif
# define TMP "/tmp/here_doc"

typedef struct myl
{
	int		fd[2];
	int		infile;
	int		outfile;
	char	**cmd;
	char	*path;
	pid_t	proc1;
	pid_t	proc2;
}	t_my_s;

void	here_doc_u(char **line, char ***back);
int		open_f(char *file, int flag);
void	dup_err(const char *str);
void	closing(t_my_s *my_s);
void	fork_process2(char **argv, char **envp, t_my_s *my_s);
void	free_cmd(char	**cmd);
char	*cmdfile(char *cmd, char **path, char **envp);
char	*ft_merge(char *a, char *b);
char	*ft_fill(char **str);
int		ft_sep(char *str, char c);
char	*get_next_line(int fd);

#endif
