/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_symb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:23:47 by mariakalash       #+#    #+#             */
/*   Updated: 2021/06/08 15:17:16 by smyriell         ###   ########.fr       */
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

void	ft_change_the_symb(char *str, t_pars *pars)
{
	int	i;
	int	q;
	int	a;

	i = 0;
	q = 0;
	a = 0;
	ft_parse_init(pars);
	pars->changed = ft_strdup(str);
	while (pars->changed[i])
	{
		if ((pars->changed[i] == '\"' || pars->changed[i] == '\'') \
												&& pars->changed[i - 1] != '\\')
		{
			ft_check_quotes(pars->changed, &i, &q, &a);
			i++;
		}
		else if (pars->changed[i] == pars->symb1 && q == 0 && a == 0)
			pars->changed[i] = pars->symb2;
		else if (pars->changed[i] == pars->symb3 && q == 0 && a == 0)
			pars->changed[i] = pars->symb4;
		else
			i++;
	}
}

void	ft_ret_back(char *str, t_pars *pars, int ci, int pi)
{
	int	i;
	int	q;
	int	a;
	int	n;

	i = 0;
	q = 0;
	a = 0;
	n = pars->n;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && str[i - 1] != '\\')
		{
			ft_check_quotes(str, &i, &q, &a);
			i++;
		}
		else if (str[i] == pars->symb2 && q == 0 && a == 0)
			pars->ret[pi].pln[ci].cmd[n][i] = pars->symb1;
		else if (str[i] == pars->symb4 && q == 0 && a == 0)
			pars->ret[pi].pln[ci].cmd[n][i] = pars->symb3;
		else
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
				ft_ret_back(set->st[pi].pln[ci].cmd[pars->n], pars, ci, pi);
				pars->n++;
			}
			ci++;
		}
		pi++;
	}
	free(pars->changed);
}

// void ft_parse_init(t_pars *pars)
// {
// 	pars->symb1 = ' ';
//     pars->symb2 = -1;
// 	pars->symb3 = '|';
// 	pars->symb4 = -2;
// }

// int main()
// {
//     char *str;
//     char symb1 = ' ';
//     char symb2 = -1;
//     char symb3 = '|';
//     char symb4 = -2;
// 	t_pars pars;

//     ft_parse_init(&pars);
    
//     str = "gd\'h || s\'gfj ||sdgf\"h  || jhjh 1\" 11\"   |||  \"11";
// 	printf("str           = %s\n", str);
// 	ft_change_the_symb(str, &pars);
//     printf("symb1 = %c\n", symb1);
//     printf("symb2 = %c\n", symb2);
//     printf("pars->changed = %s\n", pars.changed);
//     return 0;
// }

// void ft_pre_splitting(char c, int q, int a) // подменяем для сплита
// {
// 	if (c == ';' && (q == 1 || a == 1))
// 		c = -1; // подмена точки с зап
// 	else if (c == ' ' && (q == 1 || a == 1))
// 		c = -2; // подмена пробела
// }

// void ft_aft_splitting(char c, int q, int a) // обратная подмена после сплита
// {
// 	if (c == -1 && (q == 1 || a == 1))
// 		c = ';'; // подмена на точк с зап
// 	else if (c == -2 && (q == 1 || a == 1))
// 		c = ' '; // подмена на пробел
// }
