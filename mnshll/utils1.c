/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:39:57 by rburton           #+#    #+#             */
/*   Updated: 2021/04/22 20:13:46 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strlen(const char *s)
{
	int		i;

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

int		ft_strncmp(const char *s1, const char *s2, int n)
{
	int		i;

	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i] != '\0') && (s2[i] != '\0') && (i < (n - 1)))
	{
		if (s1[i] != s2[i])
			break ;
		else
			i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*return_value;
	char	*inner_hstck;

	i = 0;
	return_value = NULL;
	inner_hstck = (char*)haystack;
	if (strlen(needle) == 0)
		return (inner_hstck);
	while(inner_hstck[i] && i < len)
	{
		if (ft_strncmp(&inner_hstck[i], needle, ft_strlen(needle)) == 0)
		{
			return_value = &inner_hstck[i];	
			break;
		}
		i++;
	}
	if ((i - 1) + ft_strlen(needle) < len)
		return (return_value);
	else
		return (NULL);
}

////split

static char **ft_free(char **arr, int j)
{
	int		i;

	i = 0;
	while (i < j)
		free(arr[i++]);
	free(arr);
	arr = NULL;
	return (arr);
}

static char		*ft_word(char const *s, char c)
{
	char	*arr;
	size_t	i;
	size_t	j;
	
	i = 0;
	j = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	arr = (char *)malloc(sizeof(char) * (i + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

static int		ft_num(char const *s, char c)
{
	size_t	i;
	size_t	j;
	
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			j++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	size_t	j;
	char	**arr;
	
	if (s == NULL)
		return (NULL);
	if (!(arr = (char **)malloc((ft_num(s, c) + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			if (!(arr[j++] = ft_word(&s[i], c)))
				return (ft_free(arr, j));
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	arr[j] = NULL;
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
		if (nomatch < (size_t)ft_strlen(set))
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
		if (nomatch < (size_t)ft_strlen(set))
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
	dst[i] = '\0';
}

char	*ft_strdup(char *s1)
{
	char	*p_s1;
	int		i;

	p_s1 = (char*)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (NULL == p_s1)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		p_s1[i] = s1[i];
		i++;
	}
	p_s1[i] = '\0';
	return (p_s1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjn;
	int		i;
	int		lens1;
	int		lens2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!(sjn = (char*)malloc((lens1 + lens2 + 1) * sizeof(char))))
		return (NULL);
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


////GNL

int		w2l(int fd, char *buf, char **line)
{
	int		rv;
	char	*lineleak;

	while (1)
	{
		rv = read(fd, buf, 1);
		if (rv < 0)
			return (-1);
		else if (rv == 0)
			return (0);
		else
		{
			if (*buf == '\n')
				return (1);
			else
			{
				lineleak = *line;
				*line = ft_strjoin(*line, buf);
				free(lineleak);
			}
		}
	}
}

int		get_next_line(int fd, char **line)
{
	static char		buf;
	int				rv;

	if (!(*line = malloc(1)))
		return (-1);
	**line = 0;
	rv = w2l(fd, &buf, line);
	return (rv);
}

////