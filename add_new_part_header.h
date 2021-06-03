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

// структура для препарсера ----------------------Добавить ДИМЕ
typedef struct	s_pars
{
	char			*changed;
	char			*returned;
	short int		q;
	short int		a;
	char			symb1;
	char			symb2;
	char			symb3;
	char			symb4;
}				t_pars;