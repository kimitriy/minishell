/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 21:06:03 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/08 15:55:47 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_output_file(t_dol *dol, char *str)
{
	char *tmp;

	tmp = ft_strdup(dol->to_file);
	if (dol->to_file[0] != '\0')
		free (dol->to_file);
	dol->to_file = ft_strjoin_symb(tmp, str[dol->i]);
	free(tmp);
}

void	get_file_name(t_dol *dol, char *str)
{
	char	*tmp;

	if (dol->red_app || dol->red_out)
		ft_output_file(dol, str);
	else if (dol->red_in)
	{
		tmp = ft_strdup(dol->from_file);
		if (dol->from_file[0] != '\0')
			free(dol->from_file);
		dol->from_file = ft_strjoin_symb(tmp, str[dol->i]);
		free(tmp);
	}
}
