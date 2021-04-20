/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 17:48:17 by rburton           #+#    #+#             */
/*   Updated: 2021/04/20 18:11:14 by rburton          ###   ########.fr       */
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

	n = 0;
	while (envp[n] != NULL)
		n++;
	s->en = n;
	if (!(s->env = (char**)malloc(n * sizeof(char*))))
		err_message("env malloc error");
	i = -1;
	while (++i < n)
	{
		l = ft_strlen(envp[i]);
		if (!(s->env[i] = (char*)malloc((l + 1) * sizeof(char))))
			err_message("env malloc error");
		ft_strcpy(s->env[i], envp[i]);
	}
}

int		mnshll_loop(t_set *s)
{
	
	while (1)
	{
		// char	*str = "cmnd1 arg arg | cmnd2 arg | cmnd3 arg; cmnd4 arg arg | cmnd5 arg; cmnd6 arg | cmnd7 arg";
		char	*str = "cd";

		mini_prsr(s, str); //makes set
		mnshll_execute(s);
	}
}

int		main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_set	*s;

	if (!(s = (t_set*)malloc(1 * sizeof(t_set))))
		err_message("t_big malloc error");
	make_env(s, envp); //makes env
	mnshll_loop(s);

	return (0);
}