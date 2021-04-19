/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:54:12 by rburton           #+#    #+#             */
/*   Updated: 2021/04/19 22:37:40 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_path(t_set *s, int si, int pi)
{
	int		i;
	char	*path;

	if (s->set[si].ppline[pi].cmnd[1] != NULL)
	{
		path = (char*)malloc((ft_strlen(s->set[si].ppline[pi].cmnd[1]) + 1) * sizeof(char));
		if (NULL == path)
			return (NULL);
		ft_strcpy(path, s->set[si].ppline[pi].cmnd[1]);
	}
	else
	{
		i = 0;
		while (i < s->en)
		{
			if (NULL != ft_strnstr(s->env[i], "HOME=", 5))
			{	
				path = (char*)malloc((ft_strlen(s->env[i]) + 1) * sizeof(char));
				ft_strcpy(path, s->env[i]);
				path = ft_strtrim(path, "HOME=");
			}
			i++;
		}
	}
	return (path);
}

void	cmnd_cd(t_set *s, int si, int pi)
{
	int		err_num;
	int		chdir_err;
	char	*path;

	errno = 0;
	path = set_path(s, si, pi);
	chdir_err = chdir(path);
	if (chdir_err != 0)
	{
		err_num = errno;
		printf("%s", strerror(err_num));
	}
}

void	cmnd_pwd(t_set *s)
{
	int		i;

	i = 0;
	while (i < s->en)
	{
		// printf("s->env[%d]: %s\n", i, s->env[i]);
		if (NULL != ft_strnstr(s->env[i], "PWD=", 4))
			printf("%s\n", ft_strtrim(s->env[i], "PWD="));
		i++;
	}
}

void	cmnd_node(t_set *s)
{
	int		si;
	int		pi;
	int		i;

	si = 0;
	pi = 0;
	i = 0;
	while (si < s->sn)
	{
		while (pi < s->set[si].pn)
		{
			if (0 == ft_strcmp(s->set[si].ppline[pi].cmnd[0], "echo"))
			{
				printf("echo\n");
			}
			else if (0 == ft_strcmp(s->set[si].ppline[pi].cmnd[0], "cd"))
			{
				printf("cd\n");
				cmnd_cd(s, si, pi);
			}
			else if (0 == ft_strcmp(s->set[si].ppline[pi].cmnd[0], "pwd"))
				cmnd_pwd(s);
			else if (0 == ft_strcmp(s->set[si].ppline[pi].cmnd[0], "export"))
			{
				printf("export\n");
			}
			else if (0 == ft_strcmp(s->set[si].ppline[pi].cmnd[0], "unset"))
			{
				printf("unset\n");
			}
			else if (0 == ft_strcmp(s->set[si].ppline[pi].cmnd[0], "env"))
			{
				printf("env\n");
			}
			else if (0 == ft_strcmp(s->set[si].ppline[pi].cmnd[0], "exit"))
			{
				printf("exit\n");
			}
			pi++;
		}
		pi = 0;
		si++;
	}
}