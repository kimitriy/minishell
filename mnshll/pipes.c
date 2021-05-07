/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:55:12 by rburton           #+#    #+#             */
/*   Updated: 2021/05/08 01:03:04 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		**make_fd_arr(t_set *s, int pi)
// {
// 	int     **arr;
// 	int     ci; //command indx

// 	arr = (int**)malloc((s->set[pi].cn + 1) * sizeof(int*));
// 	if (NULL == arr)
// 		err_message("fd_arr malloc error");
// 	ci = 0;
// 	printf("CMD COUNT: %d\n", s->set[pi].cn);
// 	while (ci < s->set[pi].cn)
//     {
// 		arr[ci] = (int*)malloc(2 * sizeof(int));
// 		pipe(arr[ci]);
// 		printf("PIPE FD[%d][0]: %d, FD[%d][1]: %d\n", ci, arr[ci][0], ci, arr[ci][1]);
// 		ci++;
// 	}
// 	arr[ci] = NULL;
// 	// print2darr_int(arr);
// 	return(arr);
// }

int		**make_fd_arr(t_set *s, int pi)
{
	int     **arr;
	int     ci; //command indx
 
	arr = (int**)malloc((s->set[pi].cn + 1) * sizeof(int*)); //command number - 1 (number of pipes) + 1 (for NULL)
	if (NULL == arr)
		err_message("fd_arr malloc error");
	ci = 0;
	printf("CMD COUNT: %d\n", s->set[pi].cn);
	while (ci < (s->set[pi].cn - 1))
    {
		arr[ci] = (int*)malloc(2 * sizeof(int));
		pipe(arr[ci]);
		printf("PIPE FD[%d][0]: %d, FD[%d][1]: %d\n", ci, arr[ci][0], ci, arr[ci][1]);
		ci++;
	}
	arr[ci] = NULL;
	return(arr);
}

void	change_fd(t_set *s, int pi, int ci)
{
	int		tmp1;
	int		tmp0;

	write(1, "change_fd", 9);
	// write(1, "change_fd: pi: ", 15);
	// ft_putnbr(pi);
	// write(1, " ci: ", 5);
	// ft_putnbr(ci);
	// write(1, "\n", 1);
	
	// if (ci == 0) //for the first command
	// {
		// close(s->set[pi].fd_arr[ci][0]);
	dup2(s->set[pi].fd_arr[0][1], 1); //substitutes read end
	write(1, "ci == 0: ", 9);
	ft_putnbr(pi);
	write(1, " ci: ", 5);
	ft_putnbr(ci);
	write(1, "\n", 1);
	// }
	if (ci > 0 || ci < s->set[pi].cn - 1) //for the all rest commands
	{
		tmp0 = dup2(s->set[pi].fd_arr[ci - 1][0], 0); //substitutes read end
		tmp1 = dup2(s->set[pi].fd_arr[ci][1], 1); //substitutes write end
		write(1, "else: ", 6);
		ft_putnbr(pi);
		write(1, " ci: ", 5);
		ft_putnbr(ci);
		write(1, "\n", 1);
		if (tmp0 == -1 || tmp1 == -1)
			err_message("dup2 error");
	}

	// else if (ci == s->set[pi].cn - 1) //for the last command
	// {
		// close(s->set[pi].fd_arr[ci][1]);
	dup2(s->set[pi].fd_arr[ci - 1][0], 0); //substitutes write end
	write(1, "ci == s->set[pi].cn - 1: ", 25);
	ft_putnbr(pi);
	write(1, " ci: ", 5);
	ft_putnbr(ci);
	write(1, "\n", 1);
}

// void	change_fd_0(t_set *s, int pi, int ci)
// {
// 	dup2(s->set[pi].fd_arr[ci][1], 1); //substitutes read end
// 	// write(1, "ci == 0: ", 9);
// 	// ft_putnbr(pi);
// 	// write(1, " ci: ", 5);
// 	// ft_putnbr(ci);
// 	// write(1, "\n", 1);
// }

// void	change_fd_last(t_set *s, int pi, int ci)
// {
// 	dup2(s->set[pi].fd_arr[ci - 1][0], 0); //substitutes write end
// 	// write(1, "ci == s->set[pi].cn - 1: ", 25);
// 	// ft_putnbr(pi);
// 	// write(1, " ci: ", 5);
// 	// ft_putnbr(ci);
// 	// write(1, "\n", 1);
// }

// void	change_fd_rest(t_set *s, int pi, int ci)
// {
// 	int		tmp0;
// 	int		tmp1;
	
// 	tmp0 = dup2(s->set[pi].fd_arr[ci - 1][0], 0); //substitutes read end
// 	tmp1 = dup2(s->set[pi].fd_arr[ci][1], 1); //substitutes write end
// 	// write(1, "else: ", 6);
// 	// ft_putnbr(pi);
// 	// write(1, " ci: ", 5);
// 	// ft_putnbr(ci);
// 	// write(1, "\n", 1);
// 	if (tmp0 == -1 || tmp1 == -1)
// 		err_message("dup2 error");
// }

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
		// write(1, "s->set[pi].cn: ", 15);
		// ft_putnbr(s->set[pi].cn);
		// write(1, "\n", 1);
		
		if (pid > 0)
		{
			arr[ci] = pid;
			// close(s->set[pi].fd_arr[ci][0]); //магическая строка Тимофея
		}
		else if (pid == 0)
		{
			change_fd(s, pi, ci);
			// printf("ci: %d\n", ci);
			// if (ci == 0)
			// {
			// 	change_fd_0(s, pi, 0);
			// 	write(1, "0", 1);
			// 	write(1, "\n", 1);
			// }
			// if (ci == s->set[pi].cn - 1)
			// {
			// 	change_fd_last(s, pi, s->set[pi].cn - 1);
			// 	write(1, "last", 4);
			// 	write(1, "\n", 1);
			// }
			// else
			// {
			// 	change_fd_rest(s, pi, ci);
			// 	write(1, "rest", 4);
			// 	write(1, "\n", 1);
			// }
			if (bltn_check(s, pi, ci) == 1)
			{	
				bltn_node(s, pi, ci);
			}
			else
			{	
				mltple_cmnd_node(s, pi, ci);
			}
		}
		else
			err_message("fork() error");
		// write(1, "ITER", 4);
		ci++;
	}
	ci = 0;
	while (ci < s->set[pi].cn)
	{
		waitpid(arr[ci], &status, 0);
		// if (ci == 0)
		// 	close(s->set[pi].fd_arr[ci][1]);
		// else if (ci == s->set[pi].cn -1)
		// 	close(s->set[pi].fd_arr[ci][0]);
		// else
		// {
		// 	close(s->set[pi].fd_arr[ci][1]);
		// 	close(s->set[pi].fd_arr[ci - 1][0]);
		// }
		ci++;
	}
	// print_arr_int(arr);
	return (arr);
}

void	pipes_node(t_set *s, int pi)
{
	// write(1, "pipes_node has been reached\n", 29);
	
	s->set[pi].fd_arr = make_fd_arr(s, pi);
    s->set[pi].pid_arr = launch(s, pi);
}