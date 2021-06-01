/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 22:52:30 by rburton           #+#    #+#             */
/*   Updated: 2021/05/28 16:03:17 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			ft_free_str(prsd_arr);
			return ;
		}
		ft_free_str(prsd_arr);
		i++;
	}
}

char	**ft_rlcc_del(char **arr, int nsize)
{
	char	**narr;
	int		i;
	int		j;

	narr = (char**)ft_calloc(nsize + 1, sizeof(char*));
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
	ft_free_str(arr);
	return (narr);
}

char	**ft_rlcc_add(char **arr, int nsize, char *str)
{
	char	**narr;

	narr = arr2d_copy(arr, nsize);
	narr[nsize - 1] = ft_strdup(str);
	ft_free_str(arr);
	return (narr);
}

char	**unst(char **arr, int osize, int nsize, char **prsd_str)
{
	char	**narr_1 = NULL;
	char	**narr_2 = NULL;

	narr_1 = arr2d_copy(arr, osize);
	mark_str_to_del(narr_1, prsd_str[0]);
	narr_2 = ft_rlcc_del(narr_1, nsize);
	ft_free_str(prsd_str);
	ft_free_str(arr);
	return (narr_2);
}

void	str_ovrwrite(char **pstr, char *str)
{
	free(*pstr);
	// pstr = NULL;
	*pstr = ft_strdup(str);
//	free(str);
    // write(1, "pstr: ", 7);
    // write(1, *pstr, ft_strlen(*pstr));
    // write(1, "\n", 1);
	// return (pstr);
}

char	**exprt(char **arr, int nsize, char *str)
{
	char	**narr;

	narr = ft_rlcc_add(arr, nsize, str);
	// ft_free_str(arr);
	// free(str);
	return(narr);
}

char    **ft_realloc(char **arr, int osize, int nsize, char *str)
{
	char	**narr; //new arr
	char	**prsd_str; //
    char    **tmp;

	prsd_str = parse_arg(str);
    tmp = key_in_arr(arr, prsd_str[0]);
	if (NULL != tmp) //searches corresponding str upon the keys
	{
		if (nsize < osize) //соответствует unset
		{
			narr = unst(arr, osize, nsize, prsd_str);
			return (narr);
		}
		else if (nsize == osize)
            str_ovrwrite(tmp, str);
		ft_free_str(prsd_str);
        // print2darr(arr, 0);
		return (arr);
	}
	else //there is no such key in the arr
    {
		if (osize < nsize) //соответствует export
		{
			narr = exprt(arr, nsize, str);
			ft_free_str(prsd_str);
			return(narr);
		}
    }
    ft_free_str(prsd_str);
	return (arr);
}