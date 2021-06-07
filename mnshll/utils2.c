/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:24:30 by rburton           #+#    #+#             */
/*   Updated: 2021/06/08 00:25:01 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_in_arr(char **arr, char *str)
{
	int		i;

	i = -1;
	while (arr[++i])
	{
		if (0 == ft_strcmp(arr[i], str))
			return (arr[i]);
	}
	return (NULL);
}

char	**key_in_arr(char **arr, char *key)
{
	int		i;
	char	**prsd_arr;

	i = 0;
	while (arr[i])
	{
		prsd_arr = parse_arg(arr[i]);
		if (0 == ft_strcmp(prsd_arr[0], key))
		{
			ft_free_str(prsd_arr);
			return (&arr[i]);
		}
		ft_free_str(prsd_arr);
		i++;
	}
	return (NULL);
}

char	**arr2d_copy(char **arr, int en)
{
	int		i; //arr indx
	char	**narr;

	narr = (char **)ft_calloc(en + 1, sizeof(char *));
	i = 0;
	while (i < en)
	{
		if (NULL != arr[i])
			narr[i] = ft_strdup(arr[i]);
		else
			narr[i] = NULL;
		i++;
	}
	narr[i] = NULL;
	return (narr);
}

void	str_swap(char **arr, int i1, int i2)
{
	char	*tmp;

	tmp = ft_strdup(arr[i1]);
	free(arr[i1]);
	arr[i1] = ft_strdup(arr[i2]);
	free(arr[i2]);
	arr[i2] = ft_strdup(tmp);
	free(tmp);
}

void	arr2d_sorted(char **arr, int en)
{
	int		sc; //swap case
	int		i;

	sc = -1;
	while (sc != 0)
	{
		sc = 0;
		i = 0;
		while (i < en)
		{
			if (arr[i + 1] != NULL && ft_strcmp(arr[i], arr[i + 1]) > 0)
			{
				str_swap(arr, i, i + 1);
				sc++;
			}
			i++;
		}
	}
}
