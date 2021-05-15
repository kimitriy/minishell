/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_my.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 17:48:17 by rburton           #+#    #+#             */
/*   Updated: 2021/05/14 23:49:23 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	null_tcmnd(t_cmnd *cmd, int n)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < n)
	{
		while (cmd->cmd[i][j])
		{
			cmd->cmd[i][j] = '\0';
			j++;
		}
		i++;
		j = 0;
	}
	cmd->cmd[i] = NULL;
}

void	make_env(t_set *s, char **envp)
{
	int		i; //index of lines in envp
	int		l;

	// print2darr(envp, 0);

	s->en = 0;
	while (envp[s->en] != NULL)
		s->en++;
	s->env = ft_calloc(s->en + 1, sizeof(char*));
	// if (!(s->env = (char**)malloc((n + 1) * sizeof(char*))))
	// 	err_message("env malloc error");
	s->env[s->en] = NULL;
	i = -1;
	while (++i < s->en)
	{
		l = ft_strlen(envp[i]);
		s->env[i] = ft_calloc(l + 1, sizeof(char));
		// if (!(s->env[i] = (char*)malloc((l + 1) * sizeof(char))))
		// 	err_message("env malloc error");
		ft_strcpy(s->env[i], envp[i]);
		// printf("s->env[%d]: %s\n", i, s->env[i]);
	}
	make_exp(s, 0);
}

void	make_exp(t_set *s, int n)
{
	char	**prsd_arg;
	char	*str;
	char	*tmp;
	int		len;
	int		i;
	int		j;

	// print2darr(s->env, 0); input is OK
	if (n != 0) //n - is a flag. if it is not 0 then s->exp needs to be freed
	{	
		ft_free(s->exp);
		s->exp = NULL;
		if (s->exp == NULL)
			write(1, "s->exp is freed\n", 16); //s->exp is freed
	}
	s->exn = s->en;
	s->exp = calloc(s->exn + 1, sizeof(char*));
	i = -1;
	while (++i < s->exn)
	{
		// printf("s->env[%d]: %s\n", i, s->env[i]); OK outputs new str
		prsd_arg = parse_arg(s->env[i]); //parses each str of the env
		// print2darr(prsd_arg, 0); OK outputs new key and value
		s->exp[i] = ft_strdup(prsd_arg[0]); //gives memory and key to each str of exp
		
		len = ft_strlen(prsd_arg[1]); //calcs length of value str
		str = ft_calloc(len + 4, sizeof(char)); //gives memory to the str
		str[0] = 61; //writes '=' to the zero element of str
		str[1] = 34; //writes the first '"' to the 1st element of the str
		j = -1;
		while (++j < len) //writes the rest of value to the str in cycle 
			str[j + 2] = prsd_arg[1][j];
		str[j + 2] = 34; //writes the second '"' to the before last element of the str
		str[j + 3] = '\0'; //null terminates the end of the str
		tmp = s->exp[i]; //saves access to the allocated memory through tmp pointer
		s->exp[i] = ft_strjoin(s->exp[i], str); //joins key in the exp arr and prepared str
		
		// printf("s->exp[%d]: %s\n", i, s->exp[i]); OK
		// write(1, "s->exp[i]: ", 11);
		// write(1, s->exp[i], ft_strlen(s->exp[i]));
		// write(1, "\n", 1);
		
		free(tmp); //frees tmp
		free(str); //frees str
	}
	// s->exp[i] = NULL;
	arr2d_sorted(s->exp, s->exn);
}

// void	save_argv(t_set *s, char *argv0)
// {
// 	int		len;

// 	len = ft_strlen(argv0);
// 	s->argv0 = (char*)malloc((len + 1) * sizeof(char));
// 	if (NULL == s->argv0)
// 		err_message("argv malloc error");
// 	ft_strcpy(s->argv0, argv0);
// }