/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:39:57 by rburton           #+#    #+#             */
/*   Updated: 2021/06/12 00:10:00 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_int(int **arr)
{
	int		i;

	i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void	ft_free_str(char **arr)
{
	int		i;

	i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

int	words_counter(const char *str, char dlmtr)
{
	int		wn;
	int		ndf;
	int		i;

	i = 0;
	wn = 0;
	ndf = 0;
	while (str[i])
	{
		if (str[i] != dlmtr && ndf == 0 && str[i + 1] != '\0')
			ndf = 1;
		else if (str[i] != dlmtr && ndf == 0 && str[i + 1] == '\0')
			wn++;
		else if ((str[i] == dlmtr && ndf == 1)
			|| (str[i] != dlmtr && str[i + 1] == '\0'))
		{
			wn++;
			ndf = 0;
		}
		i++;
	}
	return (wn);
}

void	parse_and_write_to_arr(char **arr, const char *str, char dlmtr, int wn)
{
	int				i;
	int				wi;
	size_t			len;
	unsigned int	strt;

	i = -1;
	wi = 0;
	strt = 0;
	while (wi < wn && str[++i])
	{
		if (str[i] != dlmtr)
		{
			strt = i;
			len = 0;
			while (str[i] != dlmtr && str[i] != '\0')
			{
				len++;
				i++;
			}	
			arr[wi] = ft_substr(str, strt, len);
			wi++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		wn;

	wn = words_counter(s, c);
	arr = (char **)ft_calloc(wn + 1, sizeof(char *));
	parse_and_write_to_arr(arr, s, c, wn);
	return (arr);
}
