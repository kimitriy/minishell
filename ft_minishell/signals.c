/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:33:23 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/11 22:00:14 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_d(t_ter *hist)
{
	if (hist->current_hist_command->data[0] == '\0')
	{
		write(2, "exit\n", 5);
		exit(g_exit);
	}
}

void	ft_ctrl_c(t_ter *hist)
{
	if (hist->current_hist_command->data[0] != '\0')
		free(hist->current_hist_command->data);
	hist->sig_c = 1;
	hist->sig_c_new_input = 1;
	g_exit = 1;
	write(1, "\n", 1);
}

void	ft_end(int signal)
{
	int	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (!pid)
	{
		ft_putstr_fd("\n", 1);
		kill(1, SIGINT);
	}
	else
	{
		ft_putstr_fd("\n", 1);
		write (1, "\033[35mminishell>>> \x1b[0m", 22);
	}
	(void)signal;
}

void	ft_sig_quit(int signal)
{
	int	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (!pid)
		ft_putstr_fd("Quit: 3\n", 1);
	(void)signal;
}
