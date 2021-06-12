/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:16:14 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/11 23:10:27 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_slash(t_dol *dol, t_set *s, char *str)
{
	if (dol->q == 0)
	{
		s->i += 1;
		ft_add_symb(dol, s, str);
	}
	else
	{
		if (ft_strchr(dol->cont_symb, str[s->i + 1]))
		{
			s->i += 1;
			ft_add_symb(dol, s, str);
		}
	}
}

void	check_spaces(t_set *s, char *str)
{
	if (str[s->i] == ' ')
	{
		while (str[s->i] == ' ')
			s->i++;
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
		err_memory_allocation_error();
	while (i < lens1)
	{
		sjn[i] = s1[i];
		i++;
	}
	sjn[i] = symb;
	sjn[++i] = '\0';
	return (sjn);
}
