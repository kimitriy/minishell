/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 08:33:31 by rburton           #+#    #+#             */
/*   Updated: 2021/06/11 21:44:45 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_tilda(t_set *s)
{
	char	*path;
	char	*tmp;
	char	**usr_ptr;
	char	**prsd_tmp;

	usr_ptr = key_in_arr(s->env, "USER");
	prsd_tmp = parse_arg(*usr_ptr);
	path = ft_strdup("/Users/");
	tmp = path;
	path = ft_strjoin(path, prsd_tmp[1]);
	free(tmp);
	ft_free_str(prsd_tmp);
	return (path);
}

char	*cd_minus(t_set *s, int pi, int ci)
{
	char	**opwd_str;
	char	**prsd_opwd;
	char	*path;
	char	*tmp;

	opwd_str = NULL;
	path = NULL;
	opwd_str = key_in_arr(s->env, "OLDPWD");
	prsd_opwd = parse_arg(*opwd_str);
	if (ft_strlen(prsd_opwd[1]) == 0)
		err_oldpwd_not_set(s, pi, ci);
	else
	{
		path = ft_strdup(*opwd_str);
		tmp = path;
		path = ft_strtrim(path, "OLDPWD=");
		free(tmp);
	}
	ft_free_str(prsd_opwd);
	s->cd_minus = 1;
	return (path);
}

char	*cd_home(t_set *s, int pi, int ci)
{
	char	**ptr;
	char	*path;
	char	*tmp;

	ptr = NULL;
	path = NULL;
	ptr = key_in_arr(s->env, "HOME");
	if (ptr == NULL)
		err_home_not_set(s, pi, ci);
	else
	{
		path = ft_strdup(*ptr);
		tmp = path;
		path = ft_strtrim(path, "HOME=");
		free(tmp);
	}
	return (path);
}

char	*cd_freepath(t_set *s, int pi, int ci)
{
	char	*path;

	path = ft_strdup(s->st[pi].pln[ci].cmd[1]);
	return (path);
}
