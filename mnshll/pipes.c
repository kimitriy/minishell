/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:55:12 by rburton           #+#    #+#             */
/*   Updated: 2021/05/06 22:45:34 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		**make_fd_arr(t_set *s, int pi)
{
	int     **arr;
	int     ci; //command indx

	arr = (int**)malloc(s->set[pi].cn * sizeof(int*));
	if (NULL == arr)
		err_message("fd_arr malloc error");
	ci = 0;
	printf("CMD COUNT: %d\n", s->set[pi].cn);
	while (ci < s->set[pi].cn)
    {
		arr[ci] = (int*)malloc(2 * sizeof(int));
		pipe(arr[ci]);
		printf("PIPE FD[%d][0]: %d, FD[%d][1]: %d\n", ci, arr[ci][0], ci, arr[ci][1]);
		ci++;
	}
	arr[ci] = NULL;
	// print2darr_int(arr);
	return(arr);
}

void	change_fd(t_set *s, int pi, int ci)
{
	int		tmp1;
	int		tmp0;

	if (ci == 0)
	{
		close(s->set[pi].fd_arr[ci][0]);
		dup2(s->set[pi].fd_arr[ci][1], 1);
	}
	else if (ci + 1 == s->set[pi].cn)
	{
		close(s->set[pi].fd_arr[ci][1]);
		dup2(s->set[pi].fd_arr[ci - 1][0], 0);
	}
	else
	{
		tmp1 = dup2(s->set[pi].fd_arr[ci][1], 1);
		tmp0 = dup2(s->set[pi].fd_arr[ci - 1][0], 0);
		if (tmp1 == -1 || tmp0 == -1)
			err_message("dup2 error");
	}
}

int		*launch(t_set *s, int pi)
{
	int		*arr;
	int		ci; //command indx
	pid_t	pid;
	int		status;

	arr = (int*)malloc(s->set[pi].cn * sizeof(int));
	if (NULL == arr)
		err_message("fd_arr malloc error");
	ci = 0;
	while (ci < s->set[pi].cn)
	{
		pid = fork();
		
		if (pid > 0)
		{
			arr[ci] = pid;
			close(s->set[pi].fd_arr[ci][1]);
		}
		else if (pid == 0)
		{
			change_fd(s, pi, ci);
			if (bltn_check(s, pi, ci) == 1)
			{	
				bltn_node(s, pi, ci);
				write(1, "built", 5);
			}
			else
			{	
				mltple_cmnd_node(s, pi, ci);
				write(1, "cmnd", 4);
			}
		}
		else
			err_message("fork() error");
		ci++;
	}
	ci = 0;
	while (ci < s->set[pi].cn)
	{
		waitpid(arr[ci], &status, 0);
	}
	print_arr_int(arr);
	return (arr);
}

void	pipes_node(t_set *s, int pi)
{
	// write(1, "pipes_node has been reached\n", 29);

	s->set[pi].fd_arr = make_fd_arr(s, pi);
    s->set[pi].pid_arr = launch(s, pi);
}