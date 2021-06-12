/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:55:12 by rburton           #+#    #+#             */
/*   Updated: 2021/06/11 22:34:19 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*launch(t_set *s, int pi)
{
	int		*arr;
	int		ci;
	pid_t	pid;

	arr = (int *)ft_calloc(s->st[pi].cn, sizeof(int));
	ci = -1;
	while (++ci < s->st[pi].cn)
	{
		pid = fork();
		if (pid > 0)
		{
			arr[ci] = pid;
			if (ci < s->st[pi].cn - 1)
				close(s->st[pi].fd_arr[ci][1]);
		}
		else if (pid == 0)
		{
			change_fd(s, pi, ci);
			builtin_multiple_switcher(s, pi, ci);
		}
		else
			err_message("fork() error");
	}
	wpid(s, pi, arr);
	return (arr);
}

void	pipes_node(t_set *s, int pi)
{
	s->st[pi].fd_arr = make_fd_arr(s, pi);
	s->st[pi].pid_arr = launch(s, pi);
}
