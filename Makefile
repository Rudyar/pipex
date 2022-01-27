# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arudy <arudy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 10:42:59 by arudy             #+#    #+#              #
#    Updated: 2022/01/27 12:28:36 by arudy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = $(addprefix srcs/, main.c utils.c path.c \
		path_utils.c ft_split.c pipex.c errors.c )

OBJS = ${SRCS:.c=.o}

NAME = pipex

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

all: ${NAME}

${NAME}:	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
