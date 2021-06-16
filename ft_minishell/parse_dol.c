/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 19:44:41 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/15 17:20:05 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_env(t_set *s, int j)
{
	int		i;
	char	*tmp;

	i = 0;
	while (s->env[i])
	{
		if (!(ft_strncmp(s->env[i], s->dol.env_var, j)) \
													&& (s->env[i][j] == '='))
		{
			s->dol.path = ft_strdup(s->env[i] + j + 1);
			tmp = ft_strdup(s->dol.full_arg);
			free(s->dol.full_arg);
			s->dol.full_arg = ft_strjoin_dol(tmp, s->dol.path);
			free(tmp);
			free(s->dol.path);
			free(s->dol.env_var);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_not_found_in_env(t_set *s, int *len, char *str)
{
	char	*tmp;

	free(s->dol.env_var);
	*len = ft_strlen(s->dol.full_arg);
	if (s->dol.full_arg[*len] == ' ' && s->dol.q == 0)
	{
		tmp = ft_strndup(s->dol.full_arg, *len - 1);
		free(s->dol.full_arg);
		s->dol.full_arg = ft_strdup(tmp);
		free(tmp);
		return ;
	}
	else if (str[s->i + 1] == ' ')
		while (str[s->i++] == ' ')
			;
}

int	ft_check_symb_aft_dol(t_dol *dol, t_set *s, char *str, int *j)
{	
	char	*tmp;

	dol->env_var = ft_strdup("");
	while (str[s->i] && (ft_isalnum(str[s->i]) || str[s->i] == '_'))
	{
		if ((ft_isdigit(str[s->i])) && *j == 0)
		{
			dol->digit_aft_dol = 1;
			free(dol->env_var);
			return (0);
		}
		tmp = ft_strdup(dol->env_var);
		free(dol->env_var);
		dol->env_var = ft_strjoin_symb(tmp, str[s->i]);
		free(tmp);
		s->i++;
		*j += 1;
	}
	s->i--;
	return (1);
}

void	ft_slash_in_dol(t_set *s, char *str)
{
	char	*tmp;

	tmp = ft_strdup(s->dol.full_arg);
	free(s->dol.full_arg);
	s->dol.full_arg = ft_strjoin_symb(tmp, str[s->i]);
	free(tmp);
	return ;
}

void	ft_err_nmb(t_set *s)
{
	char	*ch_error;
	char	*tmp;

	s->i++;
	ch_error = ft_itoa(g_exit);
	tmp = ft_strdup(s->dol.full_arg);
	free(s->dol.full_arg);
	s->dol.full_arg = ft_strjoin_dol(tmp, ch_error);
	free(ch_error);
	free(tmp);
}
