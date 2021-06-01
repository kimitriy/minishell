/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:42:55 by rburton           #+#    #+#             */
/*   Updated: 2021/05/31 22:12:22 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	parse_spaces(t_set *s, char *str, int pi, int ci)
// {
// 	char	**cmd_tmp; //2d arr, first line is a command itself and following are args
// 	char	*tmp;
// 	int		n; //number of elements in command
// 	int		i; //index of elements in command

// 	cmd_tmp = ft_split(str, ' ');
// 	// print2darr(cmd_tmp, 0);
// 	n = 0;
// 	while (cmd_tmp[n] != NULL)
// 		n++;
// 	s->st[pi].pln[ci].cmd = (char**)calloc(n + 1, sizeof(char*));
// 	i = 0;
// 	while (i < n)
// 	{
// 		tmp = cmd_tmp[i];
// 		cmd_tmp[i] = ft_strtrim(cmd_tmp[i], " ");
// 		free(tmp);
// 		s->st[pi].pln[pi].n = n;
// 		s->st[pi].pln[ci].cmd[i] = ft_strdup(cmd_tmp[i]);
// 		i++;
// 	}
// 	s->st[pi].pln[ci].cmd[i] = NULL;
// 	// print2darr(s->st[pi].pln[ci].cmd, 0);
// 	ft_free(cmd_tmp);
// }

void	parse_spaces(t_set *s, char *str, int pi, int ci)
{
	char	**cmd_tmp; //2d arr, first line is a command itself and following are args
	char	*tmp;
	int		n; //number of elements in command
	int		i; //index of elements in command

	cmd_tmp = ft_split(str, ' ');
	n = 0;
	while (cmd_tmp[n] != NULL)
		n++;
	s->st[pi].pln[ci].n = n;
	s->st[pi].pln[ci].cmd = (char**)calloc(n + 1, sizeof(char*));
	i = 0;
	while (i < n)
	{
		tmp = cmd_tmp[i];
		cmd_tmp[i] = ft_strtrim(cmd_tmp[i], " ");
		free(tmp);
		s->st[pi].pln[ci].n = n;
		s->st[pi].pln[ci].cmd[i] = ft_strdup(cmd_tmp[i]);
		free(cmd_tmp[i]);
		i++;
	}
	s->st[pi].pln[ci].cmd[i] = NULL;
	free(cmd_tmp);
}

void	parse_pipes(t_set *s, char *str, int pi)
{
	char	**pln_tmp; //2d arr, each line is a command with its args
	char	*tmp;
	int		n; //number of elements in pipeline
	int		i; //index of elements in pipeline

	pln_tmp = ft_split(str, '|');
	n = 0;
	while (pln_tmp[n] != NULL)
		n++;
	s->st[pi].pln = (t_cmnd*)calloc(n, sizeof(t_cmnd));
	i = 0;
	while (i < n)
	{
		tmp = pln_tmp[i];
		pln_tmp[i] = ft_strtrim(pln_tmp[i], " ");
		free(tmp);
		s->st[pi].cn = n;
		s->st[pi].pln[i].cmd_tmp = ft_strdup(pln_tmp[i]);
		free(pln_tmp[i]);
		parse_spaces(s, s->st[pi].pln[i].cmd_tmp, pi, i);
		free(s->st[pi].pln[i].cmd_tmp);
		i++;
	}
	free(pln_tmp);
}

void	parse_semicolons(t_set *s, char *str)
{
	char	**set_tmp; //2d arr, each line is a pipeline string
	char	*tmp;
	int		n; //number of elements in set
	int		i; //index of elements in set

	set_tmp = ft_split(str, ';');
	n = 0;
	while (set_tmp[n] != NULL)
		n++;
	s->pn = n;
	s->st = (t_ppline*)calloc(n, sizeof(t_ppline));
	i = 0;
	while (i < n)
	{
		tmp = set_tmp[i];
		set_tmp[i] = ft_strtrim(set_tmp[i], " ");
		free(tmp);
		s->st[i].pln_tmp = ft_strdup(set_tmp[i]);
		free(set_tmp[i]);
		parse_pipes(s, s->st[i].pln_tmp, i);
		free(s->st[i].pln_tmp);
		i++;
	}
	free(set_tmp);
}

void	mini_prsr(t_set *s, char *str)
{
	parse_semicolons(s, str);
}