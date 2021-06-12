/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnds_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:56:02 by rburton           #+#    #+#             */
/*   Updated: 2021/06/11 22:21:39 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_new_path(char **path_arr, int two_dots, int lns)
{
	int		i;
	char	*npath;
	char	*leak;

	i = 0;
	npath = ft_strdup("/");
	while (i < (lns - two_dots))
	{
		leak = npath;
		npath = ft_strjoin(npath, path_arr[i]);
		free(leak);
		leak = npath;
		npath = ft_strjoin(npath, "/");
		free(leak);
		i++;
	}
	return (npath);
}

char	*path_to_verify(t_set *s, char *path)
{
	char	**str;
	char	**prsd_str;
	char	**path_arr;
	int		int_arr[2];
	char	*newpath;

	int_arr[0] = two_dots_counter(path);
	str = key_in_arr(s->env, "PWD");
	prsd_str = parse_arg(*str);
	path_arr = ft_split(prsd_str[1], '/');
	int_arr[1] = line_counter(path_arr);
	newpath = make_new_path(path_arr, int_arr[0], int_arr[1]);
	ft_free_str(prsd_str);
	ft_free_str(path_arr);
	return (newpath);
}

int	path_does_exist(t_set *s, char *path)
{
	int			res;
	struct stat	buf;
	char		*npath;

	if (ft_strncmp(path, "..", 2) == 0)
		npath = path_to_verify(s, path);
	else
		npath = path;
	res = stat(npath, &buf);
	if (res == 0)
		return (1);
	else
		return (0);
}

void	process_launcher(t_set *s, int pi, int ci, char **path)
{
	char	*true_path;
	pid_t	pid;
	int		status;

	true_path = path_checker(path);
	if (true_path != NULL)
	{
		pid = fork();
		if (pid == 0)
			execve(true_path, s->st[pi].pln[ci].cmd, s->env);
		else
		{
			wait(&status);
			g_exit = WEXITSTATUS(status);
		}
	}
	else
		err_cmnd_not_fnd(s, pi, ci);
	rdrct_fd_rw(s);
}

void	single_cmd_node(t_set *s, int pi, int ci)
{
	char	**path;

	path = split_path(s);
	if (path == NULL)
	{
		err_no_such_file_or_directory(s, pi, ci);
		return ;
	}
	complete_pth(path, s, pi, ci);
	process_launcher(s, pi, ci, path);
	ft_free_str(path);
}
