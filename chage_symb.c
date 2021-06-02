/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chage_symb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariakalashnikova <mariakalashnikova@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:23:47 by mariakalash       #+#    #+#             */
/*   Updated: 2021/05/27 14:40:06 by mariakalash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
// #include "minishell.h"

char *tmp;

int	ft_strlen(const char *str)
{
	int	i;

	i = -1;
	while (str[++i]);
	return (i);
}

char	*ft_strdup(const char *s1)
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

char	*ft_strjoin_symb(char *s1, char symb)
{
	char	*sjn;
	int		i;
	int		lens1;

	i = 0;
	if (s1 == NULL || s1[0] == '\0')
	{
		if (!(sjn = (char*)malloc((2) * sizeof(char))))
			return (NULL);
		sjn[i] = symb;
		sjn[++i] = '\0';
		return (sjn);
	}
	if (!symb)
		return (s1);
	lens1 = ft_strlen(s1);
	if (!(sjn = (char*)malloc((lens1 + 1 + 1) * sizeof(char))))
		return (NULL);
	
	while (i < lens1)
	{
		sjn[i] = s1[i];
		i++;
	}
	sjn[i] = symb;
	sjn[++i] = '\0';
	return (sjn);
}

void ft_check_quotes(char *str, int *i, int *q, int *a)//  структуру сюда тоже
{
    if (str[*i] == '\"' && *q == 0)
        *q = 1;
    else if (str[*i] == '\"' && *q == 1)
        *q = 0;
    else if (str[*i] == '\'' && *a == 0)
        *a = 1;
    else if (str[*i] == '\'' && *a == 1)
        *a = 0;
    tmp = ft_strjoin_symb(tmp, str[*i]);
    
}

// записывать tmp в структуру c долларом

void ft_change_the_symb(char *str, char symb1, char symb2, char symb3, char symb4)// send the struct here// we change the symb1 to symb2
{
    // char    *tmp;
    int i;
    int q;// quotes are opened = 1
    int a;

    i = -1;
    q = 0;
    a = 0;
    // tmp = ft_strdup("");
    while (str[++i])
    {
        if ((str[i] == '\"' || str[i] == '\'') && str[i - 1] != '\\')
            ft_check_quotes(str, &i, &q, &a);
        else if (str[i] == symb1 && q == 0 && a == 0)
            tmp = ft_strjoin_symb(tmp, symb2);// подмена с symb1 на symb 2
        else if (str[i] == symb3 && q == 0 && a == 0)
            tmp = ft_strjoin_symb(tmp, symb4);// подмена с symb3 на symb 4
        else
            tmp = ft_strjoin_symb(tmp, str[i]);
    }
    printf("tmp inside = %s\n", tmp);
}

int main()
{
    char *str;
    char symb1 = ' ';
    char symb2 = -1;
    char symb3 = '|';
    char symb4 = -2;

    tmp = ft_strdup("");
    
    str = "gd\'h || s\'gfj ||sdgf\"h  || jhjh 1\" 11\"   |||  \"11";
    ft_change_the_symb(str, symb1, symb2, symb3, symb4);
    printf("tmp = %s\n", tmp);
    printf("symb1 = %c\n", symb1);
    printf("symb2 = %c\n", symb2);
    return 0;
}
