CC = cc
SRC = pipex.c utils.c cmdfile.c
SRC_B = pipex_bonus.c utils_bonus.c cmdfile_bonus.c
OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)
CFLG = -Wall -Wextra -Werror
LIBFT = libft
NAME = pipex
NAME_B = pipex_b
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	make all -C $(LIBFT)
	$(CC) $(CFLG) $(OBJ) libft/libft.a -o $@

bonus: $(NAME_B)

$(NAME_B): $(OBJ_B)
	make all -C $(LIBFT)
	$(CC) $(CFLG) $(OBJ_B) libft/libft.a -o $@

%.o:%.c Makefile pipex.h
	$(CC) $(CFLG) -c $< -o $@

clean:
	make clean -C $(LIBFT)
	$(RM) $(OBJ) $(OBJ_B) 

fclean: clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re 
