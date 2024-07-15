NAME = minishell

CC = cc

INCLUDES = -I include
CFLAGS = -Wall -Werror -Wextra $(INCLUDES)
LIBRARY =	-lreadline
SOURCES = 	./src/error.c \
			./src/readline.c \
			./src/tokenizer_utils.c \
			./src/tokenizer.c \
			./src/do_command.c \
			./src/do_command_utils.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBRARY) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SOURCES:.c=.o)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus:
	$(MAKE) all BONUS_FLAG=yes

.PHONY: all clean fclean re bonus
