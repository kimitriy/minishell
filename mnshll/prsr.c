/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:42:55 by rburton           #+#    #+#             */
/*   Updated: 2021/05/06 22:07:41 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_spaces(t_set *s, char *str, int pi, int ci)
{
	char	**cmnd_tmp; //2d arr, first line is a command itself and following are args
	int		n; //number of elements in command
	int		i; //index of elements in command

	cmnd_tmp = ft_split(str, ' ');
	// print2darr(cmnd_tmp);
	n = 0;
	while (cmnd_tmp[n] != NULL)
		n++;
	if (!(s->set[pi].ppline[ci].cmnd = (char**)malloc(n * sizeof(char*))))
			err_message("s->set[si].ppline[pi].cmnd malloc error");
	i = -1;
	while (++i < n)
	{
		cmnd_tmp[i] = ft_strtrim(cmnd_tmp[i], " ");
		s->set[pi].ppline[pi].n = n;
		int len = ft_strlen(cmnd_tmp[i]);
		if (!(s->set[pi].ppline[ci].cmnd[i] = (char*)malloc((len + 1) * sizeof(char))))
			err_message("s->set[si].ppline[pi].cmnd[i] malloc error");
		ft_strcpy(s->set[pi].ppline[ci].cmnd[i], cmnd_tmp[i]);
	}
	s->set[pi].ppline[ci].cmnd[i] = NULL;
	// print2darr(s->set[si].ppline[pi].cmnd);
	free(cmnd_tmp);
}

void	parse_pipes(t_set *s, char *str, int pi)
{
	char	**ppln_tmp; //2d arr, each line is a command with its args
	int		n; //number of elements in pipeline
	int		i; //index of elements in pipeline

	// printf("parse_pipes: str: %s, si: %d\n", str, si);
	ppln_tmp = ft_split(str, '|');
	// print2darr(ppln_tmp);
	n = 0;
	while (ppln_tmp[n] != NULL)
		n++;
	if (!(s->set[pi].ppline = (t_cmnd*)malloc(n * sizeof(t_cmnd))))
			err_message("s->set[si].ppline malloc error");
	i = -1;
	while (++i < n)
	{
		ppln_tmp[i] = ft_strtrim(ppln_tmp[i], " ");
		s->set[pi].cn = n;
		int len = ft_strlen(ppln_tmp[i]);
		if (!(s->set[pi].ppline[i].cmnd_tmp = (char*)malloc((len + 1) * sizeof(char))))
			err_message("s->set[si].ppline[i].cmnd_tmp malloc error");
		ft_strcpy(s->set[pi].ppline[i].cmnd_tmp, ppln_tmp[i]);
		// printf("parse_pipes: ppln_tmp[%d]: %s\n", i, ppln_tmp[i]);
		// printf("parse_pipes: s->set[%d].ppline[%d].cmnd_tmp: %s\n", si, i, s->set[si].ppline[i].cmnd_tmp);
		parse_spaces(s, s->set[pi].ppline[i].cmnd_tmp, pi, i);
	}
	free(ppln_tmp);
}

void	parse_semicolons(t_set *s, char *str)
{
	char	**set_tmp; //2d arr, each line is a pipeline string
	int		n; //number of elements in set
	int		i; //index of elements in set

	set_tmp = ft_split(str, ';');
	// print2darr(set_tmp);
	n = 0;
	while (set_tmp[n] != NULL)
		n++;
	s->pn = n;
	if (!(s->set = (t_ppline*)malloc(n * sizeof(t_ppline)))) //allocates memory for n elements of set
		err_message("s->set malloc error");
	i = -1;
	while (++i < n)
	{
		set_tmp[i] = ft_strtrim(set_tmp[i], " ");
		int len = ft_strlen(set_tmp[i]);
		if (!(s->set[i].ppln_tmp = (char*)malloc((len + 1) * sizeof(char)))) //allocates memory for parsed string
			err_message("s->set malloc error");
		ft_strcpy(s->set[i].ppln_tmp, set_tmp[i]);
		// printf("parse_semicolons: s->set[%d].ppln_tmp: <%s>\n", i, s->set[i].ppln_tmp);
		parse_pipes(s, s->set[i].ppln_tmp, i);
	}
	free(set_tmp);
}

void	mini_prsr(t_set *s, char *str)
{
	parse_semicolons(s, str);
	
}