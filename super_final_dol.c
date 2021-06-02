/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_final_dol.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariakalashnikova <mariakalashnikova@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 23:31:50 by smyriell          #+#    #+#             */
/*   Updated: 2021/05/27 14:39:52 by mariakalash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122)))
		return (0);
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_strlen(const char *str)
{
	int	i;

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

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

int	ft_char_num(const char *str, int c)
{
	int	i;
	int	j;

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

char	*ft_strchr(const char *s, int c)
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

void ft_add_symb(t_dol *dol, char *str)
{
	char	*tmp;

	tmp = ft_strdup(dol->full_arg);
	if (dol->full_arg[0] != '\0')
		free (dol->full_arg);
	dol->full_arg = ft_strjoin_symb(dol->full_arg, str[dol->i]);
	if (!dol->full_arg)
	{
		dol->error = 1;
		write(2, "error dol->full_arg = ft_strjoin", 33);// error go to new input
	}
}

int ft_check_env(t_dol *dol, int j)
{
	int	i;
	char	*env[3] = {"abccd", "USER=smyriell", NULL};
	char	*tmp;

	i = 0;
	printf("CHECKING ENV\n");
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

void	ft_parse_slash(t_dol *dol, char *str)//вроде готова
{	
	printf("IN PARSE SLASH\n");
	if (dol->q == 0)
	{
		dol->i += 1;
		ft_add_symb(dol, str);
	}
	else
	{
		if (ft_strchr(dol->cont_symb, str[dol->i + 1])) // || str[dol->i + 1] == ' ')
		{
			dol->i += 1;
			ft_add_symb(dol, str);
		}
	}
	printf("ft_parse_slash: dol.full_arg = %s\n", dol->full_arg);
}

int	ft_check_symb_aft_dol(t_dol *dol, char *str, int *j)
{	
	char	*tmp;

	dol->env_var = ft_strdup("");
	while (str[dol->i] && (ft_isalnum(str[dol->i]) || str[dol->i] == '_'))
	{
		if ((ft_isdigit(str[dol->i])) && *j == 0)
		{
			printf("Check  digit aft $, str[dol->i] = %c, flag = %d\n", str[dol->i], dol->digit_aft_dol);
			dol->digit_aft_dol = 1;
			return (0);
		}
		tmp = ft_strdup(dol->env_var);
		if (dol->env_var[0] != '\0')
			free(dol->env_var);
		dol->env_var = ft_strjoin_symb(tmp, str[dol->i]);
		free(tmp);
		dol->i++;
		*j += 1;
	}
	dol->i--;
	return (1);
}

void	ft_parse_space(t_dol *dol, char *str)
{
	char *tmp;

	if (dol->q == 1) // || str[dol->i + 1] != ' ')
	{
		ft_add_symb(dol, str);
	}
	else
	{
		if (str[dol->i + 1] == ' ')
		{
			while (str[dol->i] == ' ')
				dol->i++;
			dol->i -= 1;
		}
		else if (str[dol->i + 1] == '>' && str[dol->i + 2] == '>')
			dol->i++;
		else if (str[dol->i + 1] == '>' || str[dol->i + 1] == '<')
			return ;
		else if (str[dol->i + 1] != '\0')
			ft_add_symb(dol, str);
	}
}

void	ft_parse_q_slash(t_dol *dol, char *str)
{
	char	*tmp;

	if (str[dol->i + 1] == '$' || str[dol->i + 1] == '\"')
	{
		dol->i += 1;
		ft_add_symb(dol, str);
	}
	else if (str[dol->i + 1] == '\\')
	{
		dol->i++;
		tmp = ft_strdup(dol->full_arg);
		free(dol->full_arg);
		dol->full_arg = ft_strjoin_symb(tmp, str[dol->i]);
		free(tmp);
	}
	else
	{
		tmp = ft_strdup(dol->full_arg);
		free(dol->full_arg);
		dol->full_arg = ft_strjoin_symb(tmp, str[dol->i]);
		free(tmp);
	}	
	printf("ft_parse_q_slash: dol.full_arg = %s\n", dol->full_arg);
}

void	ft_parse_a(t_dol *dol, char *str)
{
	char *tmp;

	if (dol->q == 0)
	{
		dol->i++;
		printf("IN PARSE A when q == 0\n");
		while (str[dol->i] != '\'' && str[dol->i])
		{
			tmp = ft_strdup(dol->full_arg);
			if (dol->full_arg[0] != '\0')
				free (dol->full_arg);
			dol->full_arg = ft_strjoin_symb(tmp, str[dol->i]);
			if (!dol->full_arg)
			{
				dol->error = 1;
				write(2, "error ft_parse_a dol->full_arg = ft_strjoin", 43);// error go to new input
			}
			dol->i++;
		}
		printf("ft_parse_A: dol->full_arg = %s\n", dol->full_arg);
	}
	else
		return ;
}

void ft_parse_dol(t_dol *dol, char *str)
{
	int j;
	char *tmp;
	int len;

	printf("IN PARSE DOL\n");
	if (str[dol->i + 1] == '?')
		write(1, "here should be status of previous comand\n", 41);//написать функцию
		/*
		
		*/
	if (str[dol->i - 1] != '\\')
		dol->i++;
	else
	{
		tmp = ft_strdup(dol->full_arg);
		free(dol->full_arg);
		dol->full_arg = ft_strjoin_symb(tmp, str[dol->i]);
		free(tmp);
		return ;
	}
	j = 0;
	if (!ft_check_symb_aft_dol(dol, str, &j))
	{
		if (str[dol->i + 1] == ' ')
		{
			while (str[++dol->i] == ' ');
			dol->i--;
		}
		return ;
	}
	printf("ft_parse_dol Before checking env str[dol->i] = %c\n", str[dol->i]);
	if (ft_check_env(dol, j)) //  return 1 - если не находит в перем окружении
	{
		free(dol->env_var);
		printf("ft_parse_dol NO ENV str[dol->i] = %c\n", str[dol->i]);
		len = ft_strlen(dol->full_arg);
		printf("ft_parse_dol NO ENV DOL->FULL_ARG = %s\n", dol->full_arg);
		if (dol->full_arg[len] == ' ' && dol->q == 0)// len - 1 && str[dol->i] == '\0')
		{
			tmp = ft_strndup(dol->full_arg, len - 1);
			free(dol->full_arg);
			dol->full_arg = ft_strdup(tmp);
			free(tmp);
			printf("NOW fullarg = %s\n", dol->full_arg);
			return ;
		}
		else if (str[dol->i + 1] == ' ')
			while (str[dol->i++] == ' ');
	}
	printf("ft_parse_dol NOW DOL->FULL_ARG = %s\n", dol->full_arg);
	printf("ft_parse_dol in the end str[dol->i] = %c\n", str[dol->i]);
}

