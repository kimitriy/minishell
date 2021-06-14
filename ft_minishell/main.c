/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:44:53 by rburton           #+#    #+#             */
/*   Updated: 2021/06/14 19:02:58 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	saving_inputline_to_file(t_ter *hist)
{
	int		i;
	int		n;
	char	*str;

	n = ft_strlen(hist->current_hist_command->data);
	hist->fd = open("History_file", O_CREAT | O_APPEND | O_RDWR, 0666);
	if (!hist->fd)
		err_message("History_file openning/creation error");
	str = ft_strjoin(hist->current_hist_command->data, "\n");
	n = ft_strlen(str);
	i = write(hist->fd, str, n);
	if (i == -1)
		write(1, "writing str_input to file error", 32);
	free(str);
	close(hist->fd);
}

int	main(int argc, char **argv, char **envp)
{
	t_ter	hist;
	t_set	*s;

	g_cycle = 0;
	(void)argc;
	(void)argv;
	s = (t_set *)ft_calloc(1, sizeof(t_set));
	init_all_struct(&hist, s, envp);
	signal(SIGINT, ft_end);
	signal(SIGQUIT, ft_sig_quit);
	while (1)
	{
		hist.symbols_count = 0;
		hist.f = 0;
		s->i = 0;
		hist.empty_enter = 0;
		write (1, "\033[35mminishell>>> \x1b[0m", 23);
		termcap_init(&hist);
		ft_user_input(&hist, s);
	}
	return (0);
}
