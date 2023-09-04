NAME = philo

CC = @gcc -g -lpthread

CFLAGS = -Wall -Wextra -Werror 


RM = @rm -f

SRCS = philo.c utile.c ft_sleep.c

all : ${NAME}

${NAME} :
	${CC} ${CFLAGS} ${SRCS} -o ${NAME}

clean :
	${RM} ${NAME}

fclean : clean
	${RM} ${NAME}
re : fclean all