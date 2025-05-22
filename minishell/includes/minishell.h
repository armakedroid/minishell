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
#include "../gnl/get_next_line.h"

typedef enum	e_token_in
{
	WORD,
	PIPE,
	IN,
	OUT,
	APPEND,
	HEREDOC
}	t_token_in;

typedef struct s_token
{
	char	*value;
	t_token_in	type;
	struct s_token	*next;
}	t_token;

int		have_a_var(char **envp, char **back);
void	update_smth(char **envp, char *var, char *value);
char	**ft_export(char **envp, char **back);
int		ft_cd(char **envp, char **back);
void	ft_echo(char **back);
void	ft_env(char **envp);
char	**ft_unset(char **envp, char **back);
char	*ft_pwd(char **envp, char **back);
char	*cmdfile(char *cmd, char **path, char **envp);
char	*get_path(char **env);
void	free_split(char **back);
char	*ft_merge(char *a, char *b);
char	*ft_fill(char **str);
int		ft_sep(char *str, char c);
char	*get_next_line(int fd);
void	ft_errors(int signal, char **back);

#endif
