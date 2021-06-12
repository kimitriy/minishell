/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:29:58 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/12 03:23:50 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_symbol(t_ter *hist)
{	
	int		n;
	char	*tmp;

	n = ft_strlen(hist->current_hist_command->data);
	if (hist->symbols_count > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		hist->symbols_count--;
	}
	tmp = ft_strdup(hist->current_hist_command->data);
	if (hist->current_hist_command->data[0] != '\0')
		free(hist->current_hist_command->data);
	hist->current_hist_command->data = \
							ft_strndup(tmp, n - 1);
	free(tmp);
}

void	new_input(t_ter *hist, char *buf)
{
	char	*tmp;

	if (hist->sig_c)
	{
		hist->current_hist_command->data = ft_strdup("");
		hist->sig_c = 0;
	}
	tmp = ft_strdup(hist->current_hist_command->data);
	if (hist->current_hist_command->data[0] != '\0')
		free(hist->current_hist_command->data);
	hist->current_hist_command->data = ft_strjoin(tmp, buf);
	free(tmp);
	write(1, buf, ft_strlen(buf));
	hist->symbols_count = ft_strlen(hist->current_hist_command->data);
}

int	got_key_press(char *str, t_ter *hist)
{
	if (!ft_strcmp(str, "\e[A"))
		previous_command(hist);
	else if (!ft_strcmp(str, "\e[B"))
		next_command(hist);
	else if (!ft_strcmp(str, "\177"))
		delete_symbol(hist);
	else if (!ft_strcmp(str, "\4"))
		ft_ctrl_d(hist);
	else if (!ft_strcmp(str, "\3"))
	{
		ft_ctrl_c(hist);
		return (1);
	}
	else if (!ft_strcmp(str, "\e[C"))
		return (0);
	else if (!ft_strcmp(str, "\e[D"))
		return (0);
	else if (ft_strcmp(str, "\n"))
		new_input(hist, str);
	else
	{
		new_command(hist);
		return (1);
	}
	return (0);
}

int	ft_user_input(t_ter *hist, t_set *s)
{
	char	str[21];
	int		len;

	hist->symbols_count = 0;
	tgetent(0, "xterm-256color");
	tputs(save_cursor, 1, ft_putchar);
	while (1)
	{
		len = read(0, str, 20);
		if (len == -1)
		{
			err_message("Error of User input_str reading");
			return (1);
		}
		str[len] = 0;
		if (got_key_press(str, hist))
			break ;
	}
	if (hist->sig_c || (hist->current_hist_command->data[0] == '\0' \
		&& hist->current_hist_command->prev == NULL) || hist->empty_enter == 1)
		return (1);
	ft_valid_input(hist, s);
	return (0);
}
