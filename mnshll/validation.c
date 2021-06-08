/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 22:05:40 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/08 15:21:47 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_checker(char *str, int i)
{
	int	len;
	int	q;
	int	a;

	q = 0;
	a = 0;
	len = ft_strlen(str) - 1;
	while (str[i])
	{	
		ft_check_quotes_lex(str, i, &q, &a);
		if (ft_syntax_validation(str, i, q, a))
		{
			g_exit = 258;
			return (1);
		}
		i++;
	}
	if (i == len && (q != 0 || a != 0))
	{
		g_exit = 258;
		write(2, "not valid input, check `\'` or `\"`\n", 34);
		return (1);
	}
	return (0);
}

void	ft_valid_input(t_ter *hist, t_set *s)
{
	int		i;
	char	*str;
	t_pars	pars;

	i = 0;
	str = ft_strdup(hist->current_hist_command->data);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == ';' || str[i] == '|')
	{
		g_exit = 258;
		write(2, "syntax error near unexpected token `;` or `|`\n", 46);
		return ;
	}
	if (ft_syntax_checker(str, i))
		return ;
	ft_parsing(str, s);// все от сюда и до конца вытащила из ft_valid_input(t_ter *hist, t_set *s)
	free(str);
	ft_change_the_symb(s->dol.full_arg, &pars);
	free(s->dol.full_arg);// это потом можно засунуть внутрь ft_change_the_symb после pars->changed = ft_strdup(str);
	mini_prsr(s, &pars.changed);
	print_set(s);
	ft_return_the_symb(s, &pars);
	mnshll_execute(s);

	// МАША!Подумай когда и где нужно занулять твои структуры перед новым вводом!

	
	// ft_parsing(str, s);
	// ft_parse_init(&pars);
	// ft_change_the_symb(str, &pars);
	// free(str);
	// mini_prsr(s, &pars.changed);
	// print_set(s);
	// ft_return_the_symb(s, &pars);
	// mnshll_execute(s);
	// return (0);
}