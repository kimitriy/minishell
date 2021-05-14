/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:24:30 by rburton           #+#    #+#             */
/*   Updated: 2021/05/14 07:34:44 by rburton          ###   ########.fr       */
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

char	*key_in_arr(char **arr, char *key)
{
	int		i;
	char 	**prsd_arr;

	i = -1;
	while (arr[++i])
	{
		prsd_arr = parse_arg(arr[i]);
		if (0 == ft_strcmp(prsd_arr[0], key))
		{
			ft_free(prsd_arr);
			return (arr[i]);
		}
		ft_free(prsd_arr);
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
	// print2darr(arr, 1);
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
void	mark_str_to_del(char **arr, char *key)
{
	char	**prsd_arr;
	int		i;

	i = 0;
	while (arr[i])
	{
		prsd_arr = parse_arg(arr[i]);
		if (0 == ft_strcmp(prsd_arr[0], key))
		{
			arr[i][0] = '\0';
			ft_free(prsd_arr);
			return ;
		}
		ft_free(prsd_arr);
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
			narr[j] = ft_strdup(arr[i]);
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
	narr[nsize - 1] = ft_strdup(str);
	return (narr);
}

char	**unst(char **arr, int osize, int nsize, char **prsd_str)
{
	char	**narr_1 = NULL;
	char	**narr_2 = NULL;

	narr_1 = arr2d_copy(arr, osize);
	mark_str_to_del(narr_1, prsd_str[0]);
	narr_2 = ft_rlcc_del(narr_1, nsize);
	ft_free(prsd_str);
	ft_free(arr);
	return (narr_2);
}

void	str_ovrwrite(char *pstr, char *str)
{
	free(pstr);
	pstr = NULL;
	pstr = ft_strdup(str);
	// return (pstr);
}

char	**exprt(char **arr, int nsize, char *str)
{
	char	**narr;

	narr = ft_rlcc_add(arr, nsize, str);
	ft_free(arr);
	return(narr);
}

char**	ft_realloc(char **arr, int osize, int nsize, char *str)
{
	char	**narr;
	char	**prsd_str;

	prsd_str = parse_arg(str);
	if (NULL != key_in_arr(arr, prsd_str[0])) //searches corresponding str upon the keys
	{
		if (nsize < osize) //соответствует unset
		{
			narr = unst(arr, osize, nsize, prsd_str);
			return (narr);
		}
		else if (nsize == osize)
			str_ovrwrite(key_in_arr(arr, prsd_str[0]), str);
		ft_free(prsd_str);
		return (arr);
	}
	else //there is no such key in the arr
		if (osize < nsize) //соответствует export
		{
			narr = exprt(arr, nsize, str);
			ft_free(prsd_str);
			return(narr);
		}
	ft_free(prsd_str);
	return (arr);
}

