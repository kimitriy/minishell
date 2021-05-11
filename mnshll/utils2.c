/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:24:30 by rburton           #+#    #+#             */
/*   Updated: 2021/05/11 00:47:14 by rburton          ###   ########.fr       */
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

char	**arr2d_copy(char **arr, int en)
{
	int		i; //arr indx
	char	**narr;

	narr = (char**)malloc((en + 1) * sizeof(char*));
	if (NULL == narr)
		return (NULL);
	i = -1;
	while (++i < en)
	{
		if (NULL == arr[i])
			break;
		else
		{
			narr[i] = (char*)malloc(ft_strlen(arr[i]) * sizeof(char));
			ft_strcpy(narr[i], arr[i]);
			// printf("narr[%d]: %s\n", i, narr[i]);
		}
	}
	narr[i] = NULL;
	// printf("arr2d_copy:\n");
	// print2darr(narr, 0);
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


/////realloc
void	mark_str_to_del(char **arr, char *str)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (0 == ft_strcmp(arr[i], str))
			arr[i][0] = '\0';
		i++;
	}
}


char	**ft_rlcc_del(char **arr, int nsize)
{
	char	**narr;
	int		i;
	int		j;

	narr = (char**)malloc((nsize + 1) * sizeof(char*));
	if (NULL == narr)
		err_message("realloc error");
	i = -1;
	j = 0;
	while (arr[++i])
	{
		if (arr[i][0] != '\0')
		{
			narr[j] = (char*)malloc((nsize + 1) * sizeof(char));
			if (NULL == narr)
				err_message("realloc error");
			ft_strcpy(narr[j], arr[i]);
		}
		else
			continue;
		j++;
	}
	narr[j] = NULL;
	ft_free(arr);
	return (narr);
}

char	**ft_rlcc_add(char **arr, int nsize, char *str)
{
	char	**narr;

	narr = arr2d_copy(arr, nsize);
	narr[nsize - 1] = (char*)malloc(ft_strlen(str) * sizeof(char));
	ft_strcpy(narr[nsize - 1], str);
	return (narr);
}

char	**ft_realloc(char **arr, int osize, int nsize, char *str)
{
	char	**narr_1 = NULL;
	char	**narr_2 = NULL;

	if (NULL != str_in_arr(arr, str))
	{
		if (nsize < osize) //соответствует unset
		{
			narr_1 = arr2d_copy(arr, osize);
			mark_str_to_del(narr_1, str);
			narr_2 = ft_rlcc_del(narr_1, nsize);
			return (narr_2);
		}
		else
			return (arr);
	}
	else
	{
		if (osize < nsize) //соответствует export
		{
			narr_1 = ft_rlcc_add(arr, nsize, str);
			return (narr_1);
		}
		else
			return (arr);
	}
}

