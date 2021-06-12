/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:55:12 by rburton           #+#    #+#             */
/*   Updated: 2021/06/11 22:34:11 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**make_fd_arr(t_set *s, int pi)
{
	int		**fd_arr;
	int		ci;

	fd_arr = (int **)ft_calloc(s->st[pi].cn + 1, sizeof(int *));
	ci = 0;
	while (ci < (s->st[pi].cn - 1))
	{
		fd_arr[ci] = (int *)ft_calloc(2, sizeof(int));
		pipe(fd_arr[ci]);
		ci++;
	}
	fd_arr[ci] = NULL;
	return (fd_arr);
}

void	dup2protection(int	dup2rv)
{
	if (dup2rv == -1)
		err_message("dup2 error");
}

void	change_fd(t_set *s, int pi, int ci)
{
	int		dup2rv;

	errno = 0;
	if (ci == 0)
	{
		close(s->st[pi].fd_arr[0][0]);
		dup2rv = dup2(s->st[pi].fd_arr[0][1], 1);
		dup2protection(dup2rv);
	}
	else if (ci == s->st[pi].cn - 1)
	{
		close(s->st[pi].fd_arr[ci - 1][1]);
		dup2rv = dup2(s->st[pi].fd_arr[ci - 1][0], 0);
		close(s->st[pi].fd_arr[ci - 1][1]);
		dup2protection(dup2rv);
	}
	else
	{
		close(s->st[pi].fd_arr[ci - 1][1]);
		dup2rv = dup2(s->st[pi].fd_arr[ci - 1][0], 0);
		dup2protection(dup2rv);
		close(s->st[pi].fd_arr[ci][0]);
		dup2rv = dup2(s->st[pi].fd_arr[ci][1], 1);
		dup2protection(dup2rv);
	}
}

void	wpid(t_set *s, int pi, int *pid_arr)
{
	int		ci;
	int		status;

	ci = 0;
	while (ci < s->st[pi].cn)
	{
		waitpid(pid_arr[ci], &status, 0);
		if (status == 2 || status == 3)
			g_exit = status;
		else
			g_exit = WEXITSTATUS(status);
		ci++;
	}
}

void	builtin_multiple_switcher(t_set *s, int pi, int ci)
{
	if (bltn_check(s, pi, ci) == 1)
	{
		bltn_node(s, pi, ci);
		exit(0);
	}
	else
		mltple_cmd_node(s, pi, ci);
}
