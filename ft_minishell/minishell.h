/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:15:35 by rburton           #+#    #+#             */
/*   Updated: 2021/06/14 21:27:19 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <term.h>
# include <curses.h>
# include <errno.h>
# include <signal.h>

typedef struct s_cmnd
{
	char			**cmd;
	char			*cmd_tmp;
	int				n;
}					t_cmnd;

typedef struct s_ppline
{
	t_cmnd			*pln;
	char			*pln_tmp;
	int				cn;
	int				**fd_arr;
	int				*pid_arr;
}					t_ppline;

typedef struct s_dol
{
	short int		i;
	short int		q;
	short int		a;
	short int		digit_aft_dol;
	char			*path;
	char			*env_var;
	char			*full_arg;
	char			*in_env;
	char			*cont_symb;
	int				redir;
	int				red_out;
	int				red_app;
	int				red_in;
	int				redir_pipe;
	int				fd_in;
	int				fd_out;
	char			*to_file;
	char			*from_file;
}				t_dol;

typedef struct s_set
{
	t_ppline		*st;
	char			**env;
	int				pn;
	int				en;
	int				shlvl;
	int				fd_stdin;
	int				fd_stdout;
	int				cd_minus;
	t_dol			dol;
	short int		i;
}					t_set;

int	g_exit;
int	g_cycle;

typedef struct s_list
{
	char			*data;
	char			*dup;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct s_ter
{
	struct termios	term;
	int				fd;
	char			*term_name;
	int				symbols_count;
	int				f;
	int				sig_c;
	int				sig_c_new_input;
	int				empty_enter;
	t_list			*hist_list;
	t_list			*current_hist_command;
}				t_ter;

typedef struct s_pars
{
	char			*changed;
	int				n;
	char			symb1;
	char			symb2;
	char			symb3;
	char			symb4;
}				t_pars;

/*main.c*/
void					saving_inputline_to_file(t_ter *hist);
void					catch_signal(int n);
int						main(int argc, char **argv, char **envp);

/*clear.c*/
void					clear_st(t_set *s, int pi);
void					clear_fd_arr(t_set *s, int pi);
void					clear_pid_arr(t_set *s, int pi);
void					clear_dol(t_set *s);
void					clear_s(t_set *s);

/*begin.c*/
void					saving_inputline_to_file(t_ter *hist);
void					catch_signal(int n);

/*structs_init.c*/
void					termcap_init(t_ter *hist);
void					ft_parse_init(t_pars *pars);
void					init_all_struct(t_ter *hist, t_set *s, char **envp);
void					ft_dol_struct_init(t_dol *dol);
void					termcap_back(t_ter *hist);

/*utils_m.c*/
char					*ft_strndup(char *s1, int n);
int						ft_putchar(int c);
void					ft_putstr_fd(char *s, int fd);

/*termcap.c*/
void					new_input(t_ter *hist, char *buf);
int						got_key_press(char *str, t_ter *hist);
int						ft_user_input(t_ter *hist, t_set *s);

/*utils_list.c*/
t_list					*ft_lstnew(char *content);
void					ft_no_mouse(t_list *headphone, t_list *mouse);
void					delete_node(t_list **list);
void					ft_lstadd_back(t_list **list, t_list *new);

/*history_part.c*/
void					ft_next_hist_command(t_ter *hist,
							t_list *del, t_list *tmp);
void					new_command(t_ter *hist);
void					previous_command(t_ter *hist);
void					next_command(t_ter *hist);
void					elete_symbol(t_ter *hist);

/*signals.c*/
void					ft_ctrl_d(t_ter *hist);
void					ft_ctrl_c(t_ter *hist);
void					ft_end(int signal);
void					ft_sig_quit(int signal);

/*validation.c*/
int						ft_syntax_checker(char *str, int i);
void					ft_valid_input(t_ter *hist, t_set *s);

/*lexer.c*/
void					check_space_syntax(char *str, int i, int *j);
int						ft_double_check_redir(char *str, int i, int *j);
int						redir_syntax_checking(char *str, int i, int q, int a);
int						ft_syntax_validation(char *str, int i, int q, int a);
void					ft_check_quotes_lex(char *str, int i, int *q, int *a);

/*parsing.c*/
void					ft_parse_dol(t_set *s, char *str);
int						ft_parsing_2(t_dol *dol, t_set *s, char *str);
int						ft_parsing(char *input, t_set *s);

