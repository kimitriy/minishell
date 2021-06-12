/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_m.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:17:26 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/11 21:59:16 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *s1, int n)
{
	char	*p_s1;
	int		i;

	p_s1 = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (NULL == p_s1)
		err_memory_allocation_error();
	if (n > (ft_strlen(s1)))
		err_memory_allocation_error();
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
