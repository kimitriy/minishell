/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 08:33:31 by rburton           #+#    #+#             */
/*   Updated: 2021/06/11 21:46:51 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_path(t_set *s, int pi, int ci)
{
	if (s->st[pi].pln[ci].cmd[1] != NULL)
	{
		if (s->st[pi].pln[ci].cmd[1][0] == '~')
			return (cd_tilda(s));
		else if (s->st[pi].pln[ci].cmd[1][0] == '-' &&
		s->st[pi].pln[ci].cmd[1][1] == '\0')
			return (cd_minus(s, pi, ci));
		else if (s->st[pi].pln[ci].cmd[1][0] == '#' ||
		ft_strncmp(s->st[pi].pln[ci].cmd[1], "--", 2) == 0)
			return (cd_home(s, pi, ci));
		else
			return (cd_freepath(s, pi, ci));
	}
	else
		return (cd_home(s, pi, ci));
}

void	updt_pwd_assist(char **pwd_ptr, char *str1, char *str2)
{	
	char	*pwd_str;
	char	*leak_tmp;

	pwd_str = ft_strdup(str1);
	leak_tmp = pwd_str;
	pwd_str = ft_strjoin(pwd_str, str2);
	free(leak_tmp);
	str_ovrwrite(pwd_ptr, pwd_str);
	free(pwd_str);
}

void	update_pwd(t_set *s)
{
	char	**opwd_ptr;
	char	**pwd_ptr;
	char	**prsd_tmp;
	char	*getcwd_tmp;

	opwd_ptr = key_in_arr(s->env, "OLDPWD");
	pwd_ptr = key_in_arr(s->env, "PWD");
	prsd_tmp = parse_arg(*pwd_ptr);
	getcwd_tmp = getcwd(NULL, 0);
	updt_pwd_assist(opwd_ptr, "OLDPWD=", prsd_tmp[1]);
	updt_pwd_assist(pwd_ptr, "PWD=", getcwd_tmp);
	free(getcwd_tmp);
	ft_free_str(prsd_tmp);
}

void	bltn_cd(t_set *s, int pi, int ci)
{
	int		chdir_err;
	char	*path;
	int		path_flg;

	errno = 0;
	path = set_path(s, pi, ci);
	if (path == NULL)
		return ;
	path_flg = path_does_exist(s, path);
	if (path_flg == 0 && ft_strncmp(path, "..", 2) == 0)
	{
		err_cannot_access_parent_directories(s, pi, ci);
		return ;
	}
	else
	{
		chdir_err = chdir(path);
		if (chdir_err != 0)
			err_no_such_file_or_directory(s, pi, ci);
	}
	free(path);
	update_pwd(s);
	if (s->cd_minus == 1)
		bltn_pwd(s);
}
