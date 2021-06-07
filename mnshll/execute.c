/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:19:44 by rburton           #+#    #+#             */
/*   Updated: 2021/06/07 21:28:40 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bltn_check(t_set *s, int pi, int ci)
{
	// char	*bltins[8] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	char	**bltns;

	bltns = (char **)ft_calloc(8, sizeof(char *));
	bltns[0] = ft_strdup("echo");
	bltns[1] = ft_strdup("cd");
	bltns[2] = ft_strdup("pwd");
	bltns[3] = ft_strdup("export");
	bltns[4] = ft_strdup("unset");
	bltns[5] = ft_strdup("env");
	bltns[6] = ft_strdup("exit");
	bltns[7] = NULL;
	if (NULL != str_in_arr(bltns, s->st[pi].pln[ci].cmd[0]))
	{
		ft_free_str(bltns);
		return (1);
	}
	else
	{
		ft_free_str(bltns);
		return (0);
	}
}

void	launch_mnshll(t_set *s, int pi, int ci)
{
	char	**str;
	char	**path;
	char	*tmp_leak;

	str = key_in_arr(s->env, "PWD");
	path = parse_arg(*str);
	tmp_leak = path[1];
	path[1] = ft_strjoin(path[1], "/minishell");
	free(tmp_leak);
	process_launcher(s, pi, ci, path);
	ft_free_str(path);
}

void	launch_executable(t_set *s, int pi, int ci)
{
	char	**str;
	char	**path;
	char	*tmp_strtrim;
	char	*tmp_leak;

	str = key_in_arr(s->env, "PWD");
	path = parse_arg(*str);
	tmp_strtrim = ft_strtrim(s->st[pi].pln[ci].cmd[0], ".");
	tmp_leak = path[1];
	path[1] = ft_strjoin(path[1], tmp_strtrim);
	free(tmp_leak);
	free(tmp_strtrim);
	process_launcher(s, pi, ci, path);
	ft_free_str(path);
}

void	selector(t_set *s, int pi, int ci)
{
	if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "minishell"))
		launch_mnshll(s, pi, ci);
	else if (s->st[pi].pln[ci].cmd[0][0] == '.')
		launch_executable(s, pi, ci);
	else
		single_cmd_node(s, pi, ci);
}

void	mnshll_execute(t_set *s)
{
	int		pi; //pipeline indx
	int		ci; //command indx

	pi = -1;
	while (++pi < s->pn)
	{
		if (s->st[pi].cn > 1)
			pipes_node(s, pi);
		else
		{
			ci = -1;
			while (++ci < s->st[pi].cn)
			{
				if (bltn_check(s, pi, ci) == 1)
					bltn_node(s, pi, ci);
				else
					selector(s, pi, ci);
			}
		}
	}
}
