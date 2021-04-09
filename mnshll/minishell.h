/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:15:35 by rburton           #+#    #+#             */
/*   Updated: 2021/04/09 20:53:56 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h> //waitpid() and associated macros
# include <sys/stat.h> //stat()
# include <unistd.h> //write(), read(), close(), chdir(), fork(), getcwd(), dup()/dup2(), pipe(), pid_t
# include <fcntl.h> //open()
# include <stdlib.h> //malloc(), realloc(), free(), exit(), execve()
# include <stdio.h> //getchar(), perror(), stderror()
# include <dirent.h> //opendir(), readir(), closedir()
# include <string.h> //strerror()
# include <errno.h> //errno

typedef struct	s_smll
{
	char		**cmnd; //2x arr that contains str pieces parsed upon '|'. First line is a command and following lines (if they exist) are arguments
}				t_smll;

typedef struct	s_big
{
	t_smll		*ppln; //arr that contains str pieces parsed upon ';'. Every element is a pipeline which may consists of one or a few commands.
	char		**env; //2x arr that contains parsed environment variables
}				t_big;

//main.c


//miniprsr.c
void	mini_prsr(t_big *b, char *cmd);

//utils.c
int		ft_strcmp(char *s1, char *s2);

#endif