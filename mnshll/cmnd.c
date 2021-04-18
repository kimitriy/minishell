/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:54:12 by rburton           #+#    #+#             */
/*   Updated: 2021/04/18 21:51:16 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmnd_pwd(t_set *s)
{
	int		i;

	i = 0;
	while (i < s->en)
	{
		
	}
}

void	cmnd_node(t_set *s)
{
	int		si;
	int		pi;
	int		i;

	si = 0;
	pi = 0;
	i = 0;
	while (si < s->sn)
	{
		while (pi < s->set[si].pn)
		{
			if (0 == ft_strcmp(s->set[si].ppline[pi].cmnd[0], "echo"))
			{
				printf("echo\n");
			}
			else if (0 == ft_strcmp(s->set[si].ppline[pi].cmnd[0], "cd"))
			{
				printf("cd\n");
			}
			else if (0 == ft_strcmp(s->set[si].ppline[pi].cmnd[0], "pwd"))
			{
				printf("pwd\n");
				cmnd_pwd(s);
			}
			else if (0 == ft_strcmp(s->set[si].ppline[pi].cmnd[0], "export"))
			{
				printf("export\n");
			}
			else if (0 == ft_strcmp(s->set[si].ppline[pi].cmnd[0], "unset"))
			{
				printf("unset\n");
			}
			else if (0 == ft_strcmp(s->set[si].ppline[pi].cmnd[0], "env"))
			{
				printf("env\n");
			}
			else if (0 == ft_strcmp(s->set[si].ppline[pi].cmnd[0], "exit"))
			{
				printf("exit\n");
			}
			pi++;
		}
		pi = 0;
		si++;
	}
}