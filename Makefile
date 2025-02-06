NAME		=	pipex

SRCS_FILES	= main.c pipex.c pipex_utils.c

SRCS_MAN	= 	$(SRCS_FILES)
OBJS_MAN	=	$(SRCS_MAN:.c=.o)

LIB_DIR		=	Libft
LIB_NAME 	=	libft.a
HEADER		=	-I./pipex.h

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f

all:		$(NAME)

$(NAME):	$(OBJS_MAN) pipex.h
			@echo "\033[38;2;0;0;255m╰⊱♥⊱╮ღ꧁ PIPEX by Ghazaleh ꧂ღ╭⊱♥≺"
			@echo "\033[38;2;128;0;128m\n(✿◠‿◠)\n"
			@echo "\033[38;2;255;105;180m+++++Compiling the libft+++++"
			@make -C $(LIB_DIR)
			@$(CC) $(CFLAGS) $(HEADER) $(LIB_DIR)/libft.a $(OBJS_MAN) -o $(NAME)
			@#clear
			@echo "\033[38;2;0;255;0mThe coolest PIPEX is ready! ᕕ( ᐛ )ᕗ"

%.o:		%.c Libft/*.c
			@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
			@make clean -C $(LIB_DIR)
			$(RM) $(OBJS_MAN)
			$(RM) $(OBJS_BONUS)

fclean:		clean
			@make fclean -C $(LIB_DIR)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
