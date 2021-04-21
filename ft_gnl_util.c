/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:53:14 by smyriell          #+#    #+#             */
/*   Updated: 2021/04/21 18:23:53 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_masha.h"

char	*ft_strchr_n(const char *str)
{
	size_t		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\n')
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return ((char *)str + i);
}

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	if (!s)
// 		return (0);
// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

char	*ft_strjoin(char *s1, const char *s2)
{
	char		*arr;
	size_t		i;
	size_t		j;
	size_t		s1_len;
	size_t		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen((char*)s2);
	if (!(arr = (char *)malloc((s1_len + s2_len + 1) * (sizeof(char)))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < s1_len)
	{
		arr[i] = s1[i];
		i++;
	}
	while (j < s2_len)
		arr[i++] = s2[j++];
	arr[i] = '\0';
	// free(s1);
	s1 = NULL;
	return (arr);
}

char	*ft_strdup_to_n(char *s1)
{
	size_t		i;
	char		*p_s1;

	if (!s1)
		return (0);
	i = 0;
	while (s1[i] && s1[i] != '\n')
		i++;
	if (!(p_s1 = (char*)malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		p_s1[i] = s1[i];
		i++;
	}
	p_s1[i] = '\0';
	return (p_s1);
}
