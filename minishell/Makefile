NAME = minishell

SRCS = src/cd.c src/echo.c src/env.c src/export.c src/minishell.c \
	   src/pwd.c src/unset.c src/get_p.c src/cmd.c src/get_path.c  src/exit_cmds.c src/tok3.c\
	   src/errors.c src/bigsmall.c gnl/get_next_line.c gnl/get_next_line_utils.c src/all_free.c src/my_tok.c src/min_utils.c src/pars_ut.c src/more_utils.c src/main.c src/my_pipe.c src/utils_mix.c src/tok_quote.c src/my_fun.c src/per.c src/lines.c

OBJS = $(SRCS:%.c=%.o)

LIBFT = libft/libft.a

CC = cc
CFLGS = -Wall -Wextra -Werror

READLINE_FLAGS = -lreadline -g3

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) libft
	@make bonus -C libft
	@$(CC) $(OBJS) $(LIBFT) $(READLINE_FLAGS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLGS) -c $< -o $@

clean:
	@make clean -C libft
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C libft
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

