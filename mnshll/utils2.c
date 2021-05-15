/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:24:30 by rburton           #+#    #+#             */
/*   Updated: 2021/05/15 03:09:23 by rburton          ###   ########.fr       */
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
	char 	**prsd_arr;

	i = 0;
	while (arr[i])
	{
		prsd_arr = parse_arg(arr[i]);
		if (0 == ft_strcmp(prsd_arr[0], key))
		{
			ft_free(prsd_arr);
			return (&arr[i]);
		}
		ft_free(prsd_arr);
		i++;
	}
	return (NULL);
}

char	**arr2d_copy(char **arr, int en)
{
	int		i; //arr indx
	char	**narr;

	narr = (char**)malloc((en + 1) * sizeof(char*));
	if (NULL == narr)
		err_message("pzdts");
	i = -1;
	while (++i < en)
	{
		if (NULL != arr[i])
			narr[i] = ft_strdup(arr[i]);
		else
			narr[i] = NULL;
	}
	narr[i] = NULL;
	return(narr);
}

void	str_swap(char **arr, int i1, int i2)
{
	char	*tmp;

	tmp = (char*)malloc(1 * sizeof(char));
	tmp = ft_strjoin(tmp, arr[i1]);
	arr[i1] = NULL;
	arr[i1] = (char*)malloc(1 * sizeof(char));
	arr[i1] = ft_strjoin(arr[i1], arr[i2]);
	arr[i2] = NULL;
	arr[i2] = (char*)malloc(1 * sizeof(char));
	arr[i2] = ft_strjoin(arr[i2], tmp);
}

void	arr2d_sorted(char **arr, int exn)
{
	int		sc; //swap case
	int		i;

	// print2darr(arr, 0);
	sc = -1;
	while (sc != 0)
	{
		sc = 0;
		i = 0;
		while (i < exn)
		{
			if (arr[i + 1] != NULL && ft_strcmp(arr[i], arr[i + 1]) > 0)
			{
				str_swap(arr, i, i + 1);
				sc++;
			}
			i++;
		}
	}
	// print2darr(arr, 0);
}

void    write2env(t_set *s, char *field, char *str)
{
    int     i;

    i = -1;
    while (++i < s->en)
    {
        if (0 == ft_strcmp(s->env[i], field))
        {
			free(s->env[i]);
			s->env[i] = ft_strjoin(s->env[i], field);
			s->env[i] = ft_strjoin(s->env[i], str);
		}
    }
}
