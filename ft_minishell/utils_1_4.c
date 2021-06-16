/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:39:57 by rburton           #+#    #+#             */
/*   Updated: 2021/06/15 22:37:36 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	str_n = (char *)ft_calloc((len + 1), sizeof(char));
	k = 0;
	while (k + start < sl && k < len)
	{
		*(str_n + k) = *(s + start + k);
		k++;
	}
	str_n[k] = '\0';
	return (str_n);
}

// int	w2l(int fd, char *buf, char **line)
// {
// 	int		rv;
// 	char	*lineleak;

// 	while (1)
// 	{
// 		rv = read(fd, buf, 1);
// 		if (rv < 0)
// 			return (-1);
// 		else if (rv == 0)
// 			return (0);
// 		else
// 		{
// 			if (*buf == '\n')
// 				return (1);
// 			else
// 			{
// 				lineleak = *line;
// 				*line = ft_strjoin(*line, buf);
// 				free(lineleak);
// 				lineleak = NULL;
// 			}
// 		}
// 	}
// }

// int	get_next_line(int fd, char **line)
// {
// 	static char		buf;
// 	int				rv;

// 	*line = (char *)ft_calloc(1, sizeof(char *));
// 	**line = 0;
// 	rv = w2l(fd, &buf, line);
// 	return (rv);
// }

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
