/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 16:42:38 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/15 22:14:13 by rburton          ###   ########.fr       */
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
	tmp = ft_lstnew(hist->cur_hist_command->data);
	hist->cur_hist_command->data = ft_strdup(hist->cur_hist_command->dup);
	ft_lstadd_back(&hist->hist_list, tmp);
}

void	ft_more_functions(t_ter *hist, t_list *tmp)
{
	tmp = ft_lstnew("");
	ft_lstadd_back(&hist->hist_list, tmp);
	hist->cur_hist_command = tmp;
	hist->symbols_count = 0;
}

void	new_command(t_ter *hist)
{
	t_list	*tmp;
	t_list	*del;

	del = NULL;
	tmp = NULL;
	write(1, "\n", 1);
	saving_inputline_to_file(hist);
	if (hist->cur_hist_command->data[0] == '\0')
	{
		hist->cur_hist_command->data = hist->cur_hist_command->dup;
		while (hist->cur_hist_command->next)
			hist->cur_hist_command = hist->cur_hist_command->next;
		hist->symbols_count = 0;
		hist->empty_enter = 1;
		return ;
	}
	else if (hist->cur_hist_command->next != NULL)
		ft_next_hist_command(hist, del, tmp);
	else if (hist->cur_hist_command->next == NULL)
		hist->cur_hist_command->dup = ft_strdup(hist->cur_hist_command->data);
	tmp = ft_lstnew("");
	ft_lstadd_back(&hist->hist_list, tmp);
	hist->cur_hist_command = tmp;
	hist->symbols_count = 0;
}

void	previous_command(t_ter *hist)
{
	int	n;

	if (hist->cur_hist_command->prev != NULL)
	{
		tputs(restore_cursor, 0, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		n = ft_strlen(hist->cur_hist_command->prev->data);
		write(1, hist->cur_hist_command->prev->data, n);
		hist->cur_hist_command = hist->cur_hist_command->prev;
		hist->symbols_count = n;
	}
}

void	next_command(t_ter *hist)
{
	int	n;

	if (hist->cur_hist_command->next != NULL)
	{
		tputs(restore_cursor, 0, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		n = ft_strlen(hist->cur_hist_command->next->data);
		write(1, hist->cur_hist_command->next->data, n);
		hist->cur_hist_command = hist->cur_hist_command->next;
		hist->symbols_count = n;
	}
}
