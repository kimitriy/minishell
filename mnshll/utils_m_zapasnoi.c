/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_m_zapasnoi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:39:34 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/08 15:34:26 by smyriell         ###   ########.fr       */
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
#include <signal.h>
#include "minishell.h"

// если все ок без этих функций, удаляй этот файл, тут копии

int	ft_strlen(const char *str)
{
	int	i;

	i = -1;
	while (str[++i]);
	return (i);
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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	output;

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

char	*ft_strndup(char *s1, int n) // ADD
{
	char	*p_s1;
	int		i;

	p_s1 = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (NULL == p_s1)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		p_s1[i] = s1[i];
		i++;
	}
	p_s1[i] = '\0';
	return (p_s1);
}

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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*sjn;
	int		i;
	int		lens1;
	int		lens2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!(sjn = (char *)malloc((lens1 + lens2 + 1) * sizeof(char))))
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

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*p_s1;
	size_t	i;

	p_s1 = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
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

// int	ft_char_num(const char *str, int c)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == c && str[i - 1] != '\\')
// 			j++;
// 		i++;
// 	}
// 	return (j);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*sjn;
// 	int		i;
// 	int		lens1;
// 	int		lens2;

// 	if (s1 == NULL)
// 		return (s2);
// 	else if (s2 == NULL)
// 		return (s1);
// 	lens1 = ft_strlen(s1);
// 	lens2 = ft_strlen(s2);
// 	if (!(sjn = (char *)malloc((lens1 + lens2 + 1) * sizeof(char))))
// 		return (NULL);
// 	i = 0;
// 	while (i < lens1)
// 	{
// 		sjn[i] = s1[i];
// 		i++;
// 	}
// 	while (i < (lens1 + lens2))
// 	{
// 		sjn[i] = s2[i - lens1];
// 		i++;
// 	}
// 	sjn[i] = '\0';
// 	return (sjn);
// }

// char	*ft_strdup(const char *s1)
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
