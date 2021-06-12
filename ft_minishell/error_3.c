/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:03:31 by rburton           #+#    #+#             */
/*   Updated: 2021/06/11 22:30:01 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_syntax_error_near_unexpected_token(t_set *s, int pi, int ci)
{
	write(1, "minishell: ", 11);
	write(1, "syntax error near unexpected token `", 36);
	write(1, s->st[pi].pln[ci].cmd[1], ft_strlen(s->st[pi].pln[ci].cmd[1]));
	write(1, "'", 1);
	g_exit = 258;
}

void	err_syntax_error_quotes_not_closed(void)
{
	write(1, "minishell: ", 11);
	write(1, "syntax error quotes not closed\n", 31);
	g_exit = 258;
}

void	err_unxpected_backslash_at_the_end(void)
{
	write(1, "minishell: ", 11);
	write(1, "syntax error unxpected backslash at the end\n", 44);
	g_exit = 258;
}

void	err_cannot_access_parent_directories(t_set *s, int pi, int ci)
{
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "error retrieving current directory: ", 36);
	write(1, "getcwd: cannot access parent directories: ", 42);
	write(1, "No such file or directory\n", 26);
	g_exit = 0;
}
