/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 21:06:03 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/14 21:25:34 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup_filename(t_dol *dol)
{	
	if (dol->red_in)//+++++
		dol->from_file = ft_strdup("");//++++++
	if (dol->red_out || dol->red_app)//+++++++
		dol->to_file = ft_strdup("");//+++++++
}

void	ft_output_file(t_set *s, t_dol *dol, char *str)
{
	char	*tmp;

	tmp = ft_strdup(dol->to_file);
	free (dol->to_file);
	dol->to_file = ft_strjoin_symb(tmp, str[s->i]);
	free(tmp);
}

void	get_file_name(t_set *s, t_dol *dol, char *str)
{
	char	*tmp;

	if (dol->red_app || dol->red_out)
		ft_output_file(s, dol, str);
	else if (dol->red_in)
	{
		tmp = ft_strdup(dol->from_file);
		free(dol->from_file);
		dol->from_file = ft_strjoin_symb(tmp, str[s->i]);
		free(tmp);
	}
	return ;
}
