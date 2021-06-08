/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:04:18 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/08 20:15:18 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	termcap_init(t_ter *hist)
{
	if (hist->f == 0)
	{
		tgetent(0, hist->term_name);// было раньше в начале ft_input
		tputs(save_cursor, 1, ft_putchar);// было раньше в начале ft_input
		hist->symbols_count = 0;
		tcgetattr(0, &hist->term);
		hist->term.c_lflag &= ~(ECHO);
		hist->term.c_lflag &= ~(ICANON);
		hist->term.c_lflag &= ~(ISIG);
		tcsetattr(0, TCSANOW, &hist->term);
	}
	else
	{
		tcgetattr(0, &hist->term);
		hist->term.c_lflag |= ~(ECHO);
		hist->term.c_lflag |= ~(ICANON);
		hist->term.c_lflag |= ~(ISIG);
		tcsetattr(0, TCSANOW, &hist->term);
	}
}

void	ft_parse_init(t_pars *pars)
{
	pars->symb1 = ' ';
	pars->symb2 = -1;
	pars->symb3 = '|';
	pars->symb4 = -2;
}

void	init_all_struct(t_ter *hist, t_set *s, char **envp)
{
	s = (t_set *)ft_calloc(1, sizeof(t_set));// ?????? need???
    make_env(s, envp); //makes env можно ли засунуть это в init_all_struct(&hist, &s)???
	hist->hist_list = ft_lstnew("");
	hist->current_hist_command = hist->hist_list;
}

void	ft_dol_struct_init(t_dol *dol)
{
	dol->a = 0;
	dol->q = 0;
	dol->i = 0;
	dol->error = 0;
	dol->full_arg = ft_strdup("");
	dol->path = NULL;
	dol->digit_aft_dol = 0;
	dol->red_out = 0;
	dol->red_app = 0;
	dol->red_in = 0;
	dol->redir_pipe = 0;
	dol->fd_out = -2;
	dol->fd_in = -2;
	dol->redir = 0;
	dol->cont_symb = "$\\\'\"";
}
