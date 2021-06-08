/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 21:56:14 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/08 21:56:17 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_s(t_set *s)
{
	int		pi;
	int		ci;
	int		i;

	pi = -1;
	while (++pi < s->pn)
	{
		ci = -1;
		while (++ci < s->st[pi].cn)
		{
			i = -1;
			while (++i < s->st[pi].pln[ci].n)
				if (s->st[pi].pln[ci].cmd[i] != NULL)
					free(s->st[pi].pln[ci].cmd[i]);
			if (s->st[pi].pln[ci].cmd != NULL)
				free(s->st[pi].pln[ci].cmd);
		}
		free(s->st[pi].pln);
		if (s->st[pi].fd_arr != NULL)
			ft_free_int(s->st[pi].fd_arr);
		if (s->st[pi].pid_arr != NULL)
			free(s->st[pi].pid_arr);
	}
	free(s->st);
}

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

void	catch_signal(int n)
{
	if (n == 3)
		ft_putstr_fd("Quit: 3\n", 1);
	else if (n == 2)
		write(1, "\n", 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_ter	hist;
	t_set	s;

	(void)argc;
	(void)argv;
	init_all_struct(&hist, &s, envp);
	// s = (t_set *)ft_calloc(1, sizeof(t_set));
    // make_env(s, envp); //makes env можно ли засунуть это в init_all_struct(&hist, &s)???
	signal(SIGINT, catch_signal);// могу ли засунуть в init_all_struct(&hist, &s)????
	signal(SIGQUIT, catch_signal);
	while (1)
	{
		hist.f = 0;
		write (1, "\033[35mminishell>>> \x1b[0m", 23);
		termcap_init(&hist);
		ft_user_input(&hist, &s);
	}
	return (0);
}
