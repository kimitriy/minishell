/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   very_final_dol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 23:31:50 by smyriell          #+#    #+#             */
/*   Updated: 2021/05/09 20:16:39 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "minishell.h"

int		ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int		ft_isalpha(int c)
{
	if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122)))
		return (0);
	return (1);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int ft_strlen(const char *str)
{
	int i;

	i = -1;
	while (str[++i]);
	return (i);	
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*sjn;
	int		i;
	int		lens1;
	int		lens2;

	if (s1 == NULL)
		return (s2);
	else if (s2 == NULL)
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

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	printf("I'M IN STRNCMP\n");
	if (!((s1 == 0 && s2 == 0) || n == 0))
	{
		printf("s1 = %s\n", s1);
		printf("s2 = %s\n", s2);
		while (i < n && (s1[i] || s2[i]))
		{
			if ((unsigned char)s1[i] != (unsigned char)s2[i])
				return ((unsigned char)s1[i] - (unsigned char)s2[i]);
			i++;
		}
	}
	return (0);
}

int		ft_char_num(const char *str, int c)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c && str[i - 1] != '\\')
			j++;
		i++;
	}
	return (j);
}

char		*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
	{
		s = &s[i];
		return ((char *)s);
	}
	return (0);
}

char	*ft_strdup(const char *s1)
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

char	*ft_strjoin_symb(char *s1, char symb)
{
	char	*sjn;
	int		i;
	int		lens1;

	i = 0;
	if (s1 == NULL || s1[0] == '\0')
	{
		if (!(sjn = (char*)malloc((2) * sizeof(char))))
			return (NULL);
		sjn[i] = symb;
		sjn[++i] = '\0';
		return (sjn);
	}
	if (!symb)
		return (s1);
	lens1 = ft_strlen(s1);
	if (!(sjn = (char*)malloc((lens1 + 1 + 1) * sizeof(char))))
		return (NULL);
	
	while (i < lens1)
	{
		sjn[i] = s1[i];
		i++;
	}
	sjn[i] = symb;
	sjn[++i] = '\0';
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

int ft_check_env(t_dol *dol, int j)
{
	int i;
	char *env[3] = {"abccd", "PWD=/var/folders/", NULL};
	char *tmp;

	i = 0;
	printf("CHECK ENV\n");
	while (env[i])
	{
		if (!(ft_strncmp(env[i], dol->env_var, j)) && (env[i][j] == '='))
		{
			dol->path = ft_strdup(env[i] + j + 1);
			tmp = ft_strdup(dol->full_arg);
			free(dol->full_arg);
			dol->full_arg = ft_strjoin_dol(tmp, dol->path);
			printf("ft_check_env: dol->full_arg = %s\n", dol->full_arg);
			free(tmp);
			return (0);
		}
		i++;
	}
	return (1);	
}

void ft_parse_dol(t_dol *dol, char *str)
{
	int j;
	char *tmp;
	printf("IN PARSE DOL\n");
	if (str[dol->i + 1] == '?')
		write(1, "here should be status of previous comand\n", 41);//написать функцию
	dol->i++;
	j = 0;
	dol->env_var = ft_strdup("");
	while (str[dol->i] && (ft_isalnum(str[dol->i])))
	{
		if (j == 0 && ft_isdigit(str[dol->i]))
		{
			dol->digit_aft_dol = 1;
			dol->i++;
			return ;
		}
		tmp = ft_strdup(dol->env_var);
		if (dol->env_var[0] != '\0')
			free(dol->env_var);
		dol->env_var = ft_strjoin_symb(tmp, str[dol->i]);
		free(tmp);
		dol->i++;
		j++;
		printf("ft_parse_dol: in while cycle dol->env_var = %s\n", dol->env_var);
	}
	printf("ft_parse_dol: STR[DOL->I] = %c\n", str[dol->i]);
	if (ft_check_env(dol, j)) //  return 1 - если не находит в перем окружении
	{
		if (str[dol->i] == '\\' && dol->q == 0)
			dol->i++;
		if (!dol->digit_aft_dol)// фришит все, если нет цифры
			free(dol->env_var);
		else // есть цифра 
		{
			tmp = ft_strdup(dol->full_arg);
			free(dol->full_arg);
			dol->full_arg = ft_strjoin_dol(tmp, dol->env_var);
			free(tmp);
			free(dol->env_var);
		} 	
		printf("NO VAR IN_ENV\n");
	}
	if (dol->q == 0)
		dol->i -= 1;
	if (dol->q == 1)
		dol->i += 1;
			
	// printf("At the already -1: ft_parse_dol: str[dol->i] = %c\n", str[dol->i]);
}

void	ft_parse_slash(t_dol *dol, char *str)
{
	printf("IN PARSE SLASH\n");
	if (str[dol->i] == '\\')
	{
		if (dol->q == 0)
			dol->i += 1;
		else
		{
			if (ft_strchr(dol->cont_symb, str[dol->i + 1]))
				dol->i += 1;
		}
	}
}

void	ft_parse_space(t_dol *dol, char *str)
{
	char *tmp;
	
	
	tmp = ft_strdup(dol->full_arg);
	printf("ft_space: tmp = %s\n       str[dol.i] = %c\n", tmp, str[dol->i]);
	free(dol->full_arg);
	dol->full_arg = ft_strjoin_symb(tmp, str[dol->i]);
	free(tmp);
	if (str[dol->i + 1] == ' ')
	{
		while (str[dol->i] == ' ')
			dol->i++;
		dol->i -= 1;
	}
	printf("ft_space: dol.full_arg = %s\n", dol->full_arg);
}

void	ft_parse_q(t_dol *dol, char *str)
{
	char *tmp;
	dol->q = 1;
	dol->i++;
	printf("IN PARSE Q, Q = %d\n", dol->q);
	while (str[dol->i] != '\"' && str[dol->i])
	{
		if (str[dol->i] == '\\')
			ft_parse_slash(dol, str);
		// if (str[dol->i] == ' ')
		// 	ft_parse_space(dol, str);
		if (str[dol->i] == '$')
			ft_parse_dol(dol, str);
		tmp = ft_strdup(dol->full_arg);
		printf("ft_parse_q: tmp = %s\n", tmp);
		// if (dol->full_arg[0] != '\0')
			free (dol->full_arg);
		// printf("ft_parse_q: str[dol->i] = %c\n", str[dol->i]);
		dol->full_arg = ft_strjoin_symb(dol->full_arg, str[dol->i]);
		free(tmp);
		printf("ft_parse_q: dol->full_arg = %s\n", dol->full_arg);
		if (!dol->full_arg)
		{
			dol->error = 1;
			write(2, "error ft_parse_a dol->full_arg = ft_strjoin", 43);// error go to new input
		}
		if (!str[dol->i])
			return ;
		dol->i++;
	}
	dol->q = 0;
	printf("END OF PARSE Q, Q = %d\n", dol->q);
	printf("ft_parse_q: dol->full_arg = %s\n", dol->full_arg);
	// dol->i++;
}

void	ft_parse_a(t_dol *dol, char *str)
{
	char *tmp;
	
	printf("QQQQ = %d\n", dol->q);
	if (dol->q == 0)
	{
		dol->i++;
		printf("IN PARSE A when q == 0\n");
		while (str[dol->i] != '\'' && str[dol->i])
		{
			// dol->i++;
			if (dol->full_arg[0] != '\0')
				free (dol->full_arg);
			dol->full_arg = ft_strjoin_symb(dol->full_arg, str[dol->i]);
			printf("DOL->full_arg = %s\n", dol->full_arg);
			if (!dol->full_arg)
			{
				dol->error = 1;
				write(2, "error ft_parse_a dol->full_arg = ft_strjoin", 43);// error go to new input
			}
			dol->i++;
		}
		// dol->i++;
	}
	else
		return ;
}


int		ft_dol(char *str)
{
	t_dol dol;
	char *tmp;

	dol.a = 0;
	dol.q = 0;
	dol.i = 0;
	dol.error = 0;
	dol.full_arg = ft_strdup("");
	dol.path = NULL;
	dol.digit_aft_dol = 0;
	while (str[dol.i])
	{
		if (str[dol.i] == '\\')
			ft_parse_slash(&dol, str);
		else if (str[dol.i] == '\"')
			ft_parse_q(&dol, str);
		else if (str[dol.i] == '$')
			ft_parse_dol(&dol, str);
		else if (str[dol.i] == '\'')
			ft_parse_a(&dol, str);
		else if (str[dol.i] == ' ')
			ft_parse_space(&dol, str);
		else 	
		{
			if (!str[dol.i])
				return (0);
			tmp = ft_strdup(dol.full_arg);
			printf("ft_dol: tmp = %s\n       str[dol.i] = %c\n", tmp, str[dol.i]);
			free(dol.full_arg);
			dol.full_arg = ft_strjoin_symb(tmp, str[dol.i]);
			free(tmp);
			printf("ft_dol: dol.full_arg = %s\n", dol.full_arg);
		}
		dol.i++;
		
		printf("At the end: dol.full_arg = %s\n", dol.full_arg);
	}
	// while (1);
	return (0);
}

int		main()
{
	char *a;
	// a = "hgjhgjgfgf$1USE\\\\R.kkk     l";
	a = "\'str1\'str2\"str3             $PWD str4\" \"str5\"\'$PWD\'           $PWD \"$PWD\"";
	ft_dol(a);
	return 0;
}
