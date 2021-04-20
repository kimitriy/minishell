/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:19:44 by rburton           #+#    #+#             */
/*   Updated: 2021/04/20 18:10:39 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mnshll_execute(t_set *s)
{
	int		si;
	int		pi;
	char	*bltins[7] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit"
	};
	si = -1;
	while (++si < s->sn)
	{
		pi = -1;
		while (++pi < s->set[si].pn)
			if (NULL != str_in_arr(bltins, s->set[si].ppline[pi].cmnd[0]))
				bltn_node(s);
			else
				cmnd_node(s);
	}
}