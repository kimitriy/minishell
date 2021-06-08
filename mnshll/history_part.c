/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 16:42:38 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/05 19:45:36 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_next_hist_command(t_ter *hist, t_list *del, t_list *tmp)
{
	del = hist->hist_list;
	while (del->next != NULL)
		del = del->next;
	if (del->data[0] == '\0')
		delete_node(&del);
	tmp = ft_lstnew(hist->current_hist_command->data);
	hist->current_hist_command->data = hist->current_hist_command->dup;
	ft_lstadd_back(&hist->hist_list, tmp);
}

void	new_command(t_ter *hist)// before void new_input(t_ter *hist)
{
	t_list	*tmp;
	t_list	*del;
	char	*dup;

	write(1, "\n", 1);
	saving_inputline_to_file(hist);
	if (hist->current_hist_command->data[0] == '\0')
	{
		hist->current_hist_command->data = hist->current_hist_command->dup;
		while (hist->current_hist_command->next)
			hist->current_hist_command = hist->current_hist_command->next;
		hist->symbols_count = 0;
		return ;
	}
	else if (hist->current_hist_command->next != NULL)
		ft_next_hist_command(hist, &del, &tmp);
	else if (hist->current_hist_command->next == NULL)
	{
		dup = ft_strdup(hist->current_hist_command->data);
		hist->current_hist_command->dup = dup;
	}
	tmp = ft_lstnew("");
	ft_lstadd_back(&hist->hist_list, tmp);
	hist->current_hist_command = tmp;
	hist->symbols_count = 0;
}

void	previous_command(t_ter *hist)
{
	int	n;

	if (hist->current_hist_command->prev != NULL)
	{
		tputs(restore_cursor, 0, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		n = ft_strlen(hist->current_hist_command->prev->data);
		write(1, hist->current_hist_command->prev->data, n);
		hist->current_hist_command = hist->current_hist_command->prev;
		hist->symbols_count = n;
	}
}

void	next_command(t_ter *hist)
{
	int	n;

	if (hist->current_hist_command->next != NULL)
	{
		tputs(restore_cursor, 0, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		n = ft_strlen(hist->current_hist_command->next->data);
		write(1, hist->current_hist_command->next->data, n);
		hist->current_hist_command = hist->current_hist_command->next;
		hist->symbols_count = n;
	}
}

void	delete_symbol(t_ter *hist)
{	
	int	n;

	n = ft_strlen(hist->current_hist_command->data);
	if (hist->symbols_count > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		hist->symbols_count--;
	}
	hist->current_hist_command->data = \
							ft_strndup(hist->current_hist_command->data, n - 1);
}
