NAME =	lem-in
GENERATOR_NAME = generator

SRCS =	$(wildcard src/*.c) $(wildcard lib/*.c) $(wildcard gnl/*.c)

GENERATOR_SRCS =  $(wildcard map_generator/*.c) $(wildcard lib/*.c)

OBJS =	$(SRCS:.c=.o)
GENERATOR_OBJS = $(GENERATOR_SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

generator:	${GENERATOR_OBJS}
			${CC} ${CFLAGS} ${GENERATOR_OBJS} -o ${GENERATOR_NAME}

clean:
			${RM} $(OBJS)
			${RM} ${GENERATOR_OBJS}
fclean:		clean
			${RM} $(NAME)
			${RM} ${GENERATOR_NAME}

re:			fclean all

.PHONY:		all clean fclean re