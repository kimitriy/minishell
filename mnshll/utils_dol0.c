/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dol0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 19:35:42 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/07 19:37:22 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_memory_maker(char *s1, char *s2, int *lens1, int lens2)
{
	char	*sjn;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	sjn = (char *)malloc((lens1 + lens2 + 1) * sizeof(char));
	if (!sjn)
		err_memory_allocation_error(void);
	return (sjn);
}

char	*ft_strjoin_dol(char *s1, char *s2)
{
	char	*sjn;
	int		i;
	int		lens1;
	int		lens2;

	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	sjn = ft_memory_maker(s1, s2, &lens1, &lens2);
	i = 0;
	while (i < lens1)
	{
		sjn[i] = s1[i];
		i++;
	}
	while (i < (lens1 + lens2))
	{
		sjn[i] = s2[i - lens1];
		i++;
	}
	sjn[i] = '\0';
	return (sjn);
}

static	int	size(int n)
{
	size_t			i;
	unsigned int	m;

	i = 0;
	m = n;
	if (n >= 0 && n <= 9)
		return (1);
	if (n < 0)
	{
		m = n * (-1);
		i += 1;
	}
	while (m > 0)
	{
		m /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*arr;
	size_t			c;
	unsigned int	m;

	c = size(n);
	arr = (char *)malloc((c + 1) * sizeof(char));
	if (!arr)
		err_memory_allocation_error(void);
	arr[c] = '\0';
	m = n;
	if (n == 0)
		arr[--c] = '0';
	if (n < 0)
	{
		arr[0] = '-';
		m = -n;
	}
	while (m > 0)
	{
		arr[--c] = ((m % 10) + '0');
		m /= 10;
	}
	return (arr);
}
