/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprsr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:42:37 by rburton           #+#    #+#             */
/*   Updated: 2021/06/04 17:36:11 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//**************
//
// V ETOM FILE VRODE NICHEGO NUZHNOGO
//
//***************



void	ft_quotes(char *str, int i, int *q, int *a)
{
	if (str[i] == '\"' && str[i - 1] != '\\' && *q == 0 && *a == 0)
		*q = 1;
	else if (str[i] == '\"' && str[i - 1] != '\\' && *q == 1)
		*q = 0;
	else if (str[i] == '\'' && str[i - 1] != '\\' && *a == 0 && *q == 0)
		*a = 1;
	else if (str[i] == '\'' && str[i - 1] != '\\' && *a == 1)
		*a = 0;
}

void	validation(char *str, int i)
{
	int	len;
	int	q;
	int	a;
	int	j;

	len = ft_strlen(str) - 1;
	q = 0;
	a = 0;
	while (str[i])
	{
		ft_check_lex(char *str, int i, int *)
		if ((str[i] == ';' || str[i] == '|') && q != 1 && a != 1)
		{
			j = i + 1;
			while (str[j] == ' ')
				j++;
			if (str[j] == '|' || str[j] == ';' )
				write(2, "//parse error near `;|' or parse error near `|'", 48);
		}
		else if (str[i] == '\\' && (str[i + 1] == '\0' || str[i + 1] == '\n'))
			write(2, "multiple line", 14);
		else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>' \
														&& (q == 0 || a == 0))
			write(2, "syntax error near unexpected token `>'", 39);
		else if (str[i] == '<' && str[i + 1] == '<' && (q == 0 || a == 0))
			write(2, "bonus part", 39);
		ft_quotes(str, i, &q, &a);
		if (i == len && (q != 0 || a != 0))
			write(2, "//незакрытая кавычка/апостроф\n", 56);
		i++;
	}
}

void	ft_parse_init(t_pars *pars)
{
	pars->symb1 = ' ';
	pars->symb2 = -1;
	pars->symb3 = '|';
	pars->symb4 = -2;
}

void	lexer(char *str)
{
	int		i;
	t_pars	pars;
	t_set	s;

	i = 0;
	s = (t_set *)ft_calloc(1, sizeof(t_set));
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == ';' || str[i] == '|')
		write(2, ";// невалидный символ начала syntax error near unexpected token `;`\n", 91); //correct
	validation(str, i);
	ft_parse_init(&pars);
	ft_change_the_symb(str, pars);
	splitting;
	ft_return_the_symb(s, pars);//  здесь нужно отправлять на прием массив после сплита
}
