/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 08:33:31 by rburton           #+#    #+#             */
/*   Updated: 2021/05/19 07:23:09 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_tilda(t_set *s, int pi, int ci)
{
	// (void)s;
	(void)pi;
	(void)ci;

	char	*path;
	char	**usr_ptr;
	char	**prsd_tmp;

	usr_ptr = key_in_arr(s->env, "USER");
	prsd_tmp = parse_arg(*usr_ptr);
	path = ft_strdup("/Users/");
	path = ft_strjoin(path, prsd_tmp[1]);

	// write(1, "cd_tilda\n", 9);
	// write(1, "cd_tilda\n", 9);
	return(path);
}

char	*cd_minus(t_set *s, int pi, int ci)
{
	char	**opwd_ptr;
	char	*path;

	opwd_ptr = NULL;
	path = NULL;
	opwd_ptr = key_in_arr(s->env, "OLDPWD");
	if (opwd_ptr == NULL)
		err_oldpwd_not_set(s, pi, ci);
	else
	{
		path = ft_strdup(*opwd_ptr);
		path = ft_strtrim(path, "OLDPWD=");
	}
	return(path);
}

char	*cd_home(t_set *s, int pi, int ci)
{
	char    **ptr;
	char	*path;

	ptr = NULL;
	path = NULL;
	ptr = key_in_arr(s->env, "HOME");
	if (ptr == NULL)
		err_home_not_set(s, pi, ci);
	else
	{
		path = ft_strdup(*ptr);
		path = ft_strtrim(path, "HOME=");
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

	opwd_ptr = key_in_arr(s->env, "OLDPWD");
	pwd_ptr = key_in_arr(s->env, "PWD");

	write(1, "BEFORE:\n", 8);
	write(1, "opwd_ptr: ", 10);
	write(1, *opwd_ptr, ft_strlen(*opwd_ptr));
	write(1, "\n", 1);
	write(1, "pwd_ptr: ", 9);
	write(1, *pwd_ptr, ft_strlen(*pwd_ptr));
	write(1, "\n", 1);

	opwd_str = ft_strdup("OLDPWD=");
	prsd_tmp = parse_arg(*pwd_ptr);
	opwd_str = ft_strjoin(opwd_str, prsd_tmp[1]);
	str_ovrwrite(opwd_ptr, opwd_str);

	pwd_str = ft_strdup("PWD=");
	pwd_str = ft_strjoin(pwd_str, getcwd(NULL, 0));
	str_ovrwrite(pwd_ptr, pwd_str);

	write(1, "AFTER:\n", 7);
	write(1, "opwd_ptr: ", 10);
	write(1, *opwd_ptr, ft_strlen(*opwd_ptr));
	write(1, "\n", 1);
	write(1, "pwd_ptr: ", 9);
	write(1, *pwd_ptr, ft_strlen(*pwd_ptr));
	write(1, "\n", 1);
	
	// make_exp(s, 1);
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
	update_pwd(s); 
	bltn_pwd(s);
}