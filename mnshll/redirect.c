/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:53:08 by smyriell          #+#    #+#             */
/*   Updated: 2021/05/12 17:40:31 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "minishell.h"


//сигнали стр487

// редирект стр466

/*

char *tmp;

if (str[i] == '>')
{
	i++;
	while (str[i] == ' ')
		i++;
	check if the next is the file
	while (str[i] != ' ' || str[i] != '\0' || str[i] != '|' || str[i] != ';' || str[i] != '>' || str[i] != '<')
		копируем это дело
	
}
*/
	
puts(strerror(errno));// преобразует код ошибки в сообщение

int		main(int argc, char *argv[])
{
	// char *str;

	// str = ;
	printf("my user is = %s\n", getenv("USER"));
	return 0;
}