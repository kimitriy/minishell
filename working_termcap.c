/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_termcap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:10:33 by smyriell          #+#    #+#             */
/*   Updated: 2021/05/03 17:22:27 by smyriell         ###   ########.fr       */
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

char	*ft_strndup(char *s1, int n)
{
	char	*p_s1;
	int		i;

	p_s1 = (char*)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (NULL == p_s1)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		p_s1[i] = s1[i];
		i++;
	}
	p_s1[i] = '\0';
	return (p_s1);
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*sjn;
	int		i;
	int		lens1;
	int		lens2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!(sjn = (char*)malloc((lens1 + lens2 + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < lens1)
	{
		sjn[i] = s1[i];
		i++;
	}
	while (i < (lens1 + lens2))
	{
		sjn[i] = s2[i - lens1];
		i++;
	}
	sjn[i] = '\0';
	return (sjn);
}

int		ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}


char	*ft_strdup(const char *s1)
{
	char	*p_s1;
	size_t	i;

	p_s1 = (char*)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (NULL == p_s1)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		p_s1[i] = s1[i];
		i++;
	}
	p_s1[i] = '\0';
	return (p_s1);
}

void termcap_init(t_ter *hist)
{
	if (hist->f == 0)
	{
		tcgetattr(0, &hist->term);
		hist->term.c_lflag &= ~(ECHO);
		hist->term.c_lflag &= ~(ICANON);
		hist->term.c_lflag &= ~(ISIG);
		tcsetattr(0, TCSANOW, &hist->term);	
	}
	else
	{
		tcgetattr(0, &hist->term);
		hist->term.c_lflag |= ~(ECHO);
		hist->term.c_lflag |= ~(ICANON);
		hist->term.c_lflag |= ~(ISIG);
		tcsetattr(0, TCSANOW, &hist->term);
	}
}