/*utils_pars_1.c*/
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
char					*ft_strchr(const char *s, int c);

/*utils_pars_2.c*/
char					*ft_memory_maker(char *s1, char *s2,
							int *lens1, int *lens2);
char					*ft_strjoin_dol(char *s1, char *s2);
char					*ft_itoa(int n);

/*utils_pars_3.c*/
char					*ft_strchr(const char *s, int c);
void					ft_parse_slash(t_dol *dol, t_set *s, char *str);
void					check_spaces(t_set *s, char *str);
char					*ft_strjoin_symb(char *s1, char symb);

/*parsing_part.c*/
void					ft_add_symb(t_dol *dol, t_set *s, char *str);
void					ft_parse_space(t_dol *dol, t_set *s, char *str);
void					ft_parse_q_slash(t_dol *dol, t_set *s, char *str);
void					ft_parse_a(t_dol *dol, t_set *s, char *str);
void					ft_parse_q(t_dol *dol, t_set *s, char *str);

/*parse_dol.c*/
int						ft_check_env(t_set *s, int j);
void					ft_not_found_in_env(t_set *s, int *len, char *str);
int						ft_check_symb_aft_dol(t_dol *dol,
							t_set *s, char *str, int *j);
void					ft_slash_in_dol(t_set *s, char *str);
void					ft_err_nmb(t_set *s);

/*redirects.c*/
void					ft_redir_get_file_name(t_set *s, t_dol *dol, char *str);
int						openning_to_file(t_dol *dol);
int						openning_from_file(t_dol *dol);
int						open_file(t_dol *dol);
int						ft_parse_redir(t_set *s, t_dol *dol, char *str);

/*redirects.c*/
void					ft_dup_filename(t_dol *dol);
void					ft_output_file(t_set *s, t_dol *dol, char *str);
void					get_file_name(t_set *s, t_dol *dol, char *str);


/*change_symb.c*/
void					ft_check_quotes(char *str, int *i, int *q, int *a);
void					ft_ret_back(t_set *s, t_pars *pars, int ci, int pi);
void					ft_return_the_symb(t_set *set, t_pars *pars);

/*main_my.c*/
void					null_tcmnd(t_cmnd *cmnd, int n);
void					shlvl(t_set *s);
void					save_stdfd(t_set *s);
void					make_env(t_set *s, char **envp);

/*prsr.c*/
void					parse_spaces(t_set *s, char *str, int si, int pi);
void					parse_pipes(t_set *s, char *str, int si);
void					parse_semicolons(t_set *s, char *str);
void					mini_prsr(t_set *s, char *cmd);

/*utils_1_1.c*/
void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t count, size_t size);
int						ft_strlen(const char *s);
int						ft_strcmp(char *s1, char *s2);
int						ft_strncmp(const char *s1, const char *s2, int n);
char					*ft_strnstr(const char *haystack,
							const char *needle, size_t len);

/*utils_1_2.c*/
void					ft_free_str(char **arr);
void					ft_free_int(int **arr);
int						words_counter(const char *str, char dlmtr);
void					parse_and_write_to_arr(char **arr,
							const char *str, char dlmtr, int wn);
char					**ft_split(char const *s, char c);

/*utils_1_3.c*/
int						ft_check_set(char smb, char const *check);
char					*ft_strtrim(char const *str, char const *set);
void					ft_strcpy(char *dst, const char *src);
char					*ft_strdup(char *s1);
char					*ft_strjoin(char const *s1, char const *s2);

/*utils_1_4.c*/
char					*ft_substr(char const *s,
							unsigned int start, size_t len);
int						w2l(int fd, char *buf, char **line);
int						get_next_line(int fd, char **line);
void					ft_putnbr(int n);

/*utils2.c*/
char					*str_in_arr(char **arr, char *str);
char					**key_in_arr(char **arr, char *key);
char					**arr2d_copy(char **arr, int en);
void					str_swap(char **arr, int i1, int i2);
void					arr2d_sorted(char **arr, int en);

/*realloc_1.c*/
void					mark_str_to_del(char **arr, char *str);
char					**ft_rlcc_del(char **arr, int nsize);
char					**ft_rlcc_add(char **arr, int nsize, char *str);
char					**unst(char **arr, int osize,
							int nsize, char **prsd_str);
void					str_ovrwrite(char **pstr, char *str);

