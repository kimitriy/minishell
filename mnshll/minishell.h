/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:15:35 by rburton           #+#    #+#             */
/*   Updated: 2021/04/29 19:00:48 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h> //waitpid() and associated macros
# include <sys/types.h> //fork, kill
# include <sys/stat.h> //stat()
# include <unistd.h> //write(), read(), close(), chdir(), fork(), getcwd(), dup()/dup2(), pipe(), pid_t
# include <fcntl.h> //open()
# include <stdlib.h> //malloc(), realloc(), free(), exit(), execve()
# include <stdio.h> //getchar(), perror(), stderror()
# include <dirent.h> //opendir(), readir(), closedir()
# include <string.h> //strerror()
# include <term.h> //termcap
# include <curses.h> //
# include <errno.h> //errno


//char **cmnd - is a 2d char arr that contains parts of one command delimited upon ' ' (space).
//first line is always a command itself and following ones are args.
//char *cmnd_tmp - is a tmp str used to save parsed command string.
//n - is a number of strings in cmnd arr (number of args in a command).
typedef struct	s_cmnd
{
	char		**cmnd;
	char		*cmnd_tmp;
	int			n;
}				t_cmnd;

//t_cmnd *ppline - is a arr that contains a pipeline of commands delimited upon '|' (pipe).
//Each element is a command with its args wrapped in t_cmnd struct.
//char *ppln_tmp - is a tmp str used to save parsed pipeline string.
//pn - is a number of strings in ppline arr (number of commands in a pipeline)
typedef struct	s_ppline
{
	t_cmnd		*ppline;
	char		*ppln_tmp;
	int			pn;
}				t_ppline;

//t_ppline *set - is an arr that contains a set of pipelines delimited upon ';' (semicolon).
//Each element is a pipeline which may consists of one or a few commands delimited by '|'.
//env - is 2d arr that contains parsed environment variables
//sn - is a number of strings in set arr (number of pipelines)
//en - is a number of strings in env arr
typedef struct	s_set
{
	t_ppline	*set;
	char		**env;
	char		**exp;
	char		*argv0;
	int			sn;
	int			en;
}				t_set;

//main.c
// int			main(int argc, char **argv, char **envp, char **apple);
int			main(int argc, char **argv, char **envp);

//main_my.c
void		null_tcmnd(t_cmnd *cmnd, int n);
void		save_argv(t_set *s, char *argv0);
void		make_env(t_set *s, char **envp);
void		make_exp(t_set *s);
// void		make_tset(t_set *s, char **envp, char *str);
// int			main(int argc, char **argv, char **envp);

//preprsr.c
void		ft_pre_splitting(char c, int q, int a); // подменяем для сплита
void		ft_aft_splitting(char c, int q, int a); // обратная подмена после сплита
void		validation(char *str, int i);
void		lexer(char *str);

//miniprsr.c
void		mini_prsr(t_set *s, char *cmd);
void		parse_semicolons(t_set *s, char *str);
void		parse_pipes(t_set *s, char *str, int si);
void		parse_spaces(t_set *s, char *str, int si, int pi);

//utils1c

void		ft_bzero(void *s, size_t n);
int			ft_strlen(const char *s);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		**ft_split(char const *s, char c);
void		ft_strcpy(char *dst, const char *src);
size_t		lindx(char const *s1, char const *set);
size_t		rindx(char const *s1, char const *set);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strdup(char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
int			w2l(int fd, char *buf, char **line);
int			get_next_line(int fd, char **line);

//utils2.c
void		err_message(char *error);
char		*str_in_arr(char **arr, char *str);
char		**arr2d_copy(char **arr, int en);
void		arr2d_sorted(char **arr, int en);
void    	write2env(t_set *s, char *field, char *str);

//execute.c
void		mnshll_execute(t_set *s);

//builtin.c
void		bltn_node(t_set *s, int si, int pi);
void		bltn_pwd();
void		bltn_cd(t_set *s, int si, int pi);
char		*set_path(t_set *s, int si, int pi);

//cmnd.c
void		cmnd_node(t_set *s, int si, int pi);


//print.c
void		print2darr(char **arr, int exprt_f);
void		print_set(t_set *s);

#endif