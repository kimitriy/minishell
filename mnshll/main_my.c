/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_my.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 17:48:17 by rburton           #+#    #+#             */
/*   Updated: 2021/05/14 08:02:03 by rburton          ###   ########.fr       */
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
	int		l;

	// print2darr(envp, 0);

	s->en = 0;
	while (envp[s->en] != NULL)
		s->en++;
	s->env = ft_calloc(s->en + 1, sizeof(char*));
	// if (!(s->env = (char**)malloc((n + 1) * sizeof(char*))))
	// 	err_message("env malloc error");
	s->env[s->en] = NULL;
	i = -1;
	while (++i < s->en)
	{
		l = ft_strlen(envp[i]);
		s->env[i] = ft_calloc(l + 1, sizeof(char));
		// if (!(s->env[i] = (char*)malloc((l + 1) * sizeof(char))))
		// 	err_message("env malloc error");
		ft_strcpy(s->env[i], envp[i]);
		// printf("s->env[%d]: %s\n", i, s->env[i]);
	}
	make_exp(s, 0);
}

void	make_exp(t_set *s, int n)
{
	char	**prsd_arg;
	char	*str;
	char	*tmp;
	int		len;
	int		i;
	int		j;

	if (n != 0)
		ft_free(s->exp);
	s->exn = s->en;
	s->exp = calloc(s->exn + 1, sizeof(char*));
	i = -1;
	while (++i < s->exn)
	{
		prsd_arg = parse_arg(s->env[i]);
		s->exp[i] = ft_strdup(prsd_arg[0]);
		len = ft_strlen(prsd_arg[1]);
		str = ft_calloc(len + 3, sizeof(char));
		str[0] = 61;
		str[1] = 34;
		j = -1;
		while (++j < len)
			str[j + 2] = prsd_arg[1][j];
		str[j + 2] = 34;
		tmp = s->exp[i];
		s->exp[i] = ft_strjoin(s->exp[i], str);
		// printf("s->exp[%d]: %s\n", i, s->exp[i]);
		free(tmp);
		free(str);
	}
	s->exp[i] = NULL;
	arr2d_sorted(s->exp, s->exn);
}

// void	save_argv(t_set *s, char *argv0)
// {
// 	int		len;

// 	len = ft_strlen(argv0);
// 	s->argv0 = (char*)malloc((len + 1) * sizeof(char));
// 	if (NULL == s->argv0)
// 		err_message("argv malloc error");
// 	ft_strcpy(s->argv0, argv0);
// }