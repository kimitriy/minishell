/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 04:57:25 by rburton           #+#    #+#             */
/*   Updated: 2021/06/11 21:48:22 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isnt_dash_n(char *str)
{
	int		i;

	if (str[0] != 45)
		return (1);
	else
	{
		i = 1;
		while (str[i] != '\0')
		{
			if (str[i] != 110)
				return (1);
			i++;
		}
		return (0);
	}
}

int	echo_vld(t_set *s, int pi, int ci)
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
	int		i;

	indx = echo_vld(s, pi, ci);
	i = indx;
	while (indx < s->st[pi].pln[ci].n && indx != 0)
	{
		len = ft_strlen(s->st[pi].pln[ci].cmd[indx]);
		write(1, s->st[pi].pln[ci].cmd[indx], len);
		if (i == 1 && s->st[pi].pln[ci].n > 2)
			write(1, " ", 1);
		else if (i > 1 && s->st[pi].pln[ci].n > 3)
			write(1, " ", 1);
		indx++;
	}
	if (i == 1)
		write(1, "\n", 1);
}
