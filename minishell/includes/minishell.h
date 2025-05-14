#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <sys/wait.h>
#include "../libft/libft.h"

int		have_a_var(char **envp, char **back);
void	update_smth(char **envp, char *var, char *value);
char	**ft_export(char **envp, char **back);
int		ft_cd(char **envp, char **back);
void	ft_echo(char **back);
void	ft_env(char **envp);
void	ft_unset(char **envp, char **back);
char	*ft_pwd(char **envp, char **back);

#endif
