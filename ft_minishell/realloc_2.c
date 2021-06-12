/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 22:52:30 by rburton           #+#    #+#             */
/*   Updated: 2021/06/11 23:12:30 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**exprt(char **arr, int nsize, char *str)
{
	char	**narr;

	narr = ft_rlcc_add(arr, nsize, str);
	return (narr);
}

char	**ft_realloc(char **arr, int osize, int nsize, char *str)
{
	char	**narr;
	char	**prsd_str;
	char	**tmp;

	prsd_str = parse_arg(str);
	tmp = key_in_arr(arr, prsd_str[0]);
	if (NULL != tmp && nsize < osize)
	{
		narr = unst(arr, osize, nsize, prsd_str);
		return (narr);
	}
	else if (NULL != tmp && nsize == osize)
	{
		str_ovrwrite(tmp, str);
		ft_free_str(prsd_str);
		return (arr);
	}
	else if (NULL == tmp && osize < nsize)
	{
		narr = exprt(arr, nsize, str);
		ft_free_str(prsd_str);
		return (narr);
	}
	ft_free_str(prsd_str);
	return (arr);
}
