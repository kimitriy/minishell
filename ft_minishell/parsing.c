/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 19:50:55 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/11 23:12:22 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_dol(t_set *s, char *str)
{
	int		j;
	int		len;

	if (str[s->i + 1] == '?')
	{
		ft_err_nmb(s);
		return ;
	}
	if (str[s->i - 1] != '\\')
		s->i++;
	else
		ft_slash_in_dol(s, str);
	j = 0;
	if (!ft_check_symb_aft_dol(&s->dol, s, str, &j))
	{
		if (str[s->i + 1] == ' ')
		{
			while (str[++s->i] == ' ')
				;
			s->i--;
		}
		return ;
	}
	if (ft_check_env(s, j))
		ft_not_found_in_env(s, &len, str);
}

int	ft_parsing_2(t_dol *dol, t_set *s, char *str)
{
	if (str[s->i] == ' ')
		ft_parse_space(dol, s, str);
	else if (str[s->i] == '$')
	{
		ft_parse_dol(s, str);
	}
	else if (str[s->i] == '|' && dol->redir_pipe == 1)
	{
		s->dol.full_arg = ft_strjoin_symb(s->dol.full_arg, ';');
		dol->redir_pipe = 0;
	}
	else if ((str[s->i] == '>' || str[s->i] == '<') && dol->q == 0)
	{
		if (ft_parse_redir(s, dol, str))
			return (1);
	}
	else
		ft_add_symb(dol, s, str);
	return (0);
}

int	ft_parsing(char *input, t_set *s)
{
	ft_dol_struct_init(&s->dol);
	while (input[s->i])
	{
		if (input[s->i] == '\\' )
			ft_parse_slash(&s->dol, s, input);
		else if (input[s->i] == '\'')
			ft_parse_a(&s->dol, s, input);
		else if (input[s->i] == '\"')
			ft_parse_q(&s->dol, s, input);
		else if (input[s->i] == ';' && input[s->i + 1] != '\0' \
									&& s->dol.q == 0 & s->dol.a == 0)
		{
			s->i++;
			return (0);
		}
		else
		{
			if (ft_parsing_2(&s->dol, s, input))
				return (1);
		}
		if (input[s->i])
			s->i++;
	}
	g_exit = 0;
	return (0);
}