void	ft_parse_q(t_dol *dol, char *str)
{
	char *tmp;
	int	slash;
	dol->q = 1;
	dol->i++;
	while ((!(str[dol->i - 1] == '\\' && str[dol->i] == '\"')) && str[dol->i] != '\"' && str[dol->i])
	{
		if (str[dol->i] == ' ')
			ft_parse_space(dol, str);
		else if (str[dol->i] == '$')
			ft_parse_dol(dol, str);
		else if (str[dol->i] == '\\')
			ft_parse_q_slash(dol, str);
		else
			ft_add_symb(dol, str);
		printf("ft_parse_q MIDDLE str[i] = %c\n", str[dol->i]);
		dol->i++;
		printf("ft_parse_q MIDDLE str[i++] = %c\n", str[dol->i]);
	}
	dol->q = 0;
	printf("END OF PARSE Q, Q = %d\n", dol->q);
	printf("ft_parse_q: dol->full_arg = %s\n", dol->full_arg);
}

void	check_spaces(t_dol *dol, char *str)
{
	if (str[dol->i] == ' ')
	{
		while (str[dol->i] == ' ')
			dol->i++;
	}
}

void	ft_output_file(t_dol *dol, char *str)
{
	char *tmp;

	tmp = ft_strdup(dol->to_file);
	if (dol->to_file[0] != '\0')
		free (dol->to_file);
	dol->to_file = ft_strjoin_symb(tmp, str[dol->i]);
	if (!dol->to_file)
	{
		dol->error = 1;
		write(2, "error ft_redir_get_file_name", 29);// error go to new input
	}
	free(tmp);
}

void	get_file_name(t_dol *dol, char *str)
{
	char *tmp;

	if (dol->red_app || dol->red_out)
		ft_output_file(dol, str);
	else if (dol->red_in)
	{
		tmp = ft_strdup(dol->from_file);
		if (dol->from_file[0] != '\0')
			free(dol->from_file);
		dol->from_file = ft_strjoin_symb(tmp, str[dol->i]);
		if (!dol->from_file)
		{
			dol->error = 1;
			write(2, "error ft_redir_get_file_name", 29);// error go to new input
		}
		free(tmp);
	}
}

