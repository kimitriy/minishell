/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:39:34 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/11 21:59:25 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*new;

	new = ft_calloc(1, sizeof(t_list));
	new->data = content;
	new->dup = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_no_mouse(t_list *headphone, t_list *mouse)
{	
	if (!mouse)
	{
		if (headphone)
			headphone->next = NULL;
	}
	else
	{
		if (headphone)
			mouse->prev = headphone;
	}	
}

void	delete_node(t_list **list)
{
	t_list	*mouse;
	t_list	*headphone;
	t_list	*phone;

	phone = *list;
	if (!phone)
		return ;
	headphone = phone->prev;
	mouse = phone->next;
	if (!headphone)
	{
		*list = mouse;
		mouse->prev = NULL;
	}
	else
		headphone->next = mouse;
	ft_no_mouse(headphone, mouse);
	free(phone);
	if (!headphone && !mouse)
		*list = NULL;
}

void	ft_lstadd_back(t_list **list, t_list *new)
{
	t_list	*tmp;

	tmp = *list;
	if (list && *list)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		if (new != NULL)
			new->prev = tmp;
	}
	else if (list)
		*list = new;
}
