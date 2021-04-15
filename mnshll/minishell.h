/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:15:35 by rburton           #+#    #+#             */
/*   Updated: 2021/04/15 23:16:40 by rburton          ###   ########.fr       */
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
	int			sn;
}				t_set;


//main.c
void	null_tcmnd(t_cmnd *cmnd, int n);
void	make_env(t_set *s, char **envp);
void	make_tset(t_set *s, char **envp, char *str);
int		main(int argc, char **argv, char **envp);

//miniprsr.c
void	mini_prsr(t_set *s, char *cmd);
void	parse_semicolons(t_set *s, char *str);
void	parse_pipes(t_set *s, char *str, int si);
void	parse_spaces(t_set *s, char *str, int si, int pi);

//utils.c
void	err_message(char *error);
size_t	ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
int		**give_memory(int axlr[10000][2], int w);
int		**wrd_cntr(int *wn, char const *s, char c);
char	**ft_split(char const *s, char c);
void	ft_strcpy(char *dst, const char *src);

size_t	lindx(char const *s1, char const *set);
size_t	rindx(char const *s1, char const *set);
char	*ft_strtrim(char const *s1, char const *set);

//print.c
void	print2darr(char **arr);
void	print_set(t_set *s);

#endif