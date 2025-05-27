/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:33:41 by argharag          #+#    #+#             */
/*   Updated: 2025/05/27 19:34:30 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

int		have_a_var(char **envp, char **back);
void	update_smth(char **envp, char *var, char *value);
char	**ft_export(char **envp, char **back);
int		ft_cd(char **str, char **envp);
int		ft_echo(char **back, int signal);
int		ft_env(char **envp);
char	**ft_unset(char **envp, char **back);
char	*ft_pwd(char **envp);
int		cmdfile(char **cmd, char **path, char **envp);
char	*get_path(char **env);
void	free_split(char **back);
char	*ft_merge(char *a, char *b);
char	*ft_fill(char **str);
int		ft_sep(char *str, char c);
char	*get_next_line(int fd);
int		ft_errors(int signal, char **back);
void	print_str(char **str, char *type);

#endif
