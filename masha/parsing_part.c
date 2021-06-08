/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:13:29 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/08 19:13:31 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_add_symb(t_dol *dol, char *str)
{
	char	*tmp;

	tmp = ft_strdup(dol->full_arg);
	if (dol->full_arg[0] != '\0')
		free (dol->full_arg);
	dol->full_arg = ft_strjoin_symb(tmp, str[dol->i]);
	free (tmp);
	// if (!dol->full_arg)
	// {
	// 	dol->error = 1;
	// 	write(2, "error dol->full_arg = ft_strjoin", 33);// error go to new input
	// }
}

void	ft_parse_space(t_dol *dol, char *str)
{
	char	*tmp;

	if (dol->q == 1) // || str[dol->i + 1] != ' ')
		ft_add_symb(dol, str);
	else
	{
		if (str[dol->i + 1] == ' ')
		{
			while (str[dol->i] == ' ')
				dol->i++;
			dol->i -= 1;
		}
		else if (str[dol->i + 1] == '>' && str[dol->i + 2] == '>')
			dol->i++;
		else if (str[dol->i + 1] == '>' || str[dol->i + 1] == '<')
			return ;
		else if (str[dol->i + 1] != '\0')
			ft_add_symb(dol, str);
	}
}

void	ft_parse_q_slash(t_dol *dol, char *str)
{
	char	*tmp;

	if (str[dol->i + 1] == '$' || str[dol->i + 1] == '\"')
	{
		dol->i += 1;
		ft_add_symb(dol, str);
	}
	else if (str[dol->i + 1] == '\\')
	{
		dol->i++;
		tmp = ft_strdup(dol->full_arg);
		free(dol->full_arg);
		dol->full_arg = ft_strjoin_symb(tmp, str[dol->i]);
		free(tmp);
	}
	else
	{
		tmp = ft_strdup(dol->full_arg);
		free(dol->full_arg);
		dol->full_arg = ft_strjoin_symb(tmp, str[dol->i]);
		free(tmp);
	}
}

void	ft_parse_a(t_dol *dol, char *str)
{
	char	*tmp;

	if (dol->q == 0)
	{
		dol->i++;
		while (str[dol->i] != '\'' && str[dol->i])
		{
			tmp = ft_strdup(dol->full_arg);
			if (dol->full_arg[0] != '\0')
				free (dol->full_arg);
			dol->full_arg = ft_strjoin_symb(tmp, str[dol->i]);
			// if (!dol->full_arg)
			// {
			// 	dol->error = 1;
			// 	write(2, "error ft_parse_a dol->full_arg = ft_strjoin", 43);// error go to new input
			// }
			free(tmp);
			dol->i++;
		}
	}
	else
		return ;
}

void	ft_parse_q(t_dol *dol, t_set *s, char *str)
{
	// char	*tmp;
	int		slash;

	dol->q = 1;
	dol->i++;
	while ((!(str[dol->i - 1] == '\\' && str[dol->i] == '\"')) \
										&& str[dol->i] != '\"' && str[dol->i])
	{
		if (str[dol->i] == ' ')
			ft_parse_space(dol, str);
		else if (str[dol->i] == '$')
			ft_parse_dol(s, str);
		else if (str[dol->i] == '\\')
			ft_parse_q_slash(dol, str);
		else
			ft_add_symb(dol, str);
		dol->i++;
	}
	dol->q = 0;
}
