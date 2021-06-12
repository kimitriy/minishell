/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnds_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:56:02 by rburton           #+#    #+#             */
/*   Updated: 2021/06/11 22:21:00 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	complete_pth(char **pth, t_set *s, int pi, int ci)
{
	int		i;
	char	*tmp;

	i = 0;
	while (NULL != pth[i])
	{
		tmp = pth[i];
		pth[i] = ft_strjoin(pth[i], "/");
		free(tmp);
		i++;
	}
	i = 0;
	while (NULL != pth[i])
	{
		tmp = pth[i];
		pth[i] = ft_strjoin(pth[i], s->st[pi].pln[ci].cmd[0]);
		free(tmp);
		i++;
	}
}

char	**split_path(t_set *s)
{
	int		i;
	char	*str;
	char	**pth;

	i = 0;
	while (i < s->en)
	{
		if (NULL != ft_strnstr(s->env[i], "PATH=", 5))
		{
			str = ft_strtrim(s->env[i], "PATH=");
			pth = ft_split(str, ':');
			free(str);
		}
		i++;
	}
	return (pth);
}

char	*path_checker(char **pth)
{
	int			i;
	int			res;
	struct stat	buf;

	i = 0;
	while (NULL != pth[i])
	{
		res = stat(pth[i], &buf);
		if (res == 0 && (buf.st_mode & X_OK))
			return (pth[i]);
		i++;
	}
	return (NULL);
}

int	two_dots_counter(char *str)
{
	int		i;
	int		dots;

	i = 0;
	dots = 0;
	while (str[i])
	{
		if (str[i] == '.')
			dots++;
		i++;
	}
	return (dots / 2);
}

int	line_counter(char **arr)
{
	int		i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
