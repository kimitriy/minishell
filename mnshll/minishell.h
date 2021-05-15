/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:15:35 by rburton           #+#    #+#             */
/*   Updated: 2021/05/15 03:02:45 by smyriell         ###   ########.fr       */
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
# include <term.h> //
# include <curses.h> //
# include <errno.h> //errno
# include <termios.h>


//char **cmnd - is a 2d char arr that contains parts of one command delimited upon ' ' (space).
//first line is always a command itself and following ones are args.
//char *cmnd_tmp - is a tmp str used to save parsed command string.
//n - is an arr counter.
typedef struct	s_cmnd
{
	char		**cmnd;
	char		*cmnd_tmp;
	int			n;
}				t_cmnd;

//t_cmnd *ppline - is a arr that contains a pipeline of commands delimited upon '|' (pipe).
//Each element is a command with its args wrapped in t_cmnd struct.
//char *ppln_tmp - is a tmp str used to save parsed pipeline string.
//n - is an arr counter.
typedef struct	s_ppline
{
	t_cmnd		*ppline;
	char		*ppln_tmp;
	int			pn;
}				t_ppline;

//t_ppline *set - is an arr that contains a set of pipelines delimited upon ';' (semicolon).
//Each element is a pipeline which may consists of one or a few commands delimited by '|'.
//env - is 2d arr that contains parsed environment variables
//n - is an arr counter.
typedef struct	s_set
{
	t_ppline	*set;
	char		**env;
	char		**exp;
	int			sn;
	int			en;
}				t_set;


//______________________

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

// структура под парсер (доллар) ------------------- ДОБАВИТЬ ДИМЕ
typedef struct s_dol
{
	short int		i;// index to walk through arg
	char			*cont_symb;
	short int		q;
	short int		a;
	short int		digit_aft_dol;
	char			*path;
	char			*env_var;
	// char			*tmp;
	char			*full_arg;
	char			*in_env;
	int				error;
	int				redir;
	int				red_out;// флаг на >
	int				red_app;// флаг на >>
	int				red_in; // флаг на <
	int				fd_in;
	int				fd_out;
	char			*to_file; //куда записываем
	char			*from_file; //откуда читаем
}				t_dol;

//main.c
// int			main(int argc, char **argv, char **envp, char **apple);
// int			main(int argc, char **argv, char **envp);

//main_my.c
void		null_tcmnd(t_cmnd *cmnd, int n);
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
// int			ft_strcmp(char *s1, char *s2);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		**ft_split(char const *s, char c);
void		ft_strcpy(char *dst, const char *src);
size_t		lindx(char const *s1, char const *set);
size_t		rindx(char const *s1, char const *set);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char *s2);
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
void		bltn_node(t_set *s);
void		bltn_pwd();
void		bltn_cd(t_set *s, int si, int pi);
char		*set_path(t_set *s, int si, int pi);

//cmnd.c
void		cmnd_node(t_set *s);


//print.c
void		print2darr(char **arr, int exprt_f);
void		print_set(t_set *s);

#endif
