/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 18:57:30 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/11 23:11:48 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_get_file_name(t_set *s, t_dol *dol, char *str)
{
	dol->to_file = ft_strdup("");
	dol->from_file = ft_strdup("");
	if (str[s->i] == '>' && str[s->i + 1] == '>')
	{
		s->i += 1;
		dol->red_app = 1;
		dol->redir_pipe = 1;
	}
	else if (str[s->i] == '>')
	{
		dol->red_out = 1;
		dol->redir_pipe = 1;
	}
	else if (str[s->i] == '<')
		dol->red_in = 1;
	s->i++;
	check_spaces(s, str);
	while (str[s->i] != ' ' && str[s->i] != '\0' \
									&& str[s->i] != '|' && str[s->i] != ';')
	{
		get_file_name(s, dol, str);
		s->i++;
	}
	s->i--;
}

int	openning_to_file(t_dol *dol)
{
	if (dol->red_out == 1)
		dol->fd_out = open(dol->to_file, O_CREAT | O_TRUNC | O_RDWR, 0666);
	else if (dol->red_app == 1)
		dol->fd_out = open(dol->to_file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (dol->fd_out == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(1, "\n", 1);
		g_exit = 1;
		return (1);
	}
	return (0);
}

int	openning_from_file(t_dol *dol)
{
	if (dol->red_in)
		dol->fd_in = open(dol->from_file, O_RDONLY, 0666);
	if (dol->fd_in == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(1, "\n", 1);
		g_exit = 1;
		return (1);
	}
	return (0);
}

int	open_file(t_dol *dol)
{
	if (dol->red_out || dol->red_app)
	{
		if (dol->fd_out >= 0)
			close(dol->fd_out);
		if (openning_to_file(dol))
			return (1);
	}	
	else if (dol->red_in)
	{
		if (dol->fd_in >= 0)
			close(dol->fd_in);
		if (openning_from_file(dol))
			return (1);
	}
	dol->red_app = 0;
	dol->red_out = 0;
	dol->red_in = 0;
	return (0);
}

int	ft_parse_redir(t_set *s, t_dol *dol, char *str)
{
	dol->redir = 1;
	ft_redir_get_file_name(s, dol, str);
	if (open_file(dol))
		return (1);
	return (0);
}
