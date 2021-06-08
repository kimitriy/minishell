//******* begin.c ********

void	saving_inputline_to_file(t_ter *hist);
void	catch_signal(int n);

//******* structs_init.c  ********

void	termcap_init(t_ter *hist);
void	ft_parse_init(t_pars *pars);
void	init_all_struct(t_ter *hist, t_set *s, char **envp);
void	ft_dol_struct_init(t_dol *dol);

//******* utils_m.c  ********

char	*ft_strndup(char *s1, int n);
int		ft_putchar(int c);
void	ft_putstr_fd(char *s, int fd);

//******* termcap.c  ********

void	new_input(t_ter *hist, char *buf);
int		got_key_press(char *str, t_ter *hist);
void	ft_user_input(t_ter *hist, t_set *s);

//******* utils_list.c  ********

t_list	*ft_lstnew(char *content);
void	ft_no_mouse(t_list *headphone, t_list *mouse);
void	delete_node(t_list **list);
void	ft_lstadd_back(t_list **list, t_list *new);

//******* history_part.c  ********

void	ft_next_hist_command(t_ter *hist, t_list *del, t_list *tmp);
void	new_command(t_ter *hist);
void	previous_command(t_ter *hist);
void	next_command(t_ter *hist);
void	delete_symbol(t_ter *hist);

//******* signals.c  ********

void	ft_ctrl_d(t_ter *hist);
void	ft_ctrl_c(t_ter *hist);

//******* validation.c    ********

int		ft_syntax_checker(char *str, int i);
void	ft_valid_input(t_ter *hist, t_set *s);

//******* lexer.c   ********

void	check_space_syntax(char *str, int i, int *j);
int		ft_double_check_redir(char *str, int i, int *j);
int		redir_syntax_checking(char *str, int i, int q, int a);
int		ft_syntax_validation(char *str, int i, int q, int a);
void	ft_check_quotes_lex(char *str, int i, int *q, int *a);

//*******   parsing.c     ********

void	ft_parse_dol(t_set *s, char *str);
int		ft_parsing_2(t_dol *dol, t_set *s, char *str);
int		ft_parsing(char *input, t_set *s);

//*******  utils_pars_1.c     ********

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);

//*******  utils_pars_2.c     ********

char	*ft_memory_maker(char *s1, char *s2, int *lens1, int lens2);
char	*ft_strjoin_dol(char *s1, char *s2);
// static	int	size(int n);
char	*ft_itoa(int n);

//*******  utils_pars_3.c     ********

char	*ft_strchr(const char *s, int c);
void	ft_parse_slash(t_dol *dol, char *str);
void	check_spaces(t_dol *dol, char *str);
char	*ft_strjoin_symb(char *s1, char symb);

//*******  parsing_part.c     ********

void 	ft_add_symb(t_dol *dol, char *str);
void	ft_parse_space(t_dol *dol, char *str);
void	ft_parse_q_slash(t_dol *dol, char *str);
void	ft_parse_a(t_dol *dol, char *str);
void	ft_parse_q(t_dol *dol, t_set *s, char *str);

//*******  parse_dol.c     ********

int		ft_check_env(t_set *s, int j);
void	ft_not_found_in_env(t_set *s, int *len);
int		ft_check_symb_aft_dol(t_dol *dol, char *str, int *j);
void	ft_slash_in_dol(t_set *s, char *tmp);
void	ft_err_nmb(t_set *s, char *str, char *tmp);

//*******      redirects.c      ********

void	ft_redir_get_file_name(t_dol *dol, char *str);
int		openning_to_file(t_dol *dol);
int		openning_from_file(t_dol *dol);
int		open_file(t_dol *dol);
int		ft_parse_redir(t_dol *dol, char *str);

//*******     change_symb.c  ********
void	ft_check_quotes(char *str, int *i, int *q, int *a);
void	ft_change_the_symb(char *str, t_pars *pars);
void	ft_ret_back(char *str, t_pars *pars, int ci, int pi);
void	ft_return_the_symb(t_set *set, t_pars *pars);


//ADD TO MAKEFILE

begin -> to main.c \
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
change_symb.c \

// CHANGE THIS STRUCT

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

// структура под парсер (доллар) ------------------- ДОБАВИТЬ ДИМЕ
typedef struct s_dol
{
	short int		i;// index to walk through arg
	// char			*cont_symb;// вроде не использую
	short int		q;
	short int		a;
	short int		digit_aft_dol;
	char			*path;
	char			*env_var;
	// char			*tmp;
	char			*full_arg;
	char			*in_env;
	// int				error;// вроде не надо
	int				redir;
	int				red_out;// флаг на >
	int				red_app;// флаг на >>
	int				red_in; // флаг на <
	int				fd_in;
	int				fd_out;
	char			*to_file; //куда записываем
	char			*from_file; //откуда читаем
}				t_dol;

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