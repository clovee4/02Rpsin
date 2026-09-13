NAME = rush-02
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c input.c utils.c read_dict.c parse_dict.c parse_line.c dict_utils.c \
	append.c convert.c convert_group.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c rush02.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
