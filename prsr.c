/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariakalashnikova <mariakalashnikova@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:42:37 by rburton           #+#    #+#             */
/*   Updated: 2021/05/27 14:39:55 by mariakalash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void ft_pre_splitting(char c, int q, int a) // подменяем для сплита
// {
// 	if (c == ';' && (q == 1 || a == 1))
// 		c = -1; // подмена точки с зап
// 	else if (c == ' ' && (q == 1 || a == 1))
// 		c = -2; // подмена пробела
// }

// void ft_aft_splitting(char c, int q, int a) // обратная подмена после сплита
// {
// 	if (c == -1 && (q == 1 || a == 1))
// 		c = ';'; // подмена на точк с зап
// 	else if (c == -2 && (q == 1 || a == 1))
// 		c = ' '; // подмена на пробел
// }


// check_space_syntax(str, i, &j);


void	check_space_syntax(char *str, int i, int *j)
{
	j = i + 1;
	while (str[j] == ' ')
		j++;
}


void	redir_syntax_checking(char *str, int i, int *j, int q, int a)
{
	if (str[i] == '>' && str[i + 1] == '>' && q != 1 && a != 1)
	{
		check_space_syntax(str, i + 1, &j);
		if (str[j] == '>')
			write(2, "syntax error near unexpected token `>'", 39);
	} // проверить поведение в кавычках
	else if (str[i] == '<' && str[i + 1] == '<' && q != 1 && a != 1) // проверить поведение в кавычках
		write(2, "bonus part", 39);
	else if (str[i] == '>' && q != 1 && a != 1)
	{
		check_space_syntax(str, i, &j);
		if (str[j] == '<')
			write(2, "//parse error near `<'", 23); //correct
		// com}and_validation(str, j);// посмотреть список команд шелла, завалидить возможные символы
	}
	else if (str[i] == '<' && q != 1 && a != 1)
	{
		check_space_syntax(str, i, &j);
		if (str[j] == '>')
			write(2, "//parse error near `>'", 23); //correct
		// com}and_validation(str, j);// посмотреть список команд шелла, завалидить возможные символы
	}
	else if ((str[i] == '<' || str[i] == '>') && q != 1 && a != 1)
	{
		check_space_syntax(str, i, &j);
		if (str[j] == '|' || str[j] == '\0' || str[j] == ';')
			write(2, "syntax error near unexpected token", 35); //correct
	}
	else
		return ;
}
void	ft_syntax_validation(char *str, int i, int q, int a)
{
	int	j;

	if ((str[i] == ';' || str[i] == '|') && q != 1 && a != 1)
	{
		check_space_syntax(str, i, &j);
		if (str[j] == '|' || str[j] == ';' )
			write(2, "//parse error near `;|' or parse error near `|'", 48); //correct
		// com}and_validation(str, j);// посмотреть список команд шелла, завалидить возможные символы
	}
	else if (str[i] == '\\' && (str[i + 1] == '\0' || str[i + 1] == '\n'))
		write(2, "multiple line", 14);
	else
		redir_syntax_checking(str, i, &j, q, a);
}

void validation(char *str, int i)
{
	int len;
	int q; // quot
	int a; // apos

	len = ft_strlen(str) - 1;
	q = 0;
	a = 0;
	while (str[i])
	{	
		//--------------- ОБНОВИТЬ ДИМЕ ЭТОТ КУСОК-------------------//
		if (str[i] == '\"' && str[i - 1] != '\\' && q == 0 && a == 0)
			q = 1; // 1 - кавычка открылась	
		else if (str[i] == '\"' && str[i - 1] != '\\' && q == 1)
			q = 0;// 0 - кавычка закрылась
		else if (str[i] == '\'' && str[i - 1] != '\\' && a == 0 && q == 0)
			a = 1;
		else if (str[i] == '\'' && str[i - 1] != '\\' && a == 1) 
			a = 0;
		else if (i == len && (q != 0 || a != 0))  
			write(2, "//незакрытая кавычка/апостроф\n", 56);
		else if (str[i] == '\\' && (str[i + 1] == '\0')) // || (str[i + 1] == '\"')))
			write (2, "\\ at the end of argument not valid");
		else
			ft_syntax_validation(str, i, q, a);
		i++;
	}
	return (0);
}

void lexer(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == ';' || str[i] == '|') // проверить поведение редиректов
		write(2, ";// невалидный символ начала syntax error near unexpected token `;`\n", 91); //correct
	if (ft_syntax_checker(str, i))
		write(2, "невалидный ввод", 30);// нужно попросить заново ввести строку + включить историю и настройку терминала
}