/*realloc_2.c*/
char					**exprt(char **arr, int nsize, char *str);
char					**ft_realloc(char **arr, int osize,
							int nsize, char *str);

/*execute.c*/
int						bltn_check(t_set *s, int pi, int ci);
void					launch_mnshll(t_set *s, int pi, int ci);
void					launch_executable(t_set *s, int pi, int ci);
void					mnshll_execute(t_set *s);

/*cmnds_1.c*/
void					complete_pth(char **pth, t_set *s, int pi, int ci);
char					**split_path(t_set *s);
char					*path_checker(char **pth);
int						two_dots_counter(char *str);
int						line_counter(char **arr);

/*cmnds_2.c*/
char					*make_new_path(char **path_arr, int two_dots, int lns);
char					*path_to_verify(t_set *s, char *path);
int						path_does_exist(t_set *s, char *path);
void					process_launcher(t_set *s, int pi, int ci, char **path);
void					single_cmd_node(t_set *s, int si, int pi);

/*cmnds_3.c*/
int						rvrs_indx(t_set *s, int pi, int ci);
void					mltple_cmd_node(t_set *s, int pi, int ci);

/*builtin.c*/
void					bltn_pwd(t_set *s);
void					bltn_env(t_set *s, int pi, int ci);
int						is_number(char *str);
void					bltn_exit(t_set *s, int pi, int ci);
void					bltn_node(t_set *s, int pi, int ci);

/*bltn_cd_1.c*/
char					*cd_tilda(t_set *s);
char					*cd_minus(t_set *s, int pi, int ci);
char					*cd_home(t_set *s, int pi, int ci);
char					*cd_freepath(t_set *s, int pi, int ci);
/*bltn_cd_2.c*/
char					*set_path(t_set *s, int pi, int ci);
void					updt_pwd_assist(char **pwd_ptr, char *str1, char *str2);
void					update_pwd(t_set *s);
void					bltn_cd(t_set *s, int pi, int ci);

/*bltn_echo.c*/
int						isnt_dash_n(char *str);
int						echo_vld(t_set *s, int pi, int ci);
void					bltn_echo(t_set *s, int pi, int ci);

/*bltn_export_1.c*/
void					print_exp_line(char	**prsd_arg, int rvno_f);
void					print_exp(t_set *s);
int						key_vldtr(char *str);
char					*fill_str(char *str, int len, int offset, int trm);
char					**parse_arg(char *str);

/*bltn_export_2.c*/
void					f(char **str, char **arg, char **str_tmp);
void					key_assist(t_set *s, int pi, int ci, int i);
void					fn(t_set *s, int pi, int ci, int i);
void					bltn_export(t_set *s, int pi, int ci);
void					bltn_unset(t_set *s, int pi, int ci);

/*pipes_1.c*/
int						**make_fd_arr(t_set *s, int pi);
void					dup2protection(int	dup2rv);
void					change_fd(t_set *s, int pi, int ci);
void					wpid(t_set *s, int pi, int *pid_arr);
void					builtin_multiple_switcher(t_set *s, int pi, int ci);

/*pipes_2.c*/
int						*launch(t_set *s, int pi);
void					pipes_node(t_set *s, int si);

/*rdrct.c*/
void					rdrct_fd_fw(t_set *s);
void					rdrct_fd_rw(t_set *s);

/*error_1.c*/
void					err_message(char *error);
void					err_memory_allocation_error(void);
void					err_cmnd_not_fnd(t_set *s, int pi, int ci);
void					err_not_a_valid_id(t_set *s, int pi, int ci, int i);
void					err_home_not_set(t_set *s, int pi, int ci);
/*error_2.c*/
void					err_oldpwd_not_set(t_set *s, int pi, int ci);
void					err_no_such_file_or_directory(t_set *s, int pi, int ci);
void					err_no_such_file_or_directory_env(t_set *s,
							int pi, int ci);
void					err_numeric_arg_required(t_set *s, int pi, int ci);
void					err_too_many_arguments(t_set *s, int pi, int ci);
/*error_3.c*/
void					err_syntax_error_near_unexpected_token(t_set *s,
							int pi, int ci);
void					err_syntax_error_quotes_not_closed(void);
void					err_unxpected_backslash_at_the_end(void);
void					err_cannot_access_parent_directories(t_set *s,
							int pi, int ci);

/*utils_1_5.c*/
unsigned long long int	ovrloading_protection(
							unsigned long long int n, int sign);
int						ft_atoi(const char *str);

#endif