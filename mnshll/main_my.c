/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_my.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 17:48:17 by rburton           #+#    #+#             */
/*   Updated: 2021/06/02 00:34:43 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	null_tcmnd(t_cmnd *cmd, int n)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < n)
	{
		while (cmd->cmd[i][j])
		{
			cmd->cmd[i][j] = '\0';
			j++;
		}
		i++;
		j = 0;
	}
	cmd->cmd[i] = NULL;
}

void	make_env(t_set *s, char **envp)
{
	int		i; //index of lines in envp

	s->en = 0;
	while (envp[s->en] != NULL)
		s->en++;
	s->env = ft_calloc(s->en + 1, sizeof(char*));
	i = 0;
	while (i < s->en)
	{
		if (0 == ft_strncmp(envp[i], "OLDPWD=", 7))
			s->env[i] = ft_strdup("OLDPWD");
		// else if (0 == ft_strncmp(envp[i], "SHLVL=", 6))
		// {
		// 	s->shlvl = 2;
		// 	s->env[i] = ft_strdup("SHLVL=2");
		// }
		else
			s->env[i] = ft_strdup(envp[i]);
		i++;
	}
	s->env[i] = NULL;
	// print2darr(s->env, 0);
}
