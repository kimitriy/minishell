/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 19:44:41 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/08 15:30:29 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_env(t_set *s, int j)
{
	int		i;
	char	*tmp;

	i = 0;
	printf("CHECKING ENV\n");
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
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_not_found_in_env(t_set *s, int *len, char *tmp)	
{
	free(s->dol.env_var);
	*len = ft_strlen(s->dol.full_arg);
	if (s->dol.full_arg[*len] == ' ' && s->dol.q == 0)// len - 1 && str[dol->i] == '\0')
	{
		tmp = ft_strndup(s->dol.full_arg, *len - 1);
		free(s->dol.full_arg);
		s->dol.full_arg = ft_strdup(tmp);
		free(tmp);
		return ;
	}
	else if (str[s->dol.i + 1] == ' ')
		while (str[s->dol.i++] == ' ')
			;
}

int	ft_check_symb_aft_dol(t_dol *dol, char *str, int *j)
{	
	char	*tmp;

	dol->env_var = ft_strdup("");
	while (str[dol->i] && (ft_isalnum(str[dol->i]) || str[dol->i] == '_'))
	{
		if ((ft_isdigit(str[dol->i])) && *j == 0)
		{
			dol->digit_aft_dol = 1;
			return (0);
		}
		tmp = ft_strdup(dol->env_var);
		if (dol->env_var[0] != '\0')
			free(dol->env_var);
		dol->env_var = ft_strjoin_symb(tmp, str[dol->i]);
		free(tmp);
		dol->i++;
		*j += 1;
	}
	dol->i--;
	return (1);
}

void	ft_slash_in_dol(t_set *s, char *tmp)
{
	tmp = ft_strdup(s->dol.full_arg);
	free(s->dol.full_arg);
	s->dol.full_arg = ft_strjoin_symb(tmp, str[s->dol.i]);
	free(tmp);
	return ;
}

void	ft_err_nmb(t_set *s, char *str, char *tmp)
{
	char	*ch_error;

	s->dol.i++;
	ch_error = ft_itoa(g_exit);
	tmp = ft_strdup(s->dol.full_arg);
	free(s->dol.full_arg);
	s->dol.full_arg = ft_strjoin_dol(tmp, ch_error);
	free(ch_error);
	free(tmp);
}
