/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 08:33:31 by rburton           #+#    #+#             */
/*   Updated: 2021/06/07 22:46:03 by rburton          ###   ########.fr       */
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
	return (path);
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
	//cd - (PWD / OLDPWD)
	//cd / cd ~ / cd #
	// int		err_num;
	int		chdir_err;
	char	*path;

	errno = 0;
	path = set_path(s, pi, ci);
	chdir_err = chdir(path);
	if (chdir_err != 0)
	{
		err_no_such_file_or_directory(s, pi, ci);
		// err_num = errno;
		// printf("%s", strerror(err_num));
	}
	free(path);
	update_pwd(s);
	bltn_pwd();
}
