/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:31:24 by rburton           #+#    #+#             */
/*   Updated: 2021/06/06 18:37:24 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exp(t_set *s)
{
	int		i;
	char	**arr;
	char	**arg;

	arr = arr2d_copy(s->env, s->en);
	i = 0;
	while (i < s->en)
	{
		arg = parse_arg(arr[i]);
		if (0 != ft_strcmp(arg[0], "_") && 0 != ft_strcmp(arg[0], "\0"))
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
		}
		ft_free_str(arg);
		i++;
	}
	ft_free_str(arr);
}

int		key_vldtr(t_set *s, int pi, int ci)
{
	if (s->st[pi].pln[ci].cmd[1] != NULL && s->st[pi].pln[ci].cmd[1][0] != 35) //if there is an arg and its first character isn't '#'
	{
		if (s->st[pi].pln[ci].cmd[1][0] != 95 && 1 != ft_isalpha(s->st[pi].pln[ci].cmd[1][0])) //if the first char isn't '_' and it isn't a letter
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
	char	*tmp;
	int		i;

	arr = (char*)ft_calloc(len + 1, sizeof(char));
	i = -1;
	while (++i < len)
		arr[i] = str[offset + i];
	arr[i] = '\0';
	if (trm != 0)
	{
		tmp = arr;
		arr = ft_strtrim(arr, "+");
		free(tmp);
	}
	return (arr);
}

char	**parse_arg(char *str)
{
	char	**arr;
	int		len;
	int		offset;

	arr = (char**)ft_calloc(3, sizeof(char*));
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


void 	key_assist(t_set *s, int pi, int ci, char **arg)
{
	char	**str;
	char	*rvno;
	char    *str_tmp;
	char	*leak_tmp;

	str = key_in_arr(s->env, arg[0]); //searches key in the s->env and returns corresponding str
	rvno = ft_strchr(s->st[pi].pln[ci].cmd[1], 61); //checks out whether '=' is in the arg str
	if (NULL != rvno && *(rvno - 1) != 43) //no '+' before '='
		s->env = ft_realloc(s->env, s->en, s->en, s->st[pi].pln[ci].cmd[1]); //rewrite str with a new value
	else if (NULL != rvno && *(rvno - 1) == 43) // '+' before '='
	{
		if (ft_strchr(*str, 61) != NULL)
			str_tmp = ft_strjoin(*str, arg[1]);
		else
		{
			str_tmp = ft_strjoin(*str, "=");
			leak_tmp = str_tmp;
			str_tmp = ft_strjoin(str_tmp, arg[1]);
			free(leak_tmp);
		}
		s->env = ft_realloc(s->env, s->en, s->en, str_tmp); //rewrite str with a new value
		free(str_tmp);
	}
}

void	bltn_export(t_set *s, int pi, int ci)
{
	char	**str;
	char	**arg;

	if (key_vldtr(s, pi, ci) == 1) //validates arg str or prints out exp if there is no arg str
	{
		arg = parse_arg(s->st[pi].pln[ci].cmd[1]); //parses key and value
		str = key_in_arr(s->env, arg[0]); //searches key in the s->env and returns corresponding str
		if (NULL == str) //if there is no such key in the s->env
		{
			s->env = ft_realloc(s->env, s->en, s->en + 1, s->st[pi].pln[ci].cmd[1]); //adds the whole arg str into the env arr
			s->en++;
		}
		else //there is such key in the s->env
			key_assist(s, pi, ci, arg);
		ft_free_str(arg);
	}
}

// void	bltn_export(t_set *s, int pi, int ci)
// {
// 	char	*rvno;
// 	char	**str;
// 	char	**arg;
// 	char    *str_tmp;
// 	char	*leak_tmp;

// 	if (key_vldtr(s, pi, ci) == 1) //validates arg str or prints out exp if there is no arg str
// 	{
// 		arg = parse_arg(s->st[pi].pln[ci].cmd[1]); //parses key and value
// 		str = key_in_arr(s->env, arg[0]); //searches key in the s->env and returns corresponding str
// 		rvno = ft_strchr(s->st[pi].pln[ci].cmd[1], 61); //checks out whether '=' is in the arg str
// 		if (NULL == str) //if there is no such key in the s->env
// 		{
// 			s->env = ft_realloc(s->env, s->en, s->en + 1, s->st[pi].pln[ci].cmd[1]); //adds the whole arg str into the env arr
// 			s->en++;
// 		}
// 		else
// 		{
// 			if (NULL != rvno && *(rvno - 1) != 43) //no '+' before '='
// 				s->env = ft_realloc(s->env, s->en, s->en, s->st[pi].pln[ci].cmd[1]); //rewrite str with a new value
// 			else if (NULL != rvno && *(rvno - 1) == 43) // '+' before '='
// 			{
// 				if (ft_strchr(*str, 61) != NULL)
// 					str_tmp = ft_strjoin(*str, arg[1]);
// 				else
// 				{	
// 					str_tmp = ft_strjoin(*str, "=");
// 					leak_tmp = str_tmp;
// 					str_tmp = ft_strjoin(str_tmp, arg[1]);
// 					free(leak_tmp);
// 				}
// 				s->env = ft_realloc(s->env, s->en, s->en, str_tmp); //rewrite str with a new value
// 				free(str_tmp);
// 			}
// 		}
// 		ft_free_str(arg);
// 	}
// }

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
		ft_free_str(arg);
	}
}