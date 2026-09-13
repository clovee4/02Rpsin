NAME = rush-02

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = main.c convert.c dict.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
