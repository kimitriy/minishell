/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:24:30 by rburton           #+#    #+#             */
/*   Updated: 2021/04/22 23:19:31 by rburton          ###   ########.fr       */
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

char	**arr2d_copy(char **arr)
{
	int		n;
	int		i;
	char	**narr;

	n = 0;
	while (arr[n] != NULL)
		n++;
	narr = (char**)malloc(n * sizeof(char*));
	if (NULL == narr)
		return (NULL);
	i = 0;
	while (i < n)
	{
		narr[i] = (char*)malloc(ft_strlen(arr[i]) * sizeof(char));
		ft_strcpy(narr[i], arr[i]);
		i++;
	}
	return(narr);
}

void	arr2d_sorted(char	**arr)
{
	int		si; //string indx
	char	*tmp;

	si = 0;
	while (0 < ft_strcmp(arr[si], arr[si + 1]))
	{
		tmp = (char*)malloc((ft_strlen(arr[si]) + 1) * sizeof(char));
		ft_strcpy(tmp, arr[si]);
        free(arr[si]);
        arr[si] = ft_strjoin(arr[si], arr[si + 1]);
        free(arr[si + 1]);
        arr[si] = ft_strjoin(arr[si + 1], tmp);
		free(tmp);
	}
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
