/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:39:57 by rburton           #+#    #+#             */
/*   Updated: 2021/06/06 16:44:33 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*mem;

	mem = s;
	i = 0;
	while (i < n)
	{
		mem[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*pntr;

	pntr = (void *)malloc(count * size);
	if (NULL == pntr)
		err_memory_allocation_error();
	ft_bzero(pntr, count * size);
	return (pntr);
}

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

// char **ft_free(char **arr)
// {
// 	int		i;

// 	i = 0;
// 	while (arr[i] != NULL)
// 		free(arr[i++]);
// 	free(arr);
// 	arr = NULL;
// 	return (arr);
// }

void ft_free_int(int **arr)
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

////split
int		words_counter(const char *str, char dlmtr)
{
	int		wn; //words number
	int		ndf; //non dlmtr flag
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
		else if ((str[i] == dlmtr && ndf == 1) || (str[i] != dlmtr && str[i + 1] == '\0'))
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
	int				wi; //word indx
	size_t			len; //length number
	unsigned int	strt; //start indx

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
	int		wn; //words number

	wn = words_counter(s, c);
	arr = (char**)ft_calloc(wn + 1, sizeof(char*));
	parse_and_write_to_arr(arr, s, c, wn);
	return (arr);
}

////

////ft_strtrim()
int	ft_check_set(char smb, char const *check)
{
	int	i;

	i = 0;
	while (check[i] != '\0')
	{
		if (smb == check[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	char	*trimstr;
	size_t	i;
	size_t	len;
	size_t	j;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (str[i] != '\0' && ft_check_set(str[i], set))
		i++;
	if (i < len)
		while (ft_check_set(str[len - 1], set))
			len--;
	trimstr = (char *)malloc(sizeof(*str) * (len - i + 1));
	if (!trimstr)
		return (NULL);
	while (i + j < len)
	{
		trimstr[j] = str[i + j];
		j++;
	}
	trimstr[j] = '\0';
	return (trimstr);
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
	size_t	i;
	char	*pntr;

	pntr = (char*)ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	
	i = 0;
	while (s1[i])
	{
		pntr[i] = s1[i];
		i++;
	}
	pntr[i] = '\0';
	return (pntr);
}

// char	*ft_strdup(char *s1)
// {
// 	char	*p_s1;
// 	int		i;
// 	p_s1 = (char*)malloc((ft_strlen(s1) + 1) * sizeof(char));
// 	if (NULL == p_s1)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i] != '\0')
// 	{
// 		p_s1[i] = s1[i];
// 		i++;
// 	}
// 	p_s1[i] = '\0';
// 	return (p_s1);
// }

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
	sjn = (char*)ft_calloc(lens1 + lens2 + 1, sizeof(char));
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str_n;
	size_t		k;
	size_t		sl;

	if (!s)
		return (0);
	sl = ft_strlen(s);
	if (start >= sl)
		return (ft_strdup(""));
	str_n = ft_calloc((len + 1), sizeof(char));
	if (!str_n)
		return (NULL);
	k = 0;
	while (k + start < sl && k < len)
	{
		*(str_n + k) = *(s + start + k);
		k++;
	}
	str_n[k] = '\0';
	return (str_n);
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
				lineleak = NULL;
			}
		}
	}
}

int		get_next_line(int fd, char **line)
{
	static char		buf;
	int				rv;

	*line = (char*)ft_calloc(1, sizeof(char*));
	// if (!(*line = malloc(1)))
	// 	return (-1);
	**line = 0;
	rv = w2l(fd, &buf, line);
	return (rv);
}

////

void	ft_putnbr(int n)
{
	char	ch;

	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n < 0)
	{
		write(1, "-", 1);
		ft_putnbr(n * (-1));
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		ch = n + '0';
		write(1, &ch, 1);
	}
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (NULL == s)
		return (NULL);
	i = 0;
	if (c == '\0')
	{
		while (s[i])
			i++;
		return ((char*)&s[i]);
	}
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char*)&s[i]);
		i++;
	}
	return (NULL);
}

int		ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	else
		return (0);
}

int		ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

int		ft_atoi(const char *str)
{
	size_t					i;
	int						sign;
	unsigned long long int	number;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\v'
	|| str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign *= (-1);
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	number > 9223372036854775807 && sign > 0 ? number = -1 : 0;
	number > 9223372036854775807 && sign < 0 ? number = 0 : 0;
	return (sign * (int)number);
}

////itoa
static size_t	strlength(long int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	i += 1;
	return (i);
}

static void		strreverse(char *str)
{
	int		i;
	char	tmp;

	i = 0;
	tmp = 'c';
	while (i < ft_strlen(str) / 2)
	{
		tmp = str[i];
		str[i] = str[ft_strlen(str) - 1 - i];
		str[ft_strlen(str) - 1 - i] = tmp;
		i++;
	}
}

char			*ft_itoa(int n)
{
	size_t		j;
	long int	innern;
	char		*pstr;

	innern = (long int)n;
	pstr = (char*)calloc(strlength(n) + 1, sizeof(char));
	// if (pstr == NULL)
	// 	return (NULL);
	if (n < 0)
		innern = -innern;
	j = 0;
	while (j < strlength(n))
	{
		pstr[j] = (innern % 10) + '0';
		innern = innern / 10;
		j++;
	}
	if (n < 0)
		pstr[j - 1] = '-';
	pstr[j] = '\0';
	strreverse(pstr);
	return (pstr);
}
////