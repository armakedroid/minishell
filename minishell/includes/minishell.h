/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:33:41 by argharag          #+#    #+#             */
/*   Updated: 2025/07/15 19:52:30 by apetoyan         ###   ########.fr       */
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
# define A tok_for_dol
# define B ft_substr
# define C ft_strjoin
# define D tok_for_dol_2
# define E t_output

extern int			g_exit_status;

typedef struct s_pipe
{
	int				in;
	int				out;
	int				fd[2];
	int				in_fd;
	pid_t			pid;
}					t_pipe;

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
	int				signal1;
	char			**my_p;
	t_output		*cmd;
	t_output		*cmd_start;
	int				stdout1;
	int				stdin1;
	int				fd;
	t_pipe			val;
	int				k;
	char			*str;
	struct termios	orig_termios;
}					t_mini;

typedef struct s_parse
{
	t_output		*back;
	t_output		*tmp;
	t_output		*for_args;
	int				i;
}					t_parse;

typedef struct s_tok_quote
{
	int				start;
	int				quote;
	int				sng_qut;
	int				l;
	int				j;
	int				tok_qut;
	char			*str;
	char			**all;
	char			*all1_h;
	char			*all1;
	char			*all2;
}					t_tok_quote;

typedef struct s_pipes
{
	int				saved_stdin;
	int				saved_stdout;
	int				in_fd;
	int				**fd;
	int				errors;
	int				errors1;
	int				inf;
	int				outf;
	pid_t			*pid;
	int				a;
	int				cmd_nbr;
	t_output		*str;
	t_output		*cmd_s;
}					t_pipes;

int					tok_quote3(t_tok_quote *tok, char **env);
int					tok_sec_ut(t_tok_quote *tok, t_token **token);
void				tok4_ut(t_tok_quote *tok);
void				my_pipe_while(t_pipes *m_p);
void				fork_ut(t_mini *var);
int					tokens_and_parse(t_mini *var);
int					main_while(t_mini *var);
void				cmds_while_utils(t_pipes *m_p, t_output *cmds);
void				main_function_utils(t_mini *var);
void				var_f(t_mini *var);
void				main_ut(t_mini *var);
int					cd_utils(char **str, char **envp, char *home);
int					cd_utils_mod(char **str, char *home, char **envp);
void				free_ut(t_output *cmd, char **envp, char **path);
void				free_parse(t_parse *var);
t_parse				*parse(t_token *token);
void				cmds_exit(t_pipes *m_p);
void				tok_first(int *i, char *line, t_tok_quote *tok);
char				*tok_for_dol(char *str, char **env);
int					tok_for_dol_2(char *str, char **env);
int					tok_quote(char *line, int *i, t_token **token, char **env);
int					exit_var_ut(t_mini *var, char ***str, ssize_t *k);
int					exit_return(char **str);
void				sort(char **envp);
void				print_env(char **envp);
char				**export_without_arg(char **envp);
void				initialization(t_mini *var, char **envp);
int					parse_and_pipe(t_mini *var);
int					space_token(t_mini *var, char **env);
int					main_main(t_mini *var, char **env);
int					exit_var(t_mini *var);
t_token				*create_t(char *str, int i);
char				**ft_copy_env(char **envp);
void				ft_lstadd_back1(t_token **lst, t_token *new);
t_output			*create_out(char **str, char *infile, char *outfile);
void				cmdfun(t_output **lst, t_output *new);
int					my_parse_ut(t_output **back, t_output **tmp,
						t_token **token, t_output **for_args);
void				add_token(t_token **token, char *str, int i);
int					my_pipe(t_output *cmds, t_mini *var, char **my_p);
void				check_f(t_output *cmd, char **envp, char **path, int flag);
void				here_doc_u(char **line, char ***back);
void				heredoc(const char *li);
int					have_a_var(char **envp, char **back);
void				update_smth(char **envp, char *var, char *value);
char				**ft_export(char **envp, char **back);
int					ft_cd(char **str, char **envp);
int					ft_echo(char **back, int signal, char **env);
int					ft_env(char **envp);
char				**ft_unset(char **envp, char **back);
char				*ft_pwd(char **env);
int					cmdfile(char **cmd, char **path, char **envp,
						int *exit_status);
int					cmd_unexit(char **cmd, char **path, char **envp,
						int *exit_status);
char				*get_path(char **env);
void				free_tokens(t_token *tokens);
char				*ft_merge(char *a, char *b);
char				*ft_fill(char **str);
int					ft_sep(char *str, char c);
char				*get_next_line(int fd);
int					ft_errors1(int signal, char **back, char *infile);
int					ft_errors(int signal, char **back, char *infile);
int					ft_errors126(int signal, char **back, char *infile);
int					big_crt(t_output *back, int *fd);
int					small(t_output *back, int *fd);
void				free_var(void *var);
void				free_cmd(t_output *cmd);
void				free_cmd_start(t_output *cmd);
void				free_cmd_start_wthend(t_output *cmd);
void				free_split(char **back);
int					is_space(char c);
int					is_operator(char c);
void				cd_utils_mod_ut(char **str1, char **str2, char **str,
						char *home);
char				**command_s(char *line);
t_token				*my_tok(char *line, char **env);
void				parse_ut(t_output **tmp, t_token **token);
int					parse_heredoc(t_token **token);
int					parse_wrd(t_token **token, t_output **tmp, int *i);
void				handle_sigint(int sl);
char				*get_my_env(char *str, char **env);
void				free_fd(int **fd, int i);
int					cmd_count(t_output *cmds);
int					foo(char *line, char c);
char				*get_home(char **envp);

#endif
