/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:13:29 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/15 17:20:36 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_symb(t_dol *dol, t_set *s, char *str)
{
	char	*tmp;

	if (dol->q == 1 && str[s->i] == ' ')
		str[s->i] = -1;
	else if (dol->q == 1 && str[s->i] == '|')
		str[s->i] = -2;
	tmp = ft_strdup(dol->full_arg);
	free (dol->full_arg);
	dol->full_arg = ft_strjoin_symb(tmp, str[s->i]);
	free (tmp);
}

void	ft_parse_space(t_dol *dol, t_set *s, char *str)
{
	if (dol->q == 1)
		ft_add_symb(dol, s, str);
	else
	{
		if (str[s->i + 1] == ' ')
		{
			while (str[s->i] == ' ')
				s->i++;
			s->i -= 2;
		}
		else if (str[s->i + 1] == '>' || str[s->i + 1] == '<')
			return ;
		else if (str[s->i + 1] != '\0')
			ft_add_symb(dol, s, str);
	}
}

void	ft_parse_q_slash(t_dol *dol, t_set *s, char *str)
{
	char	*tmp;

	if (str[s->i + 1] == '$' || str[s->i + 1] == '\"')
	{
		s->i += 1;
		ft_add_symb(dol, s, str);
	}
	else if (str[s->i + 1] == '\\')
	{
		s->i++;
		tmp = ft_strdup(dol->full_arg);
		free(dol->full_arg);
		dol->full_arg = ft_strjoin_symb(tmp, str[s->i]);
		free(tmp);
	}
	else
	{
		tmp = ft_strdup(dol->full_arg);
		free(dol->full_arg);
		dol->full_arg = ft_strjoin_symb(tmp, str[s->i]);
		free(tmp);
	}
}

void	ft_parse_a(t_dol *dol, t_set *s, char *str)
{
	char	*tmp;

	if (dol->q == 0)
	{
		s->i++;
		while (str[s->i] != '\'' && str[s->i])
		{
			if (str[s->i] == ' ')
				str[s->i] = -1;
			else if (str[s->i] == '|')
				str[s->i] = -2;
			tmp = ft_strdup(dol->full_arg);
			free (dol->full_arg);
			dol->full_arg = ft_strjoin_symb(tmp, str[s->i]);
			free(tmp);
			s->i++;
		}
	}
	else
		return ;
}

void	ft_parse_q(t_dol *dol, t_set *s, char *str)
{
	dol->q = 1;
	s->i++;
	while ((!(str[s->i - 1] == '\\' && str[s->i] == '\"')) \
										&& str[s->i] != '\"' && str[s->i])
	{
		if (str[s->i] == ' ')
			ft_parse_space(dol, s, str);
		else if (str[s->i] == '$')
			ft_parse_dol(s, str);
		else if (str[s->i] == '\\')
			ft_parse_q_slash(dol, s, str);
		else
			ft_add_symb(dol, s, str);
		s->i++;
	}
	dol->q = 0;
}
