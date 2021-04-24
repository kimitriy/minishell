/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:24:30 by rburton           #+#    #+#             */
/*   Updated: 2021/04/24 22:13:21 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_message(char *error)
{
    write(1, "Error!\n", 7);
	write(1, error, ft_strlen(error));
    write(1, "\n", 1);
    exit(0);
}

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

char	**arr2d_copy(char **arr, int en)
{
	// int		n;
	int		i;
	char	**narr;

	// n = 0;
	// while (arr[n] != NULL)
		// n++;
	narr = (char**)malloc((en + 1) * sizeof(char*));
	if (NULL == narr)
		return (NULL);
	narr[en] = NULL;
	i = 0;
	while (i < en)
	{
		narr[i] = (char*)malloc(ft_strlen(arr[i]) * sizeof(char));
		ft_strcpy(narr[i], arr[i]);
		i++;
	}
	// print2darr(arr, 0);
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
	print2darr(arr, 0);
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
