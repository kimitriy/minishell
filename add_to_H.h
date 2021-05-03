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
	t_list			*hist_list;
	t_list			*current_hist_command;
}				t_ter;