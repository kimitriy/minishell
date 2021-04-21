# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburton <rburton@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/28 11:32:38 by rburton           #+#    #+#              #
#    Updated: 2021/04/21 20:38:17 by rburton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

HEADER		= minishell.h

SRC 		= 	main.c \
				main_my.c \
				preprsr.c \
				prsr.c \
				utils1.c \
				utils2.c \
				execute.c \
				bltns.c \
				cmnd.c \
				print.c \

OBJS		= ${SRC:.c=.o}

GCC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror

RM			= rm -f

all:		${NAME}

.c.o:		
				${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS} ${HEADER}
				${GCC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}
		${RM} ${LIB}

re:		fclean all