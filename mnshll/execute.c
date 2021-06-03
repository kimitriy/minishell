/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:19:44 by rburton           #+#    #+#             */
/*   Updated: 2021/06/03 09:49:26 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		bltn_check(t_set *s, int pi, int ci)
{
	char	*bltins[8] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	if (NULL != str_in_arr(bltins, s->st[pi].pln[ci].cmd[0]))
		return(1);
	else
		return(0);
}

void	launch_mnshll(t_set *s, int pi, int ci)
{
	pid_t   pid;
	int		status;
	char	**str;
	char	**path;
	char	*tmp;
	
	str = key_in_arr(s->env, "PWD");
	path = parse_arg(*str);
	tmp = path[1];
	path[1] = ft_strjoin(path[1], "/minishell");
	free(tmp);
	pid = fork();
	if (pid == 0)
		execve(path[1], s->st[pi].pln[ci].cmd, s->env);
	else
	{
		wait(&status);
		s->err = WEXITSTATUS(status);
	}
	ft_free_str(path);
}

void	launch_executable(t_set *s, int pi, int ci)
{
	pid_t   pid;
	int		status;
	char	**str;
	char	**path;
	char	*tmp_strtrim;
	char	*tmp_leak;

	str = key_in_arr(s->env, "PWD");
	path = parse_arg(*str);
	tmp_strtrim = ft_strtrim(s->st[pi].pln[ci].cmd[0], ".");
	tmp_leak = path[1];
	path[1] = ft_strjoin(path[1], tmp_strtrim);
	free(tmp_strtrim);
	free(tmp_leak);
	pid = fork();
	if (pid == 0)
		execve(path[1], s->st[pi].pln[ci].cmd, s->env);
	else
	{
		wait(&status);
		s->err = WEXITSTATUS(status);
	}
	ft_free_str(path);
}

void	mnshll_execute(t_set *s)
{
	int		pi; //pipeline indx
	int		ci; //command indx
	
	pi = -1;
	while (++pi < s->pn)
		if (s->st[pi].cn > 1)
			pipes_node(s, pi);
		else
		{
			ci = -1;
			while (++ci < s->st[pi].cn)
				if (bltn_check(s, pi, ci) == 1)
					bltn_node(s, pi, ci);
				else
					if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "minishell"))
						launch_mnshll(s, pi, ci);
					else if (s->st[pi].pln[ci].cmd[0][0] == '.')
						launch_executable(s, pi, ci);
					else
						single_cmd_node(s, pi, ci);
		}
}
