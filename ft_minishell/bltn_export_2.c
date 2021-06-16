/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_export_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:31:24 by rburton           #+#    #+#             */
/*   Updated: 2021/06/15 22:17:30 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	f(char **str, char **arg, char **str_tmp)
{
	char	*leak_tmp;

	*str_tmp = ft_strjoin(*str, "=");
	leak_tmp = *str_tmp;
	*str_tmp = ft_strjoin(*str_tmp, arg[1]);
	free(leak_tmp);
}

void	key_assist(t_set *s, int pi, int ci, int i)
{
	char	**str;
	char	*rvno;
	char	*str_tmp;
	char	**arg;

	arg = parse_arg(s->st[pi].pln[ci].cmd[i]);
	str = key_in_arr(s->env, arg[0]);
	rvno = ft_strchr(s->st[pi].pln[ci].cmd[i], 61);
	if (rvno != NULL && *(rvno - 1) != 43)
		s->env = ft_realloc(s->env, s->en, s->en, s->st[pi].pln[ci].cmd[i]);
	else if (rvno != NULL && *(rvno - 1) == 43)
	{
		if (ft_strchr(*str, 61) != NULL)
			str_tmp = ft_strjoin(*str, arg[1]);
		else
			f(str, arg, &str_tmp);
		s->env = ft_realloc(s->env, s->en, s->en, str_tmp);
		free(str_tmp);
		ft_free_str(arg);
	}
}

void	fn(t_set *s, int pi, int ci, int i)
{
	s->env = ft_realloc(s->env, s->en, s->en + 1, \
		s->st[pi].pln[ci].cmd[i]);
	s->en++;
}

void	bltn_export(t_set *s, int pi, int ci)
{
	char	**str;
	char	**arg;
	int		i;

	if (s->st[pi].pln[ci].cmd[1] != NULL)
	{
		i = 0;
		while (++i < s->st[pi].pln[ci].n)
		{
			if (key_vldtr(s->st[pi].pln[ci].cmd[i]) == 1)
			{
				arg = parse_arg(s->st[pi].pln[ci].cmd[i]);
				str = key_in_arr(s->env, arg[0]);
				if (NULL == str)
					fn(s, pi, ci, i);
				else
					key_assist(s, pi, ci, i);
				ft_free_str(arg);
			}
			else
				err_not_a_valid_id(s, pi, ci, i);
		}
	}
	else
		print_exp(s);
}

void	bltn_unset(t_set *s, int pi, int ci)
{
	char	**arg;
	int		i;

	i =0;
	while (i < s->st[pi].pln[ci].n)
	{
		if (key_vldtr(s->st[pi].pln[ci].cmd[i]) == 1)
		{
			arg = parse_arg(s->st[pi].pln[ci].cmd[i]);
			if (NULL != key_in_arr(s->env, arg[0]))
			{
				s->env = ft_realloc(s->env, s->en, s->en - 1, \
					s->st[pi].pln[ci].cmd[i]);
				s->en--;
			}
			ft_free_str(arg);
		}
		else
			err_not_a_valid_id(s, pi, ci, i);
		i++;
	}
}
