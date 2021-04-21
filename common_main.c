/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:30:28 by smyriell          #+#    #+#             */
/*   Updated: 2021/04/21 17:46:26 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void ft_dollar(char *str, int i, int a)
// {
// 	int i;
// 	int a;
// 	int j; // counter for len of env var
// 	char *p;

// 	a = 0;
// 	i = 0;
// 	j = 0;

// 	while (str[i] == ' ')
// 		i++;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' && a == 0)
// 			a = 1;
// 		else if (str[i] == '\'' && a == 1)
// 			a = 0;
// 		else if (str[i] == '$' && a == 0)
// 		{
// 			i++;
// 			while (str[i] != ' ' && str[i])
// 			{
// 				j++;// len of env var
// 				i++;
// 			}
// 			i = i - j;
// 			p = ft_strndup(str + i, j)
// 			if (!p)
// 				write(1, "malloc problems", 16); // дальше записываем эту env var по р* и ищем ее в env
			
// 		}
// 		i++;
// 	}
// 	return (p);// дальше записываем эту env var по р* и ищем ее в env
// 	// вернула указатель на env var, дальше ищем совпадение с в env и если находим, то перезаписываем аргумент! с учетом символов до и после пробелов
// 	//этот указатель фришим!!!!! если не находим пишем только начало, находим то дозаписываем конец еще
// }

void ft_pre_splitting(char c, int q, int a) // подменяем для сплита
{
	if (c == ';' && (q == 1 || a == 1))
		c = 5; // подмена точки с зап
	else if (c == ' ' && (q == 1 || a == 1))
		c = 8; // подмена пробела
}

void ft_aft_splitting(char c, int q, int a) // обратная подмена после сплита
{
	if (c == 5 && (q == 1 || a == 1))
		c = ';'; // подмена на точк с зап
	else if (c == 8 && (q == 1 || a == 1))
		c = ' '; // подмена на пробел
}

void arg_validation(char *str, int i)
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
		if (q != 1 && a != 1)
		{
			if (str[i] == ';' || str[i] == '|')
			{
				j = i + 1;
				while (str[j] == ' ')
					j++;
				if (str[j] == '|' || str[j] == ';' )
					write(2, "//parse error near `;|' or parse error near `|'", 48); //correct
				// comand_validation(str, j);// посмотреть список команд шелла, завалидить возможные символы
			}
		}
		else if (str[i] == '\\' && str[i + 1] == '\0')
			write(2, "multiple line", 14);
		else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			write(2, "syntax error near unexpected token `>'", 39);
		else if (str[i] == '<' && str[i + 1] == '<')
			write(2, "bonus part", 39);
	
		// condition for opened/closed quotes/apostr | ТАК ВРОДЕ ВСЕ РАБОТАЕТ НА ВАЛИДАЦИЮ КАВЫЧЕК ВО ВСЕЙ СТРОКЕ
		
		if (str[i] == '\"' && str[i - 1] != '\\' && q == 0 && a == 0)
			q = 1; // 1 - кавычка открылась
		else if (str[i] == '\"' && str[i - 1] != '\\' && q == 1)
			q = 0;// 0 - кавычка закрылась
		else if (str[i] == '\'' && a == 0 && q == 0)
			a = 1;
		else if (str[i] == '\'' && a == 1) 
			a = 0;
		if (i == len && (q != 0 || a != 0))
			write(2, "//незакрытая кавычка/апостроф\n", 56);
		ft_pre_splitting(str[i], q, a);
		i++;
	}
}

void lexer(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == ';' || str[i] == '|') // проверить поведение редиректов
		write(2, ";// невалидный символ начала syntax error near unexpected token `;`\n", 91); //correct
	arg_validation(str, i);
	i++;

}

int main(int argc, char **argv, char **envp, char **apple) // make a copy of envp!
{
	char *line;

	write(1, "waiting for a new command\n", 27);
	while (get_next_line(0, &line))
	{
		lexer(line);
		write(1, "waiting for a new command\n", 27);	
	}	
	write(1, "waiting for a new command\n", 27);
	return 0;
}
