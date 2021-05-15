/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:15:35 by rburton           #+#    #+#             */
/*   Updated: 2021/05/15 13:29:47 by rburton          ###   ########.fr       */
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
	char		**cmd;
	char		*cmd_tmp;
	int			n;
}				t_cmnd;

//t_cmnd *ppline - is a arr that contains a pipeline of commands delimited upon '|' (pipe).
//Each element is a command with its args wrapped in t_cmnd struct.
//char *ppln_tmp - is a tmp str used to save parsed pipeline string.
//cn - is a number of strings in ppln arr (number of commands in a pipeline)
typedef struct	s_ppline
{
	t_cmnd		*pln;
	char		*pln_tmp;
	int			cn;
	int			**fd_arr;
	int			*pid_arr;
}				t_ppline;

//t_ppline *set - is an arr that contains a set of pipelines delimited upon ';' (semicolon).
//Each element is a pipeline which may consists of one or a few commands delimited by '|'.
//env - is 2d arr that contains parsed environment variables
//sn - is a number of strings in set arr (number of pipelines)
//en - is a number of strings in env arr
//exn - is a number of strings in exp arr
//err - is an error code, needs to be initialised by 0
typedef struct	s_set
{
	t_ppline	*st;
	char		**env;
	char		**exp;
	// char		*argv0;
	int			pn;
	int			en;
	int			exn;
	int			err;
}				t_set;

//main.c
// int			main(int argc, char **argv, char **envp, char **apple);
int			main(int argc, char **argv, char **envp);

//main_my.c
void		null_tcmnd(t_cmnd *cmnd, int n);
void		save_argv(t_set *s, char *argv0);
void		make_env(t_set *s, char **envp);
void		make_exp(t_set *s, int n);
// void		make_tset(t_set *s, char **envp, char *str);
// int			main(int argc, char **argv, char **envp);

//preprsr.c
void		ft_pre_splitting(char c, int q, int a); // подменяем для сплита
void		ft_aft_splitting(char c, int q, int a); // обратная подмена после сплита
void		validation(char *str, int i);
void		lexer(char *str);

//miniprsr.chan
void		mini_prsr(t_set *s, char *cmd);
void		parse_semicolons(t_set *s, char *str);
void		parse_pipes(t_set *s, char *str, int si);
void		parse_spaces(t_set *s, char *str, int si, int pi);

//utils1c

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_strlen(const char *s);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		**ft_free(char **arr);
char		**ft_free_j(char **arr, int j);
char		*ft_word(char const *s, char c);
int			ft_num(char const *s, char c);
char		**ft_split(char const *s, char c);

size_t		lindx(char const *s1, char const *set);
size_t		rindx(char const *s1, char const *set);
char		*ft_strtrim(char const *s1, char const *set);
void		ft_strcpy(char *dst, const char *src);
char		*ft_strdup(char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
int			w2l(int fd, char *buf, char **line);
int			get_next_line(int fd, char **line);
void		ft_putnbr(int n);
char		*ft_strchr(const char *s, int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);

//utils2.c
char		*str_in_arr(char **arr, char *str);
char		**key_in_arr(char **arr, char *key);
char		**arr2d_copy(char **arr, int en);
void		str_swap(char **arr, int i1, int i2);
void		arr2d_sorted(char **arr, int en);
void    	write2env(t_set *s, char *field, char *str);

//realloc.c
void		mark_str_to_del(char **arr, char *str);
char		**ft_rlcc_del(char **arr, int nsize);
char		**ft_rlcc_add(char **arr, int nsize, char *str);
char		**unst(char **arr, int osize, int nsize, char **prsd_str);
void		str_ovrwrite(char **pstr, char *str);
char		**exprt(char **arr, int nsize, char *str);
char		**ft_realloc(char **arr, int osize, int nsize, char *str);

//execute.c
int			bltn_check(t_set *s, int pi, int ci);
void		mnshll_execute(t_set *s);

//builtin.c
void		bltn_node(t_set *s, int si, int pi);
void		bltn_pwd();
void		bltn_cd(t_set *s, int si, int pi);
char		*set_path(t_set *s, int si, int pi);

//bltn_export.c
int			key_vldtr(t_set *s, int pi, int ci);
char		*fill_str(char *str, int len, int offset, int trm);
char		**parse_arg(char *str);
void		bltn_export(t_set *s, int pi, int ci);
void		bltn_unset(t_set *s, int pi, int ci);

//bltn_cd.c
char		*cd_tilda(t_set *s, int pi, int ci);
char		*cd_minus(t_set *s, int pi, int ci);
char		*cd_home(t_set *s, int pi, int ci);
char		*cd_freepath(t_set *s, int pi, int ci);
char		*set_path(t_set *s, int pi, int ci);
void		bltn_cd(t_set *s, int pi, int ci);

//cmnd.c
void		single_cmd_node(t_set *s, int si, int pi);
void		mltple_cmd_node(t_set *s, int pi, int ci);

//pipes.c	
int			**make_fd_arr(t_set *s, int pi);
void		change_fd(t_set *s, int pi, int ci);
int			*launch(t_set *s, int pi);
void    	pipes_node(t_set *s, int si);

//error.c
void		err_message(char *error);
void		err_cmnd_not_fnd(t_set *s, int pi, int ci);
void		err_not_a_valid_id(t_set *s, int pi, int ci);
void		err_home_not_set(t_set *s, int pi, int ci);
void		err_oldpwd_not_set(t_set *s, int pi, int ci);

//print.c
void		print2darr(char **arr, int exprt_f);
void		print2darr_int(int **arr);
void		print_arr_int(int *arr);
void		print_set(t_set *s);

#endif