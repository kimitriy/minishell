/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:31:24 by rburton           #+#    #+#             */
/*   Updated: 2021/05/19 08:58:58 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exp(t_set *s)
{
	int		i;
	char	**arr;
	char	**arg;

	arr = arr2d_copy(s->env, s->en);
	arr2d_sorted(arr, s->en);
	i = 0;
	while (i < s->en)
	{
		arg = parse_arg(arr[i]);
		if (0 != ft_strcmp(arg[0], "_"))
		{
			write(1, "declare -x ", 11);
			write(1, arg[0], ft_strlen(arg[0]));
			if (arg[1][0] != '\0')
			{
				write(1, "=\"", 2);
				write(1, arg[1], ft_strlen(arg[1]));
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
			ft_free(arg);
		}
		i++;
	}
}

int		key_vldtr(t_set *s, int pi, int ci)
{
	if (s->st[pi].pln[ci].cmd[1] != NULL && s->st[pi].pln[ci].cmd[1][0] != 35) //if there is arg
	{
		if (s->st[pi].pln[ci].cmd[1][0] != 95 && 1 != ft_isalpha(s->st[pi].pln[ci].cmd[1][0]))
		{	
			err_not_a_valid_id(s, pi, ci);
			return (0);
		}
		else if (s->st[pi].pln[ci].cmd[1][0] == 95 && 1 != ft_isalpha(s->st[pi].pln[ci].cmd[1][1]) && 1 != ft_isdigit(s->st[pi].pln[ci].cmd[1][1]) && s->st[pi].pln[ci].cmd[1][1] != 95)
		{	
			err_not_a_valid_id(s, pi, ci);
			return (0);
		}
		else
			return (1);
	}
	else
	{
		print_exp(s);
		return (0);
	}
}

char	*fill_str(char *str, int len, int offset, int trm)
{
	char	*arr;
	int		i;

	arr = (char*)calloc(len + 1, sizeof(char));
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

	arr = ft_calloc(3, sizeof(char*));
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

// void	bltn_export(t_set *s, int pi, int ci)
// {
// 	char	*rvno;
// 	char	**str;
// 	char	**arg;
// 	char 	*tmp;

// 	if (key_vldtr(s, pi, ci) == 1) //if key_vldtr says OK
// 	{
// 		arg = parse_arg(s->st[pi].pln[ci].cmd[1]); //parses key and value
// 		rvno = ft_strchr(s->st[pi].pln[ci].cmd[1], 61);
// 		if (NULL == rvno) //if there is no '=' therefore all the str is a key
// 		{
// 			str = key_in_arr(s->exp, arg[0]); //searches key in the s->exp and returns corresponding str
// 			if (NULL == str)
// 			{
// 				s->exp = ft_realloc(s->exp, s->exn, s->exn + 1, arg[0]); //adds key into the export arr
// 				s->exn++;
// 			}
// 		}
// 		else //if there is '='
// 		{
// 			str = key_in_arr(s->env, arg[0]); //searches key in the s->env and returns a pointer of a corresponding str
// 			if (NULL == str) //if there is no corresponding key
// 			{
// 				s->env = ft_realloc(s->env, s->en, s->en + 1, s->st[pi].pln[ci].cmd[1]); //add str to the s->env
// 				s->en++;
// 			}
// 			else
// 				if (*(rvno - 1) != 43) //no + before =
// 					s->env = ft_realloc(s->env, s->en, s->en, s->st[pi].pln[ci].cmd[1]); //rewrite str with a new value
// 				else // + before
// 				{
// 					tmp = ft_strjoin(*str, arg[1]);
// 					s->env = ft_realloc(s->env, s->en, s->en, tmp); //rewrite str with a new value
// 				}
// 			make_exp(s, 1);
// 		}
// 	}
// }

void	bltn_export(t_set *s, int pi, int ci)
{
	char	*rvno;
	char	**str;
	char	**arg;
	// char 	*tmp;

	if ( key_vldtr(s, pi, ci) == 1) //validates arg str or prints out exp if there is no arg str
	{
		arg = parse_arg(s->st[pi].pln[ci].cmd[1]); //parses key and value
		str = key_in_arr(s->env, arg[0]); //searches key in the s->env and returns corresponding str
		if (NULL == str) //if there is no such key in the s->env
		{
			s->env = ft_realloc(s->env, s->en, s->en + 1, s->st[pi].pln[ci].cmd[1]); //adds the whole arg str into the env arr
			s->en++;
		}
		else
		{
			rvno = ft_strchr(s->st[pi].pln[ci].cmd[1], 61); //checks out whether '=' is in the arg str
			if (NULL != rvno)
			{
				if (*(rvno - 1) != 43) //no '+' before '='
					s->env = ft_realloc(s->env, s->en, s->en, s->st[pi].pln[ci].cmd[1]); //rewrite str with a new value
				else // '+' before '='
					s->env = ft_realloc(s->env, s->en, s->en, ft_strjoin(*str, arg[1])); //rewrite str with a new value
			}	
		}
	}
}

void	bltn_unset(t_set *s, int pi, int ci)
{
	char	**arg;

	if (key_vldtr(s, pi, ci) == 1) //if key_vldtr says OK
	{
		arg = parse_arg(s->st[pi].pln[ci].cmd[1]); //parses key and value
		if (NULL != key_in_arr(s->env, arg[0]))
		{
			s->env = ft_realloc(s->env, s->en, s->en - 1, s->st[pi].pln[ci].cmd[1]);
			s->en--;
		}
		// make_exp(s, 1);
		// print2darr(s->env, 0);
		// print2darr(s->exp, 1);
	}
}