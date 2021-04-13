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

//pline - is a 2d arr that contains str pieces parsed upon '|' (commands).
//lines are parts (commands) a pipeline consists from.
//first element in a line is a command itself and following ones (if they exist) are arguments
typedef struct	s_smll
{
	char		**pline;
}				t_smll;


//set - is an arr that contains str pieces parsed upon ';' (pipelines).
//every element is a pipeline which may consists of one or a few commands delimited by '|'.
//env - is 2d arr that contains parsed environment variables
typedef struct	s_big
{
	t_smll		*set;
	char		**env; 
}				t_big;

//main.c


//miniprsr.c
void	mini_prsr(t_big *b, char *cmd);

//utils.c
int		ft_strcmp(char *s1, char *s2);

#endif