/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:04:18 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/16 01:43:27 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	termcap_init(t_ter *hist)
{
	if (hist->f == 0)
	{
		hist->symbols_count = 0;
		tcgetattr(0, &hist->term1);
		tcgetattr(0, &hist->term);
		hist->term.c_lflag &= ~(ECHO);
		hist->term.c_lflag &= ~(ICANON);
		hist->term.c_lflag &= ~(ISIG);
		tcsetattr(0, TCSANOW, &hist->term);
	}
	else
	{
		hist->term = hist->term1;
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
	s->cd_minus = 0;
	s->i = 0;
	make_env(s, envp);
	hist->hist_list = ft_lstnew("");
	hist->sig_c = 0;
	hist->sig_c_new_input = 0;
	hist->empty_enter = 0;
	hist->cur_hist_command = hist->hist_list;
	s->fd_true_in = dup(0);
	s->fd_true_out = dup(1);
}

void	ft_dol_struct_init(t_dol *dol)
{
	dol->a = 0;
	dol->q = 0;
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
