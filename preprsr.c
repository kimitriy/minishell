/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprsr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:42:37 by rburton           #+#    #+#             */
/*   Updated: 2021/05/14 14:17:33 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pre_splitting(char c, int q, int a) // подменяем для сплита
{
	if (c == ';' && (q == 1 || a == 1))
		c = -1; // подмена точки с зап
	else if (c == ' ' && (q == 1 || a == 1))
		c = -2; // подмена пробела
}

void ft_aft_splitting(char c, int q, int a) // обратная подмена после сплита
{
	if (c == -1 && (q == 1 || a == 1))
		c = ';'; // подмена на точк с зап
	else if (c == -2 && (q == 1 || a == 1))
		c = ' '; // подмена на пробел
}

void validation(char *str, int i)
{
	int len;
	int q; // quot
	int a; // apos
	int j;

	len = ft_strlen(str) - 1;
	q = 0;
	a = 0;
	while (str[i])
	{
		// if (str[i] == ';' && (str[i + 1] == ';' || str[i + 1] == '|'))
		// 	return (-1);//двойная ; или ; и | !!! 1. для | нужно обработать вариант что, если он разделяет два echo, то выводит только последнее
		if ((str[i] == ';' || str[i] == '|') && q != 1 && a != 1)
		{
			j = i + 1;
			while (str[j] == ' ')
				j++;
			if (str[j] == '|' || str[j] == ';' )
				write(2, "//parse error near `;|' or parse error near `|'", 48); //correct
			// com}and_validation(str, j);// посмотреть список команд шелла, завалидить возможные символы
		}
		else if (str[i] == '\\' && (str[i + 1] == '\0' || str[i + 1] == '\n'))
			write(2, "multiple line", 14);
		else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>' && (q == 0 || a == 0)) // проверить поведение в кавычках
			write(2, "syntax error near unexpected token `>'", 39);
		else if (str[i] == '<' && str[i + 1] == '<' && (q == 0 || a == 0)) // проверить поведение в кавычках
			write(2, "bonus part", 39);
			прямой и обратный редир рядом
			рядом пайп и ;
			после редиректа нельзя пайп ; и /0
			>
		bash: syntax error near unexpected token `newline' 
			< ;
		bash: syntax error near unexpected token `;'
				>> >
		bash: syntax error near unexpected token `>'
			>< or <>
	bash: syntax error near unexpected token `<'
		
		1>2  
		
		// condition for opened/closed quotes/apostr | ТАК ВРОДЕ ВСЕ РАБОТАЕТ НА ВАЛИДАЦИЮ КАВЫЧЕК ВО ВСЕЙ СТРОКЕ
		
		//--------------- ОБНОВИТЬ ДИМЕ ЭТОТ КУСОК-------------------//
		if (str[i] == '\"' && str[i - 1] != '\\' && q == 0 && a == 0)
			q = 1; // 1 - кавычка открылась	
		else if (str[i] == '\"' && str[i - 1] != '\\' && q == 1)
			q = 0;// 0 - кавычка закрылась
		else if (str[i] == '\'' && str[i - 1] && a == 0 && q == 0)
			a = 1;
		else if (str[i] == '\'' && str[i - 1] && a == 1) 
			a = 0;
		else if (i == len && (q != 0 || a != 0))  
			write(2, "//незакрытая кавычка/апостроф\n", 56);
		else if (str[i] == '\\' && (str[i + 1] == '\0')) // || (str[i + 1] == '\"')))
			write (2, "\\ at the end of argument not valid")
		ft_pre_splitting(str[i], q, a);
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
	if (validation(str, i))
		write(2, "невалидный ввод", 30);
}
