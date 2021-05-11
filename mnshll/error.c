/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:03:31 by rburton           #+#    #+#             */
/*   Updated: 2021/05/11 01:32:10 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_message(char *error)
{
    write(1, "Error!\n", 7);
	write(1, error, ft_strlen(error));
    write(1, "\n", 1);
    exit(0);
}

void	err_cmnd_not_fnd(t_set *s, int pi, int ci)
{
	int		len;
	
	len = ft_strlen(s->set[pi].ppln[ci].cmnd[0]);
	write(1, "minishell: ",  11);
	write(1, s->set[pi].ppln[ci].cmnd[0], len);
	write(1, ": ", 2);
	write(1, "command not found",  17);
	write(1, "\n", 1);
}