/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:09:04 by argharag          #+#    #+#             */
/*   Updated: 2025/06/14 19:36:06 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>

typedef enum e_token_in
{
	WORD,
	PIPE,
	IN,
	OUT,
	APPEND,
	HEREDOC
}					t_token_in;

typedef enum e_quote_type
{
	DOUBLE,
	SINGLE
}					t_quote_type;

typedef struct s_output
{
	char			*infile;
	char			*outfile;
	char			**args;
	int				num;
	int				is_p;
	struct s_output	*next;
}					t_output;

typedef struct s_token
{
	char			*value;
	t_token_in		type;
	t_quote_type	q_type;
	t_output		out;
	struct s_token	*next;
}					t_token;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char				*ft_strdup(const char *s1);
void				*ft_calloc(size_t count, size_t size);
int					ft_atoi(const char *str);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strchr(const char *s, int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
size_t				ft_strlen(const char *s);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_itoa(int n);
char				**ft_split(char const *s, char c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strjoin(char *s1, char const *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
int					ft_lstsize(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(void *content);

#endif
