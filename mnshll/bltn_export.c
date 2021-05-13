/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:31:24 by rburton           #+#    #+#             */
/*   Updated: 2021/05/13 05:48:51 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		key_vldtr(t_set *s, int pi, int ci)
{
	if (s->st[pi].pln[ci].cmd[1][0] != 95 && 1 != ft_isalpha(s->st[pi].pln[ci].cmd[1][0]))
	{	
		err_not_a_valid_id(s, pi, ci);
		return (0);
	}
	else if (s->st[pi].pln[ci].cmd[1][0] = 95 && 1 != ft_isalpha(s->st[pi].pln[ci].cmd[1][1]) && 1 != ft_isdigit(s->st[pi].pln[ci].cmd[1][1]) && s->st[pi].pln[ci].cmd[1][1] != 95)
	{	
		err_not_a_valid_id(s, pi, ci);
		return (0);
	}
	else
		return (1);
}

char	*fill_str(char *str, int len, int offset, int trm)
{
	char	*arr;
	int		i;

	arr = (char*)malloc((len + 1) * sizeof(char));
	if (NULL == arr)
		err_message("pzdts");
	i = -1;
	while (++i < len)
		arr[i] = str[offset + i];
	arr[i] = '\0';
	if (trm != 0)
		arr = ft_strtrim(arr, "+");
	return (arr);
}

char	**parse_arg(char *str)
{
	char	**arr;
	int		len;
	int		offset;

	arr = (char**)malloc(3 * sizeof(char*));
	if (NULL == arr)
		err_message("pzdts");
	arr[2] = NULL;
	len = 0;
	while (str[len] && str[len] != 61)
		len++;
	arr[0] = fill_str(str, len, 0, 43);
	if (NULL == ft_strchr(str, 61))
		offset = len;
	else
		offset = len + 1;
	len = 0;
	while(str[offset + len])
		len++;
	arr[1] = fill_str(str, len, offset, 0);
	return (arr);
}

void	bltn_export(t_set *s, int pi, int ci)
{
	char	*rvno;
	char	*str;
	char	**arg;

	
	if (key_vldtr(s, pi, ci) == 1) //if key_vldtr says OK
	{
		if (s->st[pi].pln[ci].cmd[1][0] == 35) //if #
			print2darr(s->exp, 1);
		else
		{
			rvno = ft_strchr(s->st[pi].pln[ci].cmd[1], 61);
			if (NULL == rvno) //if there is no '=' therefore all the str is a key
			{
				// str = key_in_arr(s->exp, s->st[pi].pln[ci].cmd[1]);
				if (NULL == key_in_arr(s->exp, s->st[pi].pln[ci].cmd[1])) //if there is no such key in the export arr
					s->exp = ft_realloc(s->exp, s->exn, s->exn + 1, s->st[pi].pln[ci].cmd[1]); //adds key into the export arr
			}
			else //if there is '='
			{
				if (--rvno == 43) //if + before =
				{
					arg = parse_arg(s->st[pi].pln[ci].cmd[1]); //parses arg
					str = key_in_arr(s->env, s->st[pi].pln[ci].cmd[1]);
					if (NULL == str)
						s->env = ft_realloc(s->env, s->en, s->en + 1, s->st[pi].pln[ci].cmd[1]); //if there is no the key in env, add str
					else
						str = 

				}
				else //if there is no + before =
				{
					str = NULL;
					str = (char*)malloc(1 * sizeof(char));
					str = ft_strjoin(str, s->st[pi].pln[ci].cmd[1]);
				}
			}
		}
		print2darr(s->exp, 1);	
	}
}