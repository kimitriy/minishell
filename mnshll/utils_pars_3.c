/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:16:14 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/08 19:16:17 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
	{
		s = &s[i];
		return ((char *)s);
	}
	return (0);
}

void	ft_parse_slash(t_dol *dol, char *str)
{
	if (dol->q == 0)
	{
		dol->i += 1;
		ft_add_symb(dol, str);
	}
	else
	{
		if (ft_strchr(dol->cont_symb, str[dol->i + 1])) // || str[dol->i + 1] == ' ')
		{
			dol->i += 1;
			ft_add_symb(dol, str);
		}
	}
}

void	check_spaces(t_dol *dol, char *str)
{
	if (str[dol->i] == ' ')
	{
		while (str[dol->i] == ' ')
			dol->i++;
	}
}

char	*ft_strjoin_symb(char *s1, char symb)
{
	char	*sjn;
	int		i;
	int		lens1;

	i = 0;
	if (s1 == NULL || s1[0] == '\0')
	{
		sjn = (char *)ft_calloc(2, sizeof(char));
		sjn[0] = symb;
		return (sjn);
	}
	if (!symb)
		return (s1);
	lens1 = ft_strlen(s1);
	sjn = (char *)malloc((lens1 + 1 + 1) * sizeof(char));
	if (!sjn)
		err_memory_allocation_error(void);
	while (i < lens1)
	{
		sjn[i] = s1[i];
		i++;
	}
	sjn[i] = symb;
	sjn[++i] = '\0';
	return (sjn);
}
