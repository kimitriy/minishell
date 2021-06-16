/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 22:05:40 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/16 01:16:42 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_semicolon(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 59 && str[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

int	ft_syntax_checker(char *str, int i)
{
	int	len;
	int	q;
	int	a;

	q = 0;
	a = 0;
	len = ft_strlen(str);
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

void	ft_execute_str(t_set *s, t_pars *pars, char *str)
{
	if (ft_parsing(str, s))
	{
		free(str);
		if (s->dol.from_file)
			free(s->dol.from_file);
		if (s->dol.to_file)
			free(s->dol.to_file);
		return ;
	}
	ft_parse_init(pars);
	pars->changed = ft_strdup(s->dol.full_arg);
	mini_prsr(s, pars->changed);
	ft_return_the_symb(s, pars);
	free(s->dol.full_arg);
	mnshll_execute(s);
	clear_s(s);
	rdrct_fd_rw(s);
}

void	ft_valid_input(t_ter *hist, t_set *s)
{
	int		i;
	char	*str;
	t_pars	pars;
	int		smc;

	i = 0;
	str = ft_strdup(hist->cur_hist_command->prev->data);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == ';' || str[i] == '|')
	{
		g_exit = 258;
		write(2, "syntax error near unexpected token `;` or `|`\n", 46);
		free(str);
		return ;
	}
	if (ft_syntax_checker(str, i))
	{
		free(str);
		return ;
	}
	smc = ft_count_semicolon(str);
	while (smc-- > -1)
		ft_execute_str(s, &pars, str);
	free(str);
}
