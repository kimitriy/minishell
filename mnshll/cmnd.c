/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:56:02 by rburton           #+#    #+#             */
/*   Updated: 2021/04/29 21:30:38 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	cmnd_node(t_set *s, int si, int pi)
// {
//     (void)s;
// 	(void)si;
// 	(void)pi;
//     printf("cmnd_node has reached\n");
// }

void	make_exc_arr(char **exc_arr, t_set *s, int si, int pi)
{
	int		i;

	exc_arr = (char**)malloc((s->set[si].ppline[pi].n + 1) * sizeof(char*));
	exc_arr[0] = s->argv0;
	i = 1;
	while (i < s->set[si].ppline[pi].n)
	{
		exc_arr[i] = s->set[si].ppline[pi].cmnd[i];
		i++;
	}
	exc_arr[i] = NULL;
}

void	cmnd_node(t_set *s, int si, int pi)
{
    (void)s;
    printf("cmnd_node has reached\n");

    pid_t   pid;
	char	**exc_arr;

	make_exc_arr(exc_arr, s, si, pi);

	pid = fork();
	if (pid == 0)
	{
		execve();
	}
	else
	{
		wait(&pid);
	}
}