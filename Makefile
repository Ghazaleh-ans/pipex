NAME        = pipex

SRCS_FILES  = main.c pipex.c pipex_utils.c
BONUS_FILES = main_bonus.c pipex_bonus.c pipex_utils_bonus.c pipex_heredoc_bonus.c

SRCS_MAN    = $(SRCS_FILES)
SRCS_BONUS  = $(BONUS_FILES)
OBJS_MAN    = $(SRCS_MAN:.c=.o)
OBJS_BONUS  = $(SRCS_BONUS:.c=.o)

LIB_DIR     = Libft
LIB_NAME    = libft.a
LIBFT       = $(LIB_DIR)/$(LIB_NAME)
HEADER      = -I./pipex.h
HEADER_B    =-I./pipex_bonus.h

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

all: $(NAME)

$(NAME): $(OBJS_MAN) pipex.h
	@echo "\033[38;2;0;0;255m╰⊱♥⊱╮ღ꧁ PIPEX by Ghazaleh ꧂ღ╭⊱♥≺"
	@echo "\033[38;2;128;0;128m\n(✿◠‿◠)\n"
	@echo "\033[38;2;255;105;180m+++++Compiling the libft+++++\n"
	@make -C $(LIB_DIR)
	@$(CC) $(CFLAGS) $(HEADER) -I. $(OBJS_MAN) -L$(LIB_DIR) -lft -o $(NAME)
	@#clear
	@echo "\033[38;2;0;255;0mThe coolest PIPEX is ready! ᕕ( ᐛ )ᕗ\n"

bonus: $(OBJS_BONUS) pipex_bonus.h
	@echo "\033[38;2;0;0;255m╰⊱♥⊱╮ღ꧁ PIPEX BONUS by Ghazaleh ꧂ღ╭⊱♥≺"
	@echo "\033[38;2;128;0;128m\n(✿◠‿◠)\n"
	@echo "\033[38;2;255;105;180m+++++Compiling the libft+++++\n"
	@make -C $(LIB_DIR)
	@$(CC) $(CFLAGS) $(HEADER_B) -I. $(OBJS_BONUS) -L$(LIB_DIR)  -lft -o $(NAME)
	@#clear
	@echo "\033[38;2;0;255;0mYES! It's bonus time! ─=≡Σʕっ•ᴥ•ʔっ\n"
%.o: %.c
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@make clean -C $(LIB_DIR)
	$(RM) $(OBJS_MAN)
	$(RM) $(OBJS_BONUS)

fclean: clean
	@make fclean -C $(LIB_DIR)
	$(RM) $(NAME)
	$(RM) $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
