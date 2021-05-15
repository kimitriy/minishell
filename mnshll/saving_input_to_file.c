/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saving_input_to_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:12:04 by smyriell          #+#    #+#             */
/*   Updated: 2021/04/29 20:04:48 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "minishell.h"


void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*arr;

	arr = (void *)malloc(count * size);
	if (NULL == arr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}

void	ft_strcpy(char *dst, const char *src)
{
	int		i;

	if (dst == NULL || src == NULL)
		write(1, "ft_strcpy error", 16);
	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
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

void		ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*p;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

int main()
{
	t_ter 	hist;
	char 	buf[1024];
	int		i;
	int y = 3;

	hist.fd = open("zzz", O_CREAT | O_APPEND | O_RDWR, 0666);
	if (!hist.fd)
		write(1, "history file openning/creation error", 37); // err_message("history file openning/creation error");
	while (y)
	{
		
		i = 0;
		hist.str_len = read(0, buf, 1024);
		printf("len = %d\n", hist.str_len);
		if (hist.str_len == -1)
			write(1, "reading str_input error", 24);// err_message("reading str_input error");
		hist.str = (char *)ft_calloc((hist.str_len + 1), sizeof(char));
		while (buf[i] && buf[i] != '\n')
		{
			hist.str[i] = buf[i];
			i++;
		}
		hist.str[i] = '\n';
		i = write(hist.fd, hist.str, hist.str_len);
		if (i == -1)
			write(1, "writing str_input to file error", 32);
		
		printf("%s\n", hist.str);
		free(hist.str);
		y--;
	}
	
	return (0);
}
