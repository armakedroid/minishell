/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:33:41 by argharag          #+#    #+#             */
/*   Updated: 2025/06/21 16:31:56 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# define TMP "/tmp/here_doc"

extern int g_exit_status;

typedef struct s_pipe
{
	int	in;
	int	out;
	int	fd[2];
 	int	in_fd;
	pid_t	pid;
}	t_pipe;

typedef struct s_mini
{
	t_token			*token;
	t_token			*ttmp;
	int				cd_result;
	char			*line1;
	char			*line;
	char			**env;
	pid_t			cha;
	char			*path;
	int		signal1;
	char			**my_p;
	t_output		*cmd;
	t_output		*cmd_start;
	int				stdout1;
	int				stdin1;
	int				fd;
	t_pipe			val;
	int				k;
	struct termios	orig_termios;
}	t_mini;


typedef struct s_parse
{
	t_output	*back;
	t_output	*tmp;
	t_output	*for_args;
	int			i;
}	t_parse;

void initialization(t_mini *var, char **envp);
int parse_and_pipe(t_mini *var);
int	space_token(t_mini *var);
int	main_main(t_mini *var);
int exit_var(t_mini *var, int *g_exit_status);
t_token	*create_t(char *str, int i);
char	**ft_copy_env(char **envp);
void	ft_lstadd_back1(t_token **lst, t_token *new);
t_output	*create_out(char **str, char *infile, char *outfile);
void	cmdfun(t_output **lst, t_output *new);
int my_parse_ut(t_output **back, t_output **tmp, t_token **token, t_output **for_args);
void	add_token(t_token **token, char *str, int i);
int		my_pipe(t_output *cmds, t_pipe *val, char **env, char **my_p);
void	check_f(char **back, char **envp, char **path, int flag);
void	here_doc_u(char **line, char ***back);
void	heredoc(const char *li);
int		have_a_var(char **envp, char **back);
void	update_smth(char **envp, char *var, char *value);
char	**ft_export(char **envp, char **back);
int		ft_cd(char **str, char **envp);
int		ft_echo(char **back, int signal);
int		ft_env(char **envp);
char	**ft_unset(char **envp, char **back);
char	*ft_pwd();
int		cmdfile(char **cmd, char **path, char **envp, int *exit_status);
int		cmd_unexit(char **cmd, char **path, char **envp, int *exit_status);
char	*get_path(char **env);
void	free_tokens(t_token *tokens);
char	*ft_merge(char *a, char *b);
char	*ft_fill(char **str);
int		ft_sep(char *str, char c);
char	*get_next_line(int fd);
int		ft_errors1(int signal, char **back, char *infile);
int		ft_errors(int signal, char **back, char *infile);
int		ft_errors126(int signal, char **back, char *infile);
int		big_crt(t_output *back, int *fd);
int		small(t_output *back, int *fd);
void	print_str(char **str, char *type);
void	print_cmd(t_output *token);
void	free_var(void *var);
void	free_cmd(t_output *cmd);
void	free_split(char **back);
int	is_space(char c);
int	is_operator(char c);
char	**command_s(char *line);
t_output        *parse(t_token *token, int *g_exit_status);
t_token	*my_tok(char *line);
void	print_token(t_token *token);
void	parse_ut(t_output **tmp, t_token **token);
int		parse_heredoc(t_token **token, int *g_exit_status);
int parse_wrd(t_token **token, t_output **tmp, int *i, int *g_exit_status);
void    handle_sigint(int sl);

#endif