void	ft_redir_get_file_name(t_dol *dol, char *str)
{
	dol->to_file = ft_strdup("");
	dol->from_file = ft_strdup("");
	if (str[dol->i] == '>' && str[dol->i + 1] == '>')
	{
		dol->i++;
		dol->red_app = 1;
	}
	else if (str[dol->i] == '>')
		dol->red_out = 1;
	else if (str[dol->i] == '<')
		dol->red_in = 1;
	dol->i++;
	check_spaces(dol, str);
	while (str[dol->i] != ' ' && str[dol->i] != '\0' && str[dol->i] != '|' && str[dol->i] != ';')
	{
		get_file_name(dol, str);
		dol->i++;
	}
}

void	openning_to_file(t_dol *dol)
{
	if (dol->red_out)
		dol->fd_out = open(dol->to_file, O_CREAT | O_RDWR, 0666);
	else if (dol->red_app)
		dol->fd_out = open(dol->to_file, O_CREAT | O_APPEND | O_RDWR, 0666);	
	if (dol->fd_out == -1)
		write(2, "error openning_to_file", 23);// 
}

void	openning_from_file(t_dol *dol)
{
	if (dol->red_in)
		dol->fd_in = open(dol->from_file, O_RDONLY, 0666);
	if (dol->fd_in == -1)
		write(2, "error open_file\n", 16);// 
}

void	open_file(t_dol *dol)
{
	if (dol->red_out || dol->red_app)
	{
		if (dol->fd_out >= 0)
			close(dol->fd_out);
		openning_to_file(dol);	
	}	
	else if (dol->red_in)
	{
		if (dol->fd_in >= 0)
			close(dol->fd_in);
		openning_from_file(dol); 
	}
	dol->red_app = 0;
	dol->red_out = 0;
	dol->red_in = 0;
}

void	ft_parse_redir(t_dol *dol, char *str)
{
	dol->redir = 1;
	// здесь можно сделать инит для редиректов
	ft_redir_get_file_name(dol, str);
	// dol->i--; вроде не нужно
	open_file(dol);
}

int		ft_dol(char *input)
{
	t_dol dol;
	char *tmp;
	char *str;

	dol.a = 0;
	dol.q = 0;
	dol.i = 0;
	dol.error = 0;
	dol.full_arg = ft_strdup("");
	dol.path = NULL;
	dol.digit_aft_dol = 0;
	dol.red_out = 0;
	dol.red_app = 0;
	dol.red_in = 0;
	dol.fd_out = -2;
	dol.fd_in = -2;
	dol.redir = 0;
	dol.cont_symb = "$\\\'\"";
	// init(&dol);
	str = ft_strdup(input);
	while (str[dol.i])
	{
		printf("BEG str[dol.i] =%c\n", str[dol.i]);
		if (str[dol.i] == '\\' )
			ft_parse_slash(&dol, str);
		else if (str[dol.i] == '\'')
			ft_parse_a(&dol, str);
		else if (str[dol.i] == '\"')
			ft_parse_q(&dol, str);
		else if (str[dol.i] == ' ')
			ft_parse_space(&dol, str);
		else if (str[dol.i] == '$')
			ft_parse_dol(&dol, str);
		// else if (str[dol->i] == ';')
		// 	ft_parse_semicolon(dol, str); //!!! Здесь нужно запустить Димину работу
		else if (str[dol.i] == '|' && dol.redir == 1)
		{
			dol.full_arg = ft_strjoin_symb(dol.full_arg, ';');
			// и запустить в работу Диме
		}
		else if ((str[dol.i] == '>' || str[dol.i] == '<') && dol.q == 0)
			ft_parse_redir(&dol, str);
		else
			ft_add_symb(&dol, str);
		printf("At the end: str[dol.i] =%c\n", str[dol.i]);
		printf("At the end: dol.full_arg =%s\n", dol.full_arg);
		if (str[dol.i])
			dol.i++;
	}
	return (0);
}

int		main()
{
	char *a;
	a = "< aaa cat \'str1\' | str2\"str3 $USER str4\" < bbb";
	ft_dol(a);
	return 0;
}
