/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 08:33:31 by rburton           #+#    #+#             */
/*   Updated: 2021/06/01 17:16:33 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_tilda(t_set *s, int pi, int ci)
{
	(void)pi;
	(void)ci;

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
	return(path);
}

char	*cd_minus(t_set *s, int pi, int ci)
{
	char	**opwd_ptr;
	char	*path;
	char	*tmp;

	opwd_ptr = NULL;
	path = NULL;
	opwd_ptr = key_in_arr(s->env, "OLDPWD");
	if (opwd_ptr == NULL)
		err_oldpwd_not_set(s, pi, ci);
	else
	{
		path = ft_strdup(*opwd_ptr);
		tmp = path;
		path = ft_strtrim(path, "OLDPWD=");
		free(tmp);
	}
	return(path);
}

char	*cd_home(t_set *s, int pi, int ci)
{
	char	**ptr;
	char	*path;
	char	*tmp;

	write(1, "cd_home()\n", 10);
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

char	*set_path(t_set *s, int pi, int ci)
{
	if (s->st[pi].pln[ci].cmd[1] != NULL)
	{
		if (s->st[pi].pln[ci].cmd[1][0] == '~')
			return(cd_tilda(s, pi, ci));
		else if (s->st[pi].pln[ci].cmd[1][0] == '-' && s->st[pi].pln[ci].cmd[1][1] == '\0')
			return(cd_minus(s, pi, ci));
		else if (s->st[pi].pln[ci].cmd[1][0] == '#' || ft_strncmp(s->st[pi].pln[ci].cmd[1], "--", 2) == 0)
			return(cd_home(s, pi, ci));
		else
			return(cd_freepath(s, pi, ci));
	}
	else
		return(cd_home(s, pi, ci));
}

void	update_pwd(t_set *s)
{
	char	**pwd_ptr;
	char	**opwd_ptr;
	char	**prsd_tmp;
	char	*opwd_str;
	char	*pwd_str;
	char	*tmp_getcwd;
	char	*tmp_leak;

	opwd_ptr = key_in_arr(s->env, "OLDPWD");
	pwd_ptr = key_in_arr(s->env, "PWD");
	opwd_str = ft_strdup("OLDPWD=");
	prsd_tmp = parse_arg(*pwd_ptr);
	tmp_leak = opwd_str;
	opwd_str = ft_strjoin(opwd_str, prsd_tmp[1]);
	free(tmp_leak);
	str_ovrwrite(opwd_ptr, opwd_str);
	free(opwd_str);
	pwd_str = ft_strdup("PWD=");
	tmp_getcwd = getcwd(NULL, 0);
	tmp_leak = pwd_str;
	pwd_str = ft_strjoin(pwd_str, tmp_getcwd);
	free(tmp_leak);
	str_ovrwrite(pwd_ptr, pwd_str);
	free(pwd_str);
	free(tmp_getcwd);
	ft_free_str(prsd_tmp);
}

void	bltn_cd(t_set *s, int pi, int ci)
{
	//cd - (PWD / OLDPWD)
	//cd / cd ~ / cd #
	
	int		err_num;
	int		chdir_err;


	
	char	*path;

	errno = 0;
	path = set_path(s, pi, ci);
	chdir_err = chdir(path);
	if (chdir_err != 0)
	{
		err_num = errno;
		printf("%s", strerror(err_num));
	}
	free(path);
	update_pwd(s);
	bltn_pwd(s);
}