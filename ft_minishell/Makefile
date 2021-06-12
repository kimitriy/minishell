# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburton <rburton@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/28 11:32:38 by rburton           #+#    #+#              #
#    Updated: 2021/06/12 03:28:29 by rburton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

HEADER		= minishell.h

SRC 		= 	main.c \
				main_my.c \
				prsr.c \
				utils_1_1.c \
				utils_1_2.c \
				utils_1_3.c \
				utils_1_4.c \
				utils_1_5.c \
				utils_2.c \
				realloc_1.c \
				realloc_2.c \
				execute.c \
				bltns.c \
				bltn_export_1.c \
				bltn_export_2.c \
				bltn_cd_1.c \
				bltn_cd_2.c \
				bltn_echo.c \
				cmnds_1.c \
				cmnds_2.c \
				cmnds_3.c \
				pipes_1.c \
				pipes_2.c \
				rdrct.c \
				error_1.c \
				error_2.c \
				error_3.c \
				utils_m.c \
				structs_init.c \
				termcap.c \
				history_part.c \
				utils_list.c \
				signals.c \
				validation.c \
				lexer.c \
				parsing.c \
				parsing_part.c \
				parse_dol.c \
				utils_pars_1.c \
				utils_pars_2.c \
				utils_pars_3.c \
				redirects.c \
				redirects1.c \
				change_symb.c \
				
				

TERM		= -ltermcap

OBJS		= ${SRC:.c=.o}

GCC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror

RM			= rm -f

all:		${NAME}

.c.o:		
				${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS} ${HEADER}
				${GCC} ${CFLAGS} -o ${NAME} ${TERM} ${OBJS}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}
		${RM} ${LIB}

re:		fclean all