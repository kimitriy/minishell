/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_symb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:23:47 by mariakalash       #+#    #+#             */
/*   Updated: 2021/06/11 23:14:18 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_quotes(char *str, int *i, int *q, int *a)
{
	if (str[*i] == '\"' && str[*i - 1] != '\\' && *q == 0)
		*q = 1;
	else if (str[*i] == '\"' && str[*i - 1] != '\\' && *q == 1)
		*q = 0;
	else if (str[*i] == '\'' && str[*i - 1] != '\\' && *a == 0)
		*a = 1;
	else if (str[*i] == '\'' && str[*i - 1] != '\\' && *a == 1)
		*a = 0;
}

void	ft_ret_back(t_set *s, t_pars *pars, int ci, int pi)
{
	int		i;
	int		q;
	int		a;
	int		n;
	char	*str;

	i = 0;
	q = 0;
	a = 0;
	n = pars->n;
	str = s->st[pi].pln[ci].cmd[pars->n];
	while (str[i])
	{
		if (str[i] == pars->symb2)
			s->st[pi].pln[ci].cmd[n][i] = pars->symb1;
		else if (str[i] == pars->symb4)
			s->st[pi].pln[ci].cmd[n][i] = pars->symb3;
		i++;
	}
}

void	ft_return_the_symb(t_set *set, t_pars *pars)
{
	int	pi;
	int	ci;

	pi = 0;
	while (pi < set->pn)
	{
		ci = 0;
		while (ci < set->st[pi].cn)
		{
			pars->n = 0;
			while (pars->n < set->st[pi].pln[ci].n)
			{
				ft_ret_back(set, pars, ci, pi);
				pars->n++;
			}
			ci++;
		}
		pi++;
	}
	free(pars->changed);
}
