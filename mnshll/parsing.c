/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 19:50:55 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/08 19:56:02 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_dol(t_set *s, char *str)
{
	int		j;
	char	*tmp;
	int		len;

	if (str[s->dol.i + 1] == '?')
	{
		ft_err_nmb(s, str, tmp);
		return ;
	}
	if (str[s->dol.i - 1] != '\\')
		s->dol.i++;
	else
		ft_slash_in_dol(s, tmp);
	j = 0;
	if (!ft_check_symb_aft_dol(&s->dol, str, &j))
	{
		if (str[s->dol.i + 1] == ' ')
		{
			while (str[++s->dol.i] == ' ')
				;
			s->dol.i--;
		}
		return ;
	}
	if (ft_check_env(s, j)) //  return 1 - если не находит в перем окружении
		ft_not_found_in_env(s, &len);
}

int	ft_parsing_2(t_dol *dol, t_set *s, char *str)
{
	if (str[dol->i] == ' ')
		ft_parse_space(dol, str);
	else if (str[dol->i] == '$')
		ft_parse_dol(s, str);
	else if (str[dol->i] == '|' && dol->redir_pipe = 1)// ??????
	{
		s->dol.full_arg = ft_strjoin_symb(s->dol.full_arg, ';');
		dol->redir_pipe = 0;
	}
	else if ((str[dol->i] == '>' || str[dol->i] == '<') && dol->q == 0)
	{
		if (ft_parse_redir(dol, str))
			return (1);
	}
	else
		ft_add_symb(dol, str);
	return (0);
}

int		ft_parsing(char *input, t_set *s)
{
	char *str;

	ft_dol_struct_init(&s->dol);
	str = ft_strdup(input);
	while (str[s->dol.i])
	{
		if (str[s->dol.i] == '\\' )
			ft_parse_slash(&s->dol, str);
		else if (str[s->dol.i] == '\'')
			ft_parse_a(&s->dol, str);
		else if (str[s->dol.i] == '\"')
			ft_parse_q(&s->dol, s, str);
		else 
		{
			if (ft_parsing_2(&s->dol, s, str))
				return (1);
		}
		if (str[s->dol.i])
			s->dol.i++;
	}
	g_exit = 0;
	free(str);
	return (0);
}

// int		main()
// {
// 	t_set s;
// 	char *a;
// 	a = "< aaa cat \'str1\' | str2\"str3 dk str4\" < bbb";
// 	ft_dol(a, &s);
// 	return 0;
// }