t_list *ft_lstnew(char *content)
{
    t_list *new;
    new = malloc(sizeof(t_list));
    if (!new)
        return (NULL);
    new->data = content;
	new->dup = content;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

void delete_node(t_list **list)
{
    t_list *mouse;
	t_list *headphone;
	t_list *phone;

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
	if (!mouse)
	{
		if (headphone)
			headphone->next = NULL;	
	}
	else
	{
		if (headphone)
			mouse->prev = headphone;
		else
			mouse->prev = NULL;//???
	}
	// free(phone->data);
	// free(phone->dup);
	free(phone);
	if (!headphone && !mouse)
		*list = NULL;
}

void    ft_lstadd_back(t_list **list, t_list *new)
{
	t_list	*tmp;
	t_list	*pr;

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

void saving_input_to_file(t_ter *hist)
{
	int		i;
	int		n;
	char	*str;
	
	n = ft_strlen(hist->current_hist_command->prev->data);
	hist->fd = open("History_file", O_CREAT | O_APPEND | O_RDWR, 0666);
	printf("fd = %d\n", hist->fd);
	printf("cur hist = %s\n", hist->current_hist_command->prev->data);
	if (!hist->fd)
		write(1, "history file openning/creation error", 37); // err_message("history file openning/creation error");
	if (hist->current_hist_command->prev)
		{
			str = ft_strjoin(hist->current_hist_command->prev->data, "\n");
			n = ft_strlen(str);
			i = write(hist->fd, str, n);
			printf("cur hist = %s\n", hist->current_hist_command->prev->data);
			if (i == -1)
				write(1, "writing str_input to file error", 32);
		}
	close(hist->fd);
}

void	new_input(t_ter *hist)
{
	t_list *tmp;
	
	write(1, "\n", 1);
	
	// t_list *buf = hist->hist_list;
	// while (buf) {
	// 	printf("%s\n", buf->data);
	// 	buf = buf->next;
	// }
	
	if (hist->current_hist_command->next != NULL)
	{
		t_list *del;
		
		del = hist->hist_list;
		tmp = ft_lstnew(hist->current_hist_command->data);
		if (!tmp)
			write (1, "err", 3);
		hist->current_hist_command->data = hist->current_hist_command->dup;
		while (del->next != NULL)
			del = del->next;
		if (del->data[0] == '\0')
			delete_node(&del);			
		ft_lstadd_back(&hist->hist_list, tmp);// protect lst_new
		hist->current_hist_command = tmp;
		hist->symbols_count = 0;
	}
	if (hist->current_hist_command->data[0] != '\0')
	{
		tmp = ft_lstnew("");
		if (!tmp)
			write (1, "err", 3); //err message
			ft_lstadd_back(&hist->hist_list, tmp);// protect lst_new
			hist->current_hist_command = tmp;
			hist->symbols_count = 0;
		}
	// }
}

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	new_command(t_ter *hist, char *buf)
{
	char	*tmp;
	char	*tmp_dup;
	
	
	tmp = hist->current_hist_command->data;
	hist->current_hist_command->data = ft_strjoin(tmp, buf);
	if (!strcmp(tmp, hist->current_hist_command->data) || tmp[0] != '\0')// нужно рассмотреть вариант если два раза подряд изменяю одну и ту же строчку истории 
		free(tmp);
	if (!hist->current_hist_command->next)
	{
		// // hist->current_hist_command->dup = ft_strdup(hist->current_hist_command->data);
		// tmp_dup = ft_strdup(hist->current_hist_command->data);
		// hist->current_hist_command->dup = ft_strdup(tmp_dup);
		// if (tmp_dup[0] != '\0')
		// free(tmp_dup);
		hist->current_hist_command->dup = hist->current_hist_command->data;
	}
	write(1, buf, ft_strlen(buf));
	hist->symbols_count = ft_strlen(hist->current_hist_command->data);
}

void	previous_command(t_ter *hist)
{
	int		n;

	if (hist->current_hist_command->prev != NULL)
	{
		tputs(restore_cursor, 0, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		n = ft_strlen(hist->current_hist_command->prev->data);
		write(1, hist->current_hist_command->prev->data, n);
		hist->current_hist_command = hist->current_hist_command->prev;
		hist->symbols_count = n;
	}
}

void	next_command(t_ter *hist)
{
	int		n;

	
	if (hist->current_hist_command->next != NULL)
	{
		tputs(restore_cursor, 0, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);	
		n = ft_strlen(hist->current_hist_command->next->data);
		write(1, hist->current_hist_command->next->data, n);
		hist->current_hist_command = hist->current_hist_command->next;
		hist->symbols_count = n;
	}
}

void	delete_symbol(t_ter *hist)
{	int	n;

	n = ft_strlen(hist->current_hist_command->data);
	if (hist->symbols_count > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		hist->symbols_count--;
	}
	hist->current_hist_command->data = ft_strndup(hist->current_hist_command->data, n - 1);
}

void	ft_input(t_ter *hist)
{
	char	str[42];
	int		len;

	hist->symbols_count = 0;// переделать
	tgetent(0, hist->term_name);
	tputs(save_cursor, 1, ft_putchar);
	while (1)
	{
		len = read(0, str, 41);
		if (len == -1)
			write(1, "reading str_input error", 24);// err_message("reading str_input error");
		str[len] = 0;
		if (!strcmp(str, "\e[A"))
			previous_command(hist);
		else if (!strcmp(str, "\e[B"))
			next_command(hist);
		else if (!strcmp(str, "\177"))
			delete_symbol(hist);
		else if (!strcmp(str, "\4"))
			exit(0);
		else if (!strcmp(str, "\e[C"))
			continue;
		else if (!strcmp(str, "\e[D"))
			continue;
		else if (strcmp(str, "\n"))
			new_command(hist, str);
		else
		{
			new_input(hist);
			break;
		}
	}
	//saving_input_to_file(hist); - в конец перед выходом программы запихнуть
	// parsing(hist);
}

int		main()
{
	t_ter 	hist;

	hist.hist_list = ft_lstnew("");
	if (hist.hist_list == NULL)
		write(1, "error creation a list\n", 22);// error_message
	hist.current_hist_command = hist.hist_list;// добавить это в инициализацию ниже
	// init_all_struct(encp, &all_struct);
	while (1)
	{
		hist.f = 0;
		termcap_init(&hist);
		write (1, "\033[35mminishell>>> \x1b[0m", 23);
		ft_input(&hist);
	}
	printf("******hist->f = %d\n", hist.f);
	return 0;
}