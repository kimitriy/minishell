/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_my.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 17:48:17 by rburton           #+#    #+#             */
/*   Updated: 2021/06/03 01:08:42 by rburton          ###   ########.fr       */
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

// void	shlvl(t_set *s, int pi, int ci, int lvl)
// {
// 	char	**str;
// 	char	**prsd_str;
// 	char	*dgt;
// 	char	*tmp;
	
// 	if (ft_strcmp(s->st[pi].pln[ci].cmd[0], "minishell") == 0 || ft_strcmp(s->st[pi].pln[ci].cmd[0], "exit") == 0)
// 	{
// 		str = key_in_arr(s->env, "SHLVL");
// 		prsd_str = parse_arg(*str);
// 		write(1, prsd_str[0], ft_strlen(prsd_str[0]));
// 		write(1, "\n", 1);
// 		write(1, prsd_str[1], ft_strlen(prsd_str[1]));
// 		write(1, "\n", 1);
// 		if (lvl == 1 && str == NULL)
// 			s->shlvl = 1;
// 		else if (lvl == 1 && ft_atoi(prsd_str[1]) < 0)
// 			s->shlvl = 0;
// 		else
// 			s->shlvl += lvl;
// 		if (str != NULL)
// 			free(*str);
// 		dgt = ft_itoa(s->shlvl);
// 		*str = ft_strdup("SHLVL=");
// 		tmp = *str;
// 		*str = ft_strjoin(*str, dgt);
// 		free(tmp);
// 		free(dgt);
// 		ft_free_str(prsd_str);
// 	}
// }

void	shlvl(t_set *s)
{
	char	**str;
	char	**prsd_str;
	char	*dgt;
	char	*tmp;
	
	str = key_in_arr(s->env, "SHLVL");
	prsd_str = parse_arg(*str);
	s->shlvl = ft_atoi(prsd_str[1]);
	if (str == NULL)
		s->shlvl = 1;
	else if (s->shlvl < 0)
		s->shlvl = 0;
	else
		s->shlvl++;
	if (str != NULL)
		free(*str);
	dgt = ft_itoa(s->shlvl);
	*str = ft_strdup("SHLVL=");
	tmp = *str;
	*str = ft_strjoin(*str, dgt);
	free(tmp);
	free(dgt);
	ft_free_str(prsd_str);
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
	shlvl(s);
}
