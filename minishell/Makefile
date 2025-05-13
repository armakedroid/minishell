NAME = minishell
SRCS = src/cd.c src/echo.c src/env.c src/export.c src/minishell.c src/pwd.c src/unset.c
OBJS = $(SRCS:%.c=%.o)
LIBFT = libft
CFLGS = -lreadline
CC = cc
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C $(LIBFT)
	@$(CC) $(CFLGS) $(OBJS) $(LIBFT)/$(LIBFT).a -o $(NAME)

%.o: %.c
	@$(CC) -c $^ -o $@

clean:
	@make clean -C $(LIBFT)
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
