/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 21:02:09 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/06 21:06:51 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_get_file_name(t_dol *dol, char *str)
{
	dol->to_file = ft_strdup("");
	dol->from_file = ft_strdup("");
	if (str[dol->i] == '>' && str[dol->i + 1] == '>')
	{
		dol->i++;
		dol->red_app = 1;
	}
	else if (str[dol->i] == '>')
		dol->red_out = 1;
	else if (str[dol->i] == '<')
		dol->red_in = 1;
	dol->i++;
	check_spaces(dol, str);
	while (str[dol->i] != ' ' && str[dol->i] != '\0' \
									&& str[dol->i] != '|' && str[dol->i] != ';')
	{
		get_file_name(dol, str);
		dol->i++;
	}
}

void	openning_to_file(t_dol *dol)
{
	if (dol->red_out)
		dol->fd_out = open(dol->to_file, O_CREAT | O_RDWR, 0666);
	else if (dol->red_app)
		dol->fd_out = open(dol->to_file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (dol->fd_out == -1)
		write(2, "error openning_to_file", 23);
}

void	openning_from_file(t_dol *dol)
{
	if (dol->red_in)
		dol->fd_in = open(dol->from_file, O_RDONLY, 0666);
	if (dol->fd_in == -1)
		write(2, "error open_file\n", 16);
}

void	open_file(t_dol *dol)
{
	if (dol->red_out || dol->red_app)
	{
		if (dol->fd_out >= 0)
			close(dol->fd_out);
		openning_to_file(dol);
	}	
	else if (dol->red_in)
	{
		if (dol->fd_in >= 0)
			close(dol->fd_in);
		openning_from_file(dol);
	}
	dol->red_app = 0;
	dol->red_out = 0;
	dol->red_in = 0;
}

void	ft_parse_redir(t_dol *dol, char *str)
{
	dol->redir = 1;
	ft_redir_get_file_name(dol, str);
	open_file(dol);
}
