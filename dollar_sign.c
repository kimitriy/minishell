/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:43:54 by smyriell          #+#    #+#             */
/*   Updated: 2021/05/03 22:21:36 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int ft_strlen(char *str)
{
	int i;

	i = -1;
	while (str[++i]);
	return (i);	
}

char	*ft_strdup(char *s1)
{
	char	*p_s1;
	int		i;

	p_s1 = (char*)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (NULL == p_s1)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		p_s1[i] = s1[i];
		i++;
	}
	p_s1[i] = '\0';
	return (p_s1);
}

char	*ft_strjoin_dol(char *s1, char *s2)
{
	char	*sjn;
	int		i;
	int		lens1;
	int		lens2;

	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!(sjn = (char*)malloc((lens1 + lens2 + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < lens1)
	{
		sjn[i] = s1[i];
		i++;
	}
	while (i < (lens1 + lens2))
	{
		sjn[i] = s2[i - lens1];
		i++;
	}
	sjn[i] = '\0';
	return (sjn);
}

char	*ft_strndup(char *s1, int n)
{
	char	*p_s1;
	size_t	i;

	p_s1 = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (NULL == p_s1)
		return (NULL);
	if (n > (ft_strlen(s1)))
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		p_s1[i] = s1[i];
		i++;
	}
	p_s1[i] = '\0';
	return (p_s1);
}

char  *ft_dollar(char *str)
{
	int i;
	int a;
	int j; // counter for len of env var
	char *p;

	a = 0;
	i = 0;
	j = 0;

	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == '\'' && a == 0)
			a = 1;
		else if (str[i] == '\'' && a == 1)
			a = 0;
		else if (str[i] == '$' && a == 0)
		{
			i++;
			while (str[i] != ' ' && str[i])
			{
				j++;// len of env var
				i++;
			}
			i = i - j;
			p = ft_strndup(str + i, j);
			if (!p)
				write(1, "malloc problems", 16); // дальше записываем эту env var по р* и ищем ее в env
			
		}
		i++;
	}
	return (p); // вернула указатель на env var, дальше ищем совпадение с в env и если находим, то перезаписываем аргумент! с учетом символов до и после пробелов
	//этот указатель фришим!!!!! если не находим пишем только начало, находим то дозаписываем конец еще
	
}

char *find_the_line(char **env, char *p_to_env)
{
	int		n;
	int		i;

	n =	ft_strlen(p_to_env);
	i = 0;
	while (env[i] && strncmp(env[i], p_to_env, n))
		i++;
	return (env[i]);
}

char *dollar_to_path(char **env, char *p_to_env_var)
{
	// int		n;
	int		i;
	int		j;
	char	*p_to_env_str;
	char	*path;

	//env + i // это искомая переменная в env с ее путем, дальше нужно скопировать только путь
	p_to_env_str = find_the_line(env, p_to_env_var);
	if (!p_to_env_str)
		return (NULL);
	j = 0;
	while (p_to_env_str[++j] && p_to_env_str[j] != '=')
			;
	j++;
	path = p_to_env_str + j;
	free(p_to_env_var); // надо???
	return(path);
}

char  *glue_path_to_arg(char *arg, char *path)
{
	char *full_arg;
	char *before_dol;
	char *aft_dol;
	int i;
	char *tmp;

	i = -1;
	while (arg[++i] != '$');
	before_dol = ft_strndup(arg, i);
	printf("before_dol = %s\n", before_dol);
	while (arg[i] != ' ')
		i++;
	aft_dol	= ft_strdup(arg + i);
	printf("aft_dol = %s\n", aft_dol);
	tmp = ft_strjoin_dol(before_dol, path);
	printf("tmp = %s\n", tmp);
	full_arg = ft_strjoin_dol(tmp, aft_dol);
	free(before_dol);
	free(tmp);
	free(aft_dol);
	printf("full_arg = %s\n", full_arg);
	return (full_arg);
}

int main()
{
	char *p;
	char *arg;
	char *path;
	char *end;
	// char **env;

	char *env[3] = {"abccd", "TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n003vj3w00yw8z/T/", NULL};
	
	arg = "         hhgf$TMPDIR kh";

	p = ft_dollar(arg);
	path = dollar_to_path(env, p);
		// printf("%s\n", p);
		end = glue_path_to_arg(arg, path);
	while (1)
	;
	
	return (0);
}