/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:42:37 by rburton           #+#    #+#             */
/*   Updated: 2021/06/12 00:38:29 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_space_syntax(char *str, int i, int *j)
{
	*j = i + 1;
	while (str[*j] == ' ')
		*j += 1;
}

int	ft_double_check_redir(char *str, int i, int *j)
{
	check_space_syntax(str, i, j);
	if (str[i] == '>')
	{
		if (str[*j] == '<')
		{
			write(2, "syntax error near unexpected token `<'\n", 39);
			return (1);
		}
	}
	else
	{
		if (str[*j] == '>')
		{
			write(2, "syntax error near unexpected token `>'\n", 39);
			return (1);
		}
	}
	return (0);
}

int	redir_syntax_checking(char *str, int i, int q, int a)
{
	int	j;

	if (str[i] == '>' && str[i + 1] == '>' && q != 1 && a != 1)
	{
		check_space_syntax(str, i + 1, &j);
		if (str[j] == '>')
			return (1);
	}
	else if (str[i] == '<' && str[i + 1] == '<' && q != 1 && a != 1)
	{
		write(2, "bonus part case\n", 16);
		return (1);
	}
	else if (q != 1 && a != 1 && (str[i] == '>' || str[i] == '<'))
	{
		if (ft_double_check_redir(str, i, &j))
			return (1);
	}
	else if ((str[i] == '<' || str[i] == '>') && q != 1 && a != 1)
	{
		check_space_syntax(str, i, &j);
		if (str[j] == '|' || str[j] == '\0' || str[j] == ';')
			return (1);
	}
	return (0);
}

int	ft_syntax_validation(char *str, int i, int q, int a)
{
	int	j;

	if ((str[i] == ';' || str[i] == '|') && q != 1 && a != 1)
	{
		check_space_syntax(str, i, &j);
		if (str[j] == '|' || str[j] == ';' )
		{
			write(2, "syntax error near unexpected token `;` or `|`\n", 46);
			return (1);
		}
	}
	else if (str[i] == '\\' && (str[i + 1] == '\0' || str[i + 1] == '\n'))
	{
		write(2, "multiple line is not valid case in this shell\n", 46);
		return (1);
	}
	else if (str[i] == '>' || str[i] == '<')
	{
		if (redir_syntax_checking(str, i, q, a))
		{
			write(2, "syntax error near unexpected token `>' or `<'\n", 46);
			return (1);
		}
	}
	return (0);
}

void	ft_check_quotes_lex(char *str, int i, int *q, int *a)
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
