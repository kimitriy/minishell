/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniprsr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:42:55 by rburton           #+#    #+#             */
/*   Updated: 2021/04/15 23:21:49 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_spaces(t_set *s, char *str, int si, int pi)
{
	char	**cmnd_tmp; //2d arr, first line is a command itself and following are args
	int		n; //number of elements in command
	int		i; //index of elements in command

	cmnd_tmp = ft_split(str, ' ');
	// print2darr(cmnd_tmp);
	n = 0;
	while (cmnd_tmp[n] != NULL)
		n++;
	s->set->ppline->n = n;
	if (!(s->set[si].ppline[pi].cmnd = (char**)malloc(n * sizeof(char*))))
			err_message("s->set[si].ppline[pi].cmnd malloc error");
	i = -1;
	while (++i < n)
	{
		if (!(s->set[si].ppline[pi].cmnd[i] = (char*)malloc(ft_strlen(cmnd_tmp[i]) * sizeof(char))))
			err_message("s->set[si].ppline[pi].cmnd[i] malloc error");
		ft_strcpy(s->set[si].ppline[pi].cmnd[i], cmnd_tmp[i]);
	}
	s->set[si].ppline[pi].cmnd[i] = NULL;
	// print2darr(s->set[si].ppline[pi].cmnd);
	free(cmnd_tmp);
}

void	parse_pipes(t_set *s, char *str, int si)
{
	char	**ppln_tmp; //2d arr, each line is a command with its args
	int		n; //number of elements in pipeline
	int		i; //index of elements in pipeline

	ppln_tmp = ft_split(str, '|');
	// print2darr(ppln_tmp);
	n = 0;
	while (ppln_tmp[n] != NULL)
		n++;
	s->set->pn = n;
	if (!(s->set[si].ppline = (t_cmnd*)malloc(n * sizeof(t_cmnd))))
			err_message("s->set[si].ppline malloc error");
	i = -1;
	while (++i < n)
	{
		if (!(s->set[si].ppline[i].cmnd_tmp = (char*)malloc(ft_strlen(ppln_tmp[i]) * sizeof(char))))
			err_message("s->set[si].ppline[i].cmnd_tmp malloc error");
		ppln_tmp[i] = ft_strtrim(ppln_tmp[i], " ");
		ft_strcpy(s->set[si].ppline[i].cmnd_tmp, ppln_tmp[i]);
		parse_spaces(s, s->set[si].ppline[i].cmnd_tmp, si, i);
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
	s->sn = n;
	if (!(s->set = (t_ppline*)malloc(n * sizeof(t_ppline)))) //allocates memory for n elements of set
		err_message("s->set malloc error");
	i = -1;
	while (++i < n)
	{
		if (!(s->set[i].ppln_tmp = (char*)malloc(ft_strlen(set_tmp[i]) * sizeof(char)))) //allocates memory for parsed string
			err_message("s->set malloc error");
		ft_strcpy(s->set[i].ppln_tmp, set_tmp[i]);
		parse_pipes(s, s->set[i].ppln_tmp, i);
	}
	free(set_tmp);
}



void	mini_prsr(t_set *s, char *str)
{
	parse_semicolons(s, str);
	
}