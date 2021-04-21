/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addititional_func_masha.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 16:45:44 by smyriell          #+#    #+#             */
/*   Updated: 2021/04/21 18:03:35 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_masha.h"

int ft_strlen(char *str)
{
	int i;

	i = -1;
	while (str[++i]);
	return (i);	
}

// void symbol_valid(char c)
// {
// 	if (!(c == '$' || c == '-' || c == '|' || c == '<' || c == '>' || c == '?' \
// 		|| c == ';' || (c > 64 && c < 91) || (c > 96 && c < 124 )))
// 		write (1, "not valid\n", 10);
// 	write (1, "ok\n", 3);			
// }
// _______________________________________________
// char	*ft_strndup(const char *s1, int n)
// {
// 	char	*p_s1;
// 	size_t	i;

// 	p_s1 = (char*)malloc((ft_strlen((char*)s1) + 1) * sizeof(char));
// 	if (NULL == p_s1)
// 		return (NULL);
// 	if (n > (ft_strlen(s1)))
// 		return (NULL);
// 	i = 0;
// 	while (s1[i] != '\0' && i < n)
// 	{
// 		p_s1[i] = s1[i];
// 		i++;
// 	}
// 	p_s1[i] = '\0';
// 	return (p_s1);
// }
// ______________________________________________________
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

// int		ft_strcpy(char *dst, const char *src)
// {
// 	int		i;

	
// 	if (dst == NULL && src == NULL)
// 		return (0);
// 	i = 0;
// 	while (i < (dstsize - 1) && src[i])
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (ft_strlen(src));
// }

int		ft_strncmp(const char *s1, const char *s2, int n)
{
	int i;

	i = 0;
	if (!((s1 == 0 && s2 == 0) || n == 0))
	{
		while (i < n && (s1[i] || s2[i]))
		{
			if ((unsigned char)s1[i] != (unsigned char)s2[i])
				return ((unsigned char)s1[i] - (unsigned char)s2[i]);
			i++;
		}
	}
	return (0);
}


// int main()
// {
// 	char *a = "abcdefg";
// 	printf("%.*s\n", 5, a);
// 	return (0);
// }

