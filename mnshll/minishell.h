/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:15:35 by rburton           #+#    #+#             */
/*   Updated: 2021/06/08 15:54:41 by smyriell         ###   ########.fr       */
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

// структура под парсер (доллар) ------------------- ДОБАВИТЬ ДИМЕ
typedef struct s_dol
{
	short int		i;// index to walk through arg
	char			*cont_symb;// вроде не использую
	short int		q;
	short int		a;
	short int		digit_aft_dol;
	char			*path;
	char			*env_var;
	// char			*tmp;
	char			*full_arg;
	char			*in_env;
	int				error;// вроде не надо
	int				redir;
	int				red_out;// флаг на >
	int				red_app;// флаг на >>
	int				red_in; // флаг на <
	int				fd_in;
	int				fd_out;
	char			*to_file; //куда записываем
	char			*from_file; //откуда читаем
}				t_dol;


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

//t_ppline *st - is an arr that contains a set of pipelines delimited upon ';' (semicolon).
//Each element is a pipeline which may consists of one or a few commands delimited by '|'.
//env - is 2d arr that contains parsed environment variables
//pn - is a number of strings in set arr (pipelines number)
//en - is a number of strings in env arr
//err - is an error code, needs to be initialised by 0
typedef struct	s_set
{
	t_ppline	*st;
	char		**env;
	int			pn;
	int			en;
	int			err;
	int			shlvl;
	t_dol		dol;
}				t_set;

//global var
int g_exit;

// структура для листа ----------------------- ДОБАВИТЬ ДИМЕ

typedef struct	s_list
{
	char			*data;
	char			*dup;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

//  структура под историю ----------------------- ДОБАВИТЬ ДИМЕ
typedef struct	s_ter
{
	struct termios	term;
	int				fd;
	char 			*term_name;
	int				symbols_count;
	int				f;
	t_list			*hist_list;
	t_list			*current_hist_command;
}				t_ter;



// структура для препарсера ----------------------ПЕРЕДЕЛАТЬ ДИМЕ
typedef struct	s_pars
{
	char			*changed;
	int				n; // количество строк в массиве с командой и аргументами 
	char			symb1;
	char			symb2;
	char			symb3;
	char			symb4;
}				t_pars;

//main.c
// int			main(int argc, char **argv, char **envp, char **apple);
int			main(int argc, char **argv, char **envp);

//main_my.c
void		null_tcmnd(t_cmnd *cmnd, int n);
void		save_argv(t_set *s, char *argv0);
void		make_env(t_set *s, char **envp);
void		make_exp(t_set *s, int n);
void		shlvl(t_set *s);
// void		make_tset(t_set *s, char **envp, char *str);
// int			main(int argc, char **argv, char **envp);

//preprsr.c
void		ft_pre_splitting(char c, int q, int a); // подменяем для сплита
void		ft_aft_splitting(char c, int q, int a); // обратная подмена после сплита
void		validation(char *str, int i);
void		lexer(char *str);

//prsr.c
void		mini_prsr(t_set *s, char *cmd);
void		parse_semicolons(t_set *s, char *str);
void		parse_pipes(t_set *s, char *str, int si);
void		parse_spaces(t_set *s, char *str, int si, int pi);

//utils1c

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_strlen(const char *s);
int			ft_strcmp(char *s1, char *s2);
//заменить! int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char 		**ft_free(char **arr);
void		ft_free_str(char **arr);
void		ft_free_int(int **arr);
int			words_counter(const char *str, char dlmtr);
void		parse_and_write_to_arr(char **arr, const char *str, char dlmtr, int wn);
char		**ft_split(char const *s, char c);
int			ft_check_set(char smb, char const *check);

char		*ft_strtrim(char const *str, char const *set);
void		ft_strcpy(char *dst, const char *src);
//заменить char		*ft_strdup(char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			w2l(int fd, char *buf, char **line);
int			get_next_line(int fd, char **line);
void		ft_putnbr(int n);
char		*ft_strchr(const char *s, int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);

//utils2.c
char		*str_in_arr(char **arr, char *str);
char		**key_in_arr(char **arr, char *key);
char		**arr2d_copy(char **arr, int en);
void		str_swap(char **arr, int i1, int i2);
void		arr2d_sorted(char **arr, int en);
// void    	write2env(t_set *s, char *field, char *str);

// realloc.c
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

//cmnds.c
void		complete_pth(char **pth, t_set *s, int pi, int ci);
char		**split_path(t_set *s);
char		*path_checker(char **pth);
void		single_cmd_node(t_set *s, int si, int pi);
int			rvrs_indx(t_set *s, int pi, int ci);
void		mltple_cmd_node(t_set *s, int pi, int ci);

// builtin.c
void		bltn_node(t_set *s, int si, int pi);
void		bltn_pwd();
void		bltn_cd(t_set *s, int si, int pi);
char		*set_path(t_set *s, int si, int pi);

// bltn_export.c
int			key_vldtr(t_set *s, int pi, int ci);
char		*fill_str(char *str, int len, int offset, int trm);
char		**parse_arg(char *str);
void		bltn_export(t_set *s, int pi, int ci);
void		bltn_unset(t_set *s, int pi, int ci);

// bltn_cd.c
char		*cd_tilda(t_set *s, int pi, int ci);
char		*cd_minus(t_set *s, int pi, int ci);
char		*cd_home(t_set *s, int pi, int ci);
char		*cd_freepath(t_set *s, int pi, int ci);
char		*set_path(t_set *s, int pi, int ci);
void		bltn_cd(t_set *s, int pi, int ci);

// bltn_echo.c
int			isnt_dash_n(char *str);
int			echo_vld(t_set *s, int pi, int ci);
void		bltn_echo(t_set *s, int pi, int ci);

//pipes.c	
int			**make_fd_arr(t_set *s, int pi);
void		change_fd(t_set *s, int pi, int ci);
void		wpid(t_set *s, int pi, int *pid_arr);
int			*launch(t_set *s, int pi);
void    	pipes_node(t_set *s, int si);

//error.c
void		err_message(char *error);
void		err_cmnd_not_fnd(t_set *s, int pi, int ci);
void		err_not_a_valid_id(t_set *s, int pi, int ci);
void		err_home_not_set(t_set *s, int pi, int ci);
void		err_oldpwd_not_set(t_set *s, int pi, int ci);
void		err_no_such_file_or_directory(t_set *s, int pi, int ci);
void		err_numeric_arg_required(t_set *s, int pi, int ci);
void		err_too_many_arguments(t_set *s, int pi, int ci);

//print.c
void		print2darr(char **arr, int exprt_f);
void		print2darr_int(int **arr);
void		print_arr_int(int *arr);
void		print_set(t_set *s);

#endif