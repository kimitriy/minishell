/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_export_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:31:24 by rburton           #+#    #+#             */
/*   Updated: 2021/06/12 00:46:00 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exp_line(char	**prsd_arg, int rvno_f)
{
	write(1, "declare -x ", 11);
	write(1, prsd_arg[0], ft_strlen(prsd_arg[0]));
	if (rvno_f == 1)
		write(1, "=\"\"", 3);
	if (prsd_arg[1][0] != '\0')
	{
		write(1, "=\"", 2);
		write(1, prsd_arg[1], ft_strlen(prsd_arg[1]));
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

void	print_exp(t_set *s)
{
	int		i;
	char	**arr;
	char	**arg;
	char	*rvno_p;

	arr = arr2d_copy(s->env, s->en);
	arr2d_sorted(arr, s->en);
	i = 0;
	while (i < s->en)
	{
		arg = parse_arg(arr[i]);
		if (0 != ft_strcmp(arg[0], "_")
			&& 0 != ft_strcmp(arg[0], "\0"))
		{
			rvno_p = ft_strchr(arr[i], '=');
			if (rvno_p != NULL && *(rvno_p + 1) == '\0')
				print_exp_line(arg, 1);
			else
				print_exp_line(arg, 0);
		}
		ft_free_str(arg);
		i++;
	}
	ft_free_str(arr);
}

int	key_vldtr(char *str)
{
	if (str[0] != 35)
	{
		if (str[0] != 95 && 1 != ft_isalpha(str[0]))
			return (0);
		else if (str[0] == 95 && 1 != ft_isalpha(str[1])
			&& 1 != ft_isdigit(str[1]) && str[1] != 95)
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

char	*fill_str(char *str, int len, int offset, int trm)
{
	char	*arr;
	char	*tmp;
	int		i;

	arr = (char *)ft_calloc(len + 1, sizeof(char));
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

	arr = (char **)ft_calloc(3, sizeof(char *));
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
	while (str[offset + len])
		len++;
	arr[1] = fill_str(str, len, offset, 0);
	return (arr);
}
