/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:39:57 by rburton           #+#    #+#             */
/*   Updated: 2021/04/09 19:41:38 by rburton          ###   ########.fr       */
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_strcmp(char *s1, char *s2)
{
	int		i;
	int		output;

	i = 0;
	output = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			break ;
		else
			i++;
	}
	output = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (output);
}

////split

int		**give_memory(int axlr[10000][2], int w)
{
	int		**arr;
	int		i;

	i = -1;
	if (!(arr = (int**)malloc(w * sizeof(int*))))
		return (NULL);
	i = -1;
	while (++i < w)
	{
		if (!(arr[i] = (int*)malloc(2 * sizeof(int))))
			return (NULL);
		arr[i][0] = axlr[i][0];
		arr[i][1] = axlr[i][1];
	}
	return (arr);
}

int		**wrd_cntr(int *wn, char const *s, char c)
{
	int		i; //line symbol counter
	int		w; //words(lines) counter
	int		f; //flag
	int		axlr[10000][2];
	int		**arr;
	
	i = -1;
	w = 0;
	f = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			if (f == 0 && (f = 1))
				axlr[w][0] = i;
			if (s[i + 1] == '\0' && (axlr[w][1] = i - axlr[w][0] + 1))
				w++;
		}
		else if (s[i] == c && f == 1 && (axlr[w++][1] = i - axlr[w][0]))
			f = 0;
	}
	arr = give_memory(axlr, w);
	*wn = w;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	int		wn;
	int		**axlr;
	char	**arr;
	
	if (!s)
		return (NULL);
	axlr = wrd_cntr(&wn, s, c);
	if (!(arr = (char**)malloc(wn * sizeof(char*))))
		return (NULL);
	i = -1;
	while (++i < wn)
	{
		if (!(arr[i] = (char*)malloc(axlr[i][1] * sizeof(char))))
			return (NULL);
		k = -1;
		while (++k < axlr[i][1])
			arr[i][k] = s[k + axlr[i][0]];
	}
	arr[i] = NULL;
	free(axlr);
	return (arr);
}

////

////ft_strtrim()

size_t	lindx(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	nomatch;

	i = -1;
	nomatch = 0;
	while (s1[++i])
	{
		j = -1;
        while (set[++j])
			if (s1[i] != set[j])
				nomatch++;
		if (nomatch < ft_strlen(set))
			nomatch = 0;
		else
			return (i);		
	}
	return (0);
}

size_t	rindx(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	nomatch;

	i = ft_strlen(s1);
	nomatch = 0;
	while (--i > 0)
	{
		j = -1;
        while (set[++j])
			if (s1[i] != set[j])
				nomatch++;
		if (nomatch < ft_strlen(set))
			nomatch = 0;
		else
			return (i);		
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return (NULL);
	strtrim = (char*)malloc((rindx(s1, set) - lindx(s1, set) + 2) * sizeof(char));
	if (NULL == strtrim)
		return (NULL);
	i = -1;
	j = lindx(s1, set) - 1;
	while (++i < (rindx(s1, set) - lindx(s1, set) + 1))
		strtrim[i] = s1[++j];
	if (lindx(s1, set) == 0 && rindx(s1, set) == 0)
		strtrim[0] = '\0';
	strtrim[i] = '\0';
	return (strtrim);
}

////

void	ft_strcpy(char *dst, const char *src)
{
	int		i;

	if (dst == NULL || src == NULL)
		err_message("ft_strcpy error");
	i = -1;
	while (src[++i])
		dst[i] = src[i];
}

void	print2darr(char **arr)
{
	int		n;
	int		i;

	n = 0;
	while (arr[n] != NULL)
		n++;
	i = -1;
	while (++i < n)
		printf("line:%d, %s\n", i, arr[i]);
}