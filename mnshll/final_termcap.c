/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_termcap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:31:31 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/08 15:20:53 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_input(t_ter *hist, char *buf) //before void	new_command(t_ter *hist, char *buf)
{
	char	*tmp;
	char	*tmp_dup;

	tmp = hist->current_hist_command->data;
	hist->current_hist_command->data = ft_strjoin(tmp, buf);
	if (tmp[0] != '\0')
		free(tmp);
	write(1, buf, ft_strlen(buf));
	hist->symbols_count = ft_strlen(hist->current_hist_command->data);
}

void	ft_ctrl_d(t_ter *hist)
{
	if (hist->current_hist_command->data[0] == '\0')
	{
		write(2, "exit\n", 5);
		exit(g_exit);// exit + в аргумент статус выхода g_exit(если ошибка 1(cd, unset если не отрабатывают, возвр 1) или 0 (execve без ошибок), проверить на команду если нет 127, chmode 126), если маллок то статус ошибки = 2, )
	}
}

void	ft_ctrl_c(t_ter *hist)
{
	free(hist->current_hist_command->data);
	free(hist->current_hist_command->dup);//  надо ли чистить??
	hist->current_hist_command->data = ft_strdup("");
	g_exit = 1;
	write(1, "\n", 1); //TODO наверное нужно будет почистить че-нить еще)))
}

int	got_key_press(char *str, t_ter *hist)
{
	if (!ft_strcmp(str, "\e[A"))
		previous_command(hist);
	else if (!ft_strcmp(str, "\e[B"))
		next_command(hist);
	else if (!ft_strcmp(str, "\177"))
		delete_symbol(hist);
	else if (!ft_strcmp(str, "\4")) // ctrl-d
		ft_ctrl_d(hist);
	else if (!ft_strcmp(str, "\3"))// ctrl-c
	{
		ft_ctrl_c(hist);
		return (1);
	}
	else if (!ft_strcmp(str, "\e[C")) // vlevo ili vpravo
		continue ;
	else if (!ft_strcmp(str, "\e[D")) // vlevo ili vpravo
		continue ;
	else if (ft_strcmp(str, "\n"))
		new_input(hist, str);
	else
	{
		new_command(hist);
		return (1);
	}
	return (0);
}

void	ft_user_input(t_ter *hist, t_set *s)
{
	char	str[21];
	int		len;

	// hist->symbols_count = 0;// переделать ?? закинула эту часть в термкап инит
	// tgetent(0, hist->term_name); // закинула в термкап инит
	// tputs(save_cursor, 1, ft_putchar); // закинула в термкап инит
	while (1)
	{
		len = read(0, str, 20);
		if (len == -1)
		{
			err_message("Error of User input_str reading");
			return ;
		}
		str[len] = 0;
		if (got_key_press(str, hist))
			break ;
	}
	hist->f = 1;
	termcap_init(hist);
	ft_valid_input(hist, s); // здесь думай нужна ли ft_valid_input(hist, s) интовой или можно сделать войдовской
}
