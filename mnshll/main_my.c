/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_my.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 17:48:17 by rburton           #+#    #+#             */
/*   Updated: 2021/05/09 15:00:54 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	null_tcmnd(t_cmnd *cmnd, int n)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < n)
	{
		while (cmnd->cmnd[i][j])
		{
			cmnd->cmnd[i][j] = '\0';
			j++;
		}
		i++;
		j = 0;
	}
	cmnd->cmnd[i] = NULL;
}

void	make_env(t_set *s, char **envp)
{
	int		n; //number of lines in envp
	int		i; //index of lines in envp
	int		l;

	// print2darr(envp, 0);

	n = 0;
	while (envp[n] != NULL)
		n++;
	s->en = n;
	if (!(s->env = (char**)malloc((n + 1) * sizeof(char*))))
		err_message("env malloc error");
	s->env[n] = NULL;
	i = -1;
	while (++i < n)
	{
		l = ft_strlen(envp[i]);
		if (!(s->env[i] = (char*)malloc((l + 1) * sizeof(char))))
			err_message("env malloc error");
		ft_strcpy(s->env[i], envp[i]);
	}
	make_exp(s);
}

void	make_exp(t_set *s)
{
	s->exp = arr2d_copy(s->env, s->en);
	s->exn = s->en;
	arr2d_sorted(s->exp, s->exn);
}

void	save_argv(t_set *s, char *argv0)
{
	int		len;

	len = ft_strlen(argv0);
	s->argv0 = (char*)malloc((len + 1) * sizeof(char));
	if (NULL == s->argv0)
		err_message("argv malloc error");
	ft_strcpy(s->argv0, argv0);
}