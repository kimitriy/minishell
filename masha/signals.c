/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:33:23 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/08 17:33:54 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
