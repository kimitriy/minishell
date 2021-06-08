/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_m.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:17:26 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/08 19:17:29 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_strndup(char *s1, int n)
// {
// 	char	*p_s1;
// 	int		i;

// 	p_s1 = (char *) ft_calloc((ft_strlen(s1) + 1), sizeof(char));
// 	i = 0;
// 	while (s1[i] != '\0' && i < n)
// 	{
// 		p_s1[i] = s1[i];
// 		i++;
// 	}
// 	p_s1[i] = '\0';
// 	return (p_s1);
// }

char	*ft_strndup(char *s1, int n)
{
	char	*p_s1;
	size_t	i;

	p_s1 = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (NULL == p_s1)
		err_memory_allocation_error(void);
	if (n > (ft_strlen(s1)))
		err_memory_allocation_error(void);
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		p_s1[i] = s1[i];
		i++;
	}
	p_s1[i] = '\0';
	return (p_s1);
}

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (s == NULL || fd < 0)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

// int	ft_check_string_and_symb(char *s1, char symb, char **sjn)
// {
// 	int	i;

// 	i = 0;
// 	if (s1 == NULL || s1[0] == '\0')
// 	{
// 		*sjn = (char *)ft_calloc(2, sizeof(char));
// 		*sjn[i] = symb;
// 		*sjn[++i] = '\0';
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

// char	*ft_strjoin_symb(char *s1, char symb)
// {
// 	char	*sjn;
// 	int		i;
// 	int		lens1;

// 	i = 0;
// 	if (ft_check_string_and_symb(s1, symb, &sjn))
// 		return (sjn);
// 	if (!symb)
// 		return (s1);
// 	lens1 = ft_strlen(s1);
// 	sjn = (char *)ft_calloc((lens1 + 1 + 1), sizeof(char));
// 	while (i < lens1)
// 	{
// 		sjn[i] = s1[i];
// 		i++;
// 	}
// 	sjn[i] = symb;
// 	sjn[++i] = '\0';
// 	return (sjn);
// }


