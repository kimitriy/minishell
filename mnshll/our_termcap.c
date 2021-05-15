/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_termcap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 21:09:52 by smyriell          #+#    #+#             */
/*   Updated: 2021/05/01 00:09:12 by smyriell         ###   ########.fr       */
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

// typedef struct	s_ter
// {
// 	char 			**hist_arr;
// 	int				j;// - двигаемся по строчкам массива
// 	struct termios	term;
// 	int				i;                                                                         
// 	char			*str;
// 	int				str_len;
// 	int				f;
// 	int				fd;
// 	char 			*term_name;
// }				t_ter;

int ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void		ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*p;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

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

void termcap_init(t_ter *hist)
{
	hist->term_name = "xterm-256color";
	
	if (hist->f == 0)
	{
		tcgetattr(0, &hist->term);
		hist->term.c_lflag &= ~(ECHO);
		hist->term.c_lflag &= ~(ICANON);
		hist->term.c_lflag &= ~(ISIG);
		tcsetattr(0, TCSANOW, &hist->term);	
	}
	else if (hist->f == 1)
	{
		tcgetattr(0, &hist->term);
		hist->term.c_lflag |= ~(ECHO);
		hist->term.c_lflag |= ~(ICANON);
		hist->term.c_lflag |= ~(ISIG);
		tcsetattr(0, TCSANOW, &hist->term);
	}
}


void	hist_to_file(t_ter *hist)
{
	int		i;
	int		j;
	tgetent(0, hist->term_name);
	tputs(save_cursor, 1, ft_putchar);
	hist->fd = open("new1", O_CREAT | O_APPEND | O_RDWR, 0666);
	if (!hist->fd)
		write(1, "history file openning/creation error", 37); // err_message("history file openning/creation error");
	i = 0;
	j = 0;
	hist->str_len = read(0, hist->buf, 1024);
	if (hist->str_len == -1)
		write(1, "reading str_input error", 24);// err_message("reading str_input error");
	hist->str = (char *)ft_calloc((hist->str_len + 1), sizeof(char));
	while (hist->buf[i])
	{
		// while (hist->buf[i] == '\n' && hist->buf[i - 1] == '\n')
		// 	i++;
		hist->str[j] = hist->buf[i];
		i++;
		j++;
	}
	hist->str[j] = '\n';
	i = write(hist->fd, hist->str, hist->str_len);
	if (i == -1)
		write(1, "writing str_input to file error", 32);
	write (1, hist->str, hist->str_len);
	free(hist->str);
	
	// if (strcmp(buf, "\4") == 0)
	// 	i = write(hist->fd, "\n", 1);
	close(hist->fd);
	hist->f = 1;
	termcap_init(hist);
	printf("1111******hist->f = %d\n", hist->f);
}

int			main()
{
	
	t_ter 	hist;
	char	buf[1024] = {'\0'};
	while (strcmp(hist.buf, "\4") || strcmp(hist.buf, "\n"))
	{
		hist.f = 0;
		termcap_init(&hist);
		hist_to_file(&hist);
	}
	hist.f = 1;
	printf("******hist->f = %d\n", hist.f);
	// buf = (char*)ft_calloc(1024, sizeof(char));
	
	
		// while (strcmp(hist.str, "\4"))
		// {} 
	// 	while (strcmp(buf, "\n"))
	// {
	// 	do
	// 	{
	// 		hist.str_len = read(0, buf, 1024);
	// 		if (hist.str_len == -1)
	// 			write(1, "reading str_input error", 24);// err_message("reading str_input error");
	// 		buf[hist.str_len] = '\0';
	// 		if (!strcmp(buf, "\e[A"))
	// 		{ 
	// 			// обращаемся к массиву c историей, если ничего не было то, ничего не выводим
	// 			tputs(restore_cursor, 0, ft_putchar);
	// 			tputs(tigetstr("ed"), 1, ft_putchar);
	// 			write(1, "previous", 8); // предыдущую строку
	// 			// printf("prev\n");
	// 		}
	// 		else if (!strcmp(buf, "\e[B"))
	// 		{
	// 			tputs(restore_cursor, 0, ft_putchar);
	// 			tputs(tigetstr("ed"), 1, ft_putchar);
	// 			write(1, "next", 4);
	// 		}
	// 		// else if (!strcmp(str, key_backspace) && !strcmp(str, "\177"))
	// 		else if (!strcmp(buf, "\177"))
	// 		{
	// 			tputs(cursor_left, 1, ft_putchar);
	// 			tputs(tgetstr("dc", 0), 1, ft_putchar);
	// 		}
	// 		else
	// 			write (1, buf, hist.str_len);
	// 	} while (strcmp(buf, "\n") && strcmp(buf, "\4"));
	// }
	// write (1, "\n", 1);
	return 0;
}