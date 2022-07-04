NAME	=	philo

SRCS	=	args.c \
			eat.c \
			finish.c \
			ft_atoi.c \
			init.c \
			philo.c \
			put_forks.c \
			routine.c \
			routine_rip.c \
			sleep.c \
			take_forks.c \
			take_forks_utils.c \
			think.c \
			time.c \
			utils.c

HEADER	=	philo.h

OBJS	=	${SRCS:%.c=%.o}

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

.PHONY	:	all clean fclean re

all		:	${NAME}

%.o 	:	%.c ${HEADER}
			${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean	:
			${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all
