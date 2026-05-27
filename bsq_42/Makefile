NAME = bsq

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
	file_opr.c \
	map_columns.c \
	map_header.c \
	map_header_utils.c \
	memory.c \
	print.c \
	stdin.c \
	validate.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c bsq.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
