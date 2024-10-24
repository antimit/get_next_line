CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = gnl.a
SRCS = get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^
 
all: $(NAME)


$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(NAME)

.PHONY: clean fclean
