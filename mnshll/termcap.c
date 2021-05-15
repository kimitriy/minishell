/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:36:24 by smyriell          #+#    #+#             */
/*   Updated: 2021/04/29 20:41:19 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <term.h>
#include <curses.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*arr;

	arr = (void *)malloc(count * size);
	if (NULL == arr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}

void termcap_init(t_ter hist)
{
	if (hist.f == 0)
	{
		tcgetattr(0, &hist.term);
		hist.term.c_lflag &= ~(ECHO);
		hist.term.c_lflag &= ~(ICANON);
		hist.term.c_lflag &= ~(ISIG);
		tcsetattr(0, TCSANOW, &hist.term);	
	}
	else
	{
		tcgetattr(0, &hist.term);
		hist.term.c_lflag |= ~(ECHO);
		hist.term.c_lflag |= ~(ICANON);
		hist.term.c_lflag |= ~(ISIG);
		tcsetattr(0, TCSANOW, &hist.term);
	}
}


int ft_putchar(int c)
{
	return (write(1, &c, 1));
}

// void	hist_saving(t_ter hist)
// {
// 	char 	buf[1024];
// 	int		i;

// 	hist.fd = open("hist_archieve", O_CREAT | O_APPEND | O_RDWR, 0666);
// 	if (!hist.fd)
// 		write(1, "history file openning/creation error", 37); // err_message("history file openning/creation error");
// 	i = 0;
// 	hist.str_len = read(0, buf, 1024);
// 	if (hist.str_len == -1)
// 		write(1, "reading str_input error", 24);// err_message("reading str_input error");
// 	hist.str = (char *)ft_calloc((hist.str_len + 1), sizeof(char));
// 	if (!hist.str)
// 		write(1, "malloc error", 13);
// 	while (buf[i] && buf[i] != '\n')
// 	{
// 		hist.str[i] = buf[i];
// 		i++;
// 	}
// 	hist.str[i] = '\n';
// 	i = write(hist.fd, hist.str, hist.str_len);
// 	if (i == -1)
// 		write(1, "writing str_input to file error", 32);
// 	free(hist.str);
// }

int	main(int argc, char const *argv[1])
{
	char str[2000];
	int l;
	t_ter 	hist;
	char *term_name;
	
	term_name = "xterm-256color";
	hist.f = 0;
	termcap_init(hist);
	tgetent(0, term_name);
	tputs(save_cursor, 1, ft_putchar);
	while (strcmp(str, "\4"))
	{
		do
		{
			l = read(0, str, 50);
			str[l] = '\0';
			if (!strcmp(str, "\e[A"))
			{
				tputs(restore_cursor, 0, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				write(1, "previous", 8);
				// printf("prev\n");
			}
			else if (!strcmp(str, "\e[B"))
			{
				tputs(restore_cursor, 0, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				write(1, "next", 4);
			}
			// else if (!strcmp(str, key_backspace) && !strcmp(str, "\177"))
			else if (!strcmp(str, "\177"))
			{
				tputs(cursor_left, 1, ft_putchar);
				tputs(tgetstr("dc", 0), 1, ft_putchar);
			}
			else
				write (1, str, l);
		} while (strcmp(str, "\n") && strcmp(str, "\4"));
	}
	write (1, "\n", 1);
	return 0;
}
