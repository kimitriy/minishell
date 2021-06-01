/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:55:12 by rburton           #+#    #+#             */
/*   Updated: 2021/06/01 17:39:20 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		**make_fd_arr(t_set *s, int pi)
{
	int     **fd_arr;
	int     ci; //command indx
 
	fd_arr = (int**)ft_calloc(s->st[pi].cn + 1, sizeof(int*)); //command number - 1 (number of pipes) + 1 (for NULL)
	ci = 0;
	while (ci < (s->st[pi].cn - 1))
    {
		fd_arr[ci] = (int*)ft_calloc(2, sizeof(int));
		pipe(fd_arr[ci]);
		printf("PIPE FD[%d][0]: %d, FD[%d][1]: %d\n", ci, fd_arr[ci][0], ci, fd_arr[ci][1]);
		ci++;
	}
	fd_arr[ci] = NULL;
	return(fd_arr);
}

void	change_fd
(t_set *s, int pi, int ci)
{
	int		tmp0;
	int		tmp1;

	errno = 0;
	if (ci == 0) //for the first command
	{
		close(s->st[pi].fd_arr[0][0]); //makes error2
		tmp0 = dup2(s->st[pi].fd_arr[0][1], 1); //substitutes write end
		if (tmp0 == -1)
			err_message("dup2 error 0");
	}
	else if (ci == s->st[pi].cn - 1) //for the last command
	{
		close(s->st[pi].fd_arr[ci - 1][1]); //closes write end
		tmp1 = dup2(s->st[pi].fd_arr[ci - 1][0], 0); //substitutes read end
		close(s->st[pi].fd_arr[ci - 1][1]);
		if (tmp1 == -1)
			err_message("dup2 error last");
	}
	else //for the all rest commands
	{
		close(s->st[pi].fd_arr[ci - 1][1]); //closes write end
		tmp0 = dup2(s->st[pi].fd_arr[ci - 1][0], 0); //substitutes read end
		close(s->st[pi].fd_arr[ci][0]); //closes read end
		tmp1 = dup2(s->st[pi].fd_arr[ci][1], 1); //substitutes write end
		if (tmp0 == -1 || tmp1 == -1)
			err_message("dup2 error rest");
	}
}

void	wpid(t_set *s, int pi, int *pid_arr)
{
	int		ci; //cmnd indx
	int		status;
	
	ci = 0;
	while (ci < s->st[pi].cn)
	{
		waitpid(pid_arr[ci], &status, 0);
		s->err = WEXITSTATUS(status);
		ci++;
	}
}

int		*launch(t_set *s, int pi)
{
	int		*arr;
	int		ci; //command indx
	pid_t	pid;

	arr = (int*)ft_calloc(s->st[pi].cn, sizeof(int));
	ci = 0;
	while (ci < s->st[pi].cn)
	{
		pid = fork();
		if (pid > 0)
		{
			arr[ci] = pid;
			if (ci < s->st[pi].cn - 1)
				close(s->st[pi].fd_arr[ci][1]); //магическая строка Тимофея
		}
		else if (pid == 0)
		{
			change_fd(s, pi, ci);
			if (bltn_check(s, pi, ci) == 1)
			{
				bltn_node(s, pi, ci);
				exit(0);
			}
			else
				mltple_cmd_node(s, pi, ci);
		}
		else
			err_message("fork() error");
		ci++;
	}
	wpid(s, pi, arr);
	return (arr);
}

void	pipes_node(t_set *s, int pi)
{
	s->st[pi].fd_arr = make_fd_arr(s, pi);
    s->st[pi].pid_arr = launch(s, pi);
}