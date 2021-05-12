/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:42:55 by rburton           #+#    #+#             */
/*   Updated: 2021/05/11 15:57:52 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_spaces(t_set *s, char *str, int pi, int ci)
{
	char	**cmd_tmp; //2d arr, first line is a command itself and following are args
	int		n; //number of elements in command
	int		i; //index of elements in command

	cmd_tmp = ft_split(str, ' ');
	// print2darr(cmd_tmp, 0);
	n = 0;
	while (cmd_tmp[n] != NULL)
		n++;
	if (!(s->st[pi].pln[ci].cmd = (char**)malloc(n * sizeof(char*))))
			err_message("s->st[si].pln[pi].cmd malloc error");
	i = -1;
	while (++i < n)
	{
		cmd_tmp[i] = ft_strtrim(cmd_tmp[i], " ");
		s->st[pi].pln[pi].n = n;
		int len = ft_strlen(cmd_tmp[i]);
		if (!(s->st[pi].pln[ci].cmd[i] = (char*)malloc((len + 1) * sizeof(char))))
			err_message("s->st[si].pln[pi].cmd[i] malloc error");
		ft_strcpy(s->st[pi].pln[ci].cmd[i], cmd_tmp[i]);
	}
	s->st[pi].pln[ci].cmd[i] = NULL;
	// print2darr(s->st[pi].pln[ci].cmd, 0);
	free(cmd_tmp);
}

void	parse_pipes(t_set *s, char *str, int pi)
{
	char	**pln_tmp; //2d arr, each line is a command with its args
	int		n; //number of elements in pipeline
	int		i; //index of elements in pipeline

	// printf("parse_pipes: str: %s, si: %d\n", str, si);
	pln_tmp = ft_split(str, '|');
	// print2darr(pln_tmp, 0);
	n = 0;
	while (pln_tmp[n] != NULL)
		n++;
	if (!(s->st[pi].pln = (t_cmnd*)malloc(n * sizeof(t_cmnd))))
			err_message("s->st[si].pln malloc error");
	i = -1;
	while (++i < n)
	{
		pln_tmp[i] = ft_strtrim(pln_tmp[i], " ");
		s->st[pi].cn = n;
		int len = ft_strlen(pln_tmp[i]);
		if (!(s->st[pi].pln[i].cmd_tmp = (char*)malloc((len + 1) * sizeof(char))))
			err_message("s->st[si].pln[i].cmd_tmp malloc error");
		ft_strcpy(s->st[pi].pln[i].cmd_tmp, pln_tmp[i]);
		// printf("parse_pipes: pln_tmp[%d]: %s\n", i, pln_tmp[i]);
		// printf("parse_pipes: s->st[%d].pln[%d].cmd_tmp: %s\n", pi, i, s->st[pi].pln[i].cmd_tmp);
		parse_spaces(s, s->st[pi].pln[i].cmd_tmp, pi, i);
	}
	free(pln_tmp);
}

void	parse_semicolons(t_set *s, char *str)
{
	char	**set_tmp; //2d arr, each line is a pipeline string
	int		n; //number of elements in set
	int		i; //index of elements in set

	set_tmp = ft_split(str, ';');
	// print2darr(set_tmp, 0);
	n = 0;
	while (set_tmp[n] != NULL)
		n++;
	s->pn = n;
	if (!(s->st = (t_ppline*)malloc(n * sizeof(t_ppline)))) //allocates memory for n elements of set
		err_message("s->set malloc error");
	i = -1;
	while (++i < n)
	{
		set_tmp[i] = ft_strtrim(set_tmp[i], " ");
		int len = ft_strlen(set_tmp[i]);
		if (!(s->st[i].pln_tmp = (char*)malloc((len + 1) * sizeof(char)))) //allocates memory for parsed string
			err_message("s->set malloc error");
		ft_strcpy(s->st[i].pln_tmp, set_tmp[i]);
		// printf("parse_semicolons: s->st[%d].pln_tmp: <%s>\n", i, s->st[i].pln_tmp);
		parse_pipes(s, s->st[i].pln_tmp, i);
	}
	free(set_tmp);
}

void	mini_prsr(t_set *s, char *str)
{
	parse_semicolons(s, str);
	
}