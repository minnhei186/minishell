NAME = minishell

CC = cc

RLDIR	= $(shell brew --prefix readline)
INCLUDES = -I include -I libft
CFLAGS = -Wall -Werror -Wextra $(INCLUDES)
LIBRARY =	-lreadline -L$(RLDIR)/lib libft -lft
# SOURCES = 	./src/last_status.c \
# 			./src/error_utils.c \
# 			./src/error.c \
# 			./src/read_pipe.c \
# 			./src/readline.c \
# 			./src/tokenizer_quotes.c \
# 			./src/tokenizer_utils.c \
# 			./src/tokenizer.c \
# 			./src/do_command.c \
# 			./src/do_command_utils.c \
# 			./src/expand_special_parameter.c \
# 			./src/expand_utils.c \
# 			./src/expand_quote.c \
# 			./src/expand.c \
# 			./src/parse_pipe.c \
# 			./src/parse_redirection.c \
# 			./src/parse_append.c \
# 			./src/parse.c \
# 			./src/destructor.c \
# 			./src/redirect_utils.c \
# 			./src/redirect.c \
# 			./src/pipe.c
SOURCES = 	./src/error_utils.c \
			./src/error.c \
			./src/read_pipe.c \
			./src/readline.c \
			./src/tokenizer_quotes.c \
			./src/tokenizer_utils.c \
			./src/tokenizer.c \
			./src/do_command.c \
			./src/do_command_utils.c \
			./src/expand_special_parameter.c \
			./src/expand_utils.c \
			./src/expand_quote.c \
			./src/expand.c \
			./src/parse_pipe.c \
			./src/parse_redirection.c \
			./src/parse_append.c \
			./src/parse.c \
			./src/destructor.c \
			./src/redirect_utils.c \
			./src/redirect.c \
			./src/pipe.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) libft
	$(CC) $(OBJECTS) $(LIBRARY) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	make -C libft

clean:
	rm -f $(SOURCES:.c=.o)
	make -C libft clean

fclean: clean
	rm -f $(NAME) libft/libft.a

re: fclean all

bonus:
	$(MAKE) all BONUS_FLAG=yes

.PHONY: all clean libft fclean re bonus
