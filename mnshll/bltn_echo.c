/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 04:57:25 by rburton           #+#    #+#             */
/*   Updated: 2021/05/20 04:58:35 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		isnt_dash_n(char *str)
{
	int		i;

	if (str[0] != 45)
		return (1);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 110)
			return (1);
		i++;
	}
	return (0);
}

int		echo_vld(t_set *s, int pi, int ci)
{
	int		i;

	i = 1;
	while (i < s->st[pi].pln[ci].n)
	{
		if (1 == isnt_dash_n(s->st[pi].pln[ci].cmd[i]))
			return (i);
		i++;
	}
	return (0);
}

void	bltn_echo(t_set *s, int pi, int ci)
{
	int		indx;
	int		len;

	indx = echo_vld(s, pi, ci);
	if (indx > 1)
	{
		while (s->st[pi].pln[ci].cmd[indx] != NULL)
		{
			len = ft_strlen(s->st[pi].pln[ci].cmd[indx]);
			write(1, s->st[pi].pln[ci].cmd[indx], len);
			indx++;
		}
	}
	else if (indx == 1)
	{
		while (s->st[pi].pln[ci].cmd[indx] != NULL)
		{
			len = ft_strlen(s->st[pi].pln[ci].cmd[indx]);
			write(1, s->st[pi].pln[ci].cmd[1], len);
			indx++;
		}
		write(1, "\n", 1);
	}
}