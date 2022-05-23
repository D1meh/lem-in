NAME =	lem-in

SRCS =	$(wildcard lib/*.c) $(wildcard src/*.c) $(wildcard gnl/*.c)
OBJS =	$(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
RM = rm -rf

all: $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

clean:
			${RM} $(OBJS)

fclean:		clean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re