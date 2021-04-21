/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:31:45 by smyriell          #+#    #+#             */
/*   Updated: 2021/04/21 17:26:29 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <term.h>
#  define BUFFER_SIZE 10

void	lexer(char *str);
int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strdup(char *s1);
int		get_next_line(int fd, char **line);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strdup_to_n(char *s1);
char	*ft_strchr_n(const char *s);
int		w2l(int fd, char *buf, char **line);
