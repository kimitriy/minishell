/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testik.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smyriell <smyriell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 14:39:50 by smyriell          #+#    #+#             */
/*   Updated: 2021/06/06 14:58:07 by smyriell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/types.h> //fork, kill
# include <sys/stat.h> //stat()
# include <unistd.h> //write(), read(), close(), chdir(), fork(), getcwd(), dup()/dup2(), pipe(), pid_t
# include <fcntl.h> //open()
# include <stdlib.h> //malloc(), realloc(), free(), exit(), execve()
# include <stdio.h> //getchar(), perror(), stderror()
# include <dirent.h> //opendir(), readir(), closedir()
# include <string.h> //strerror()
# include <term.h> //termcap
# include <curses.h> //
# include <errno.h> //errno

void	*ft_calloc(size_t count, size_t size) // ДОБАВИТЬ ДИМЕ
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

int	ft_strlen(const char *str)
{
	int	i;

	i = -1;
	while (str[++i]);
	return (i);
}

int	ft_check_string_and_symb(char *s1, char symb, char **sjn)
{
	int i;

	i = 0;
	if (s1 == NULL || s1[0] == '\0')
	{
		*sjn = (char *)ft_calloc(2, sizeof(char));
		*sjn[i] = symb;
		*sjn[++i] = '\0';
		return (1);
	}
	else
		return (0);
}

char	*ft_strjoin_symb(char *s1, char symb)
{
	char	*sjn;
	int		i;
	int		lens1;

	i = 0;
	if (ft_check_string_and_symb(s1, symb, &sjn))
		return (sjn);
	if (!symb)
		return (s1);
	lens1 = ft_strlen(s1);
	sjn = (char *)malloc((lens1 + 1 + 1) * sizeof(char));
	if (NULL == sjn)
		return (NULL);
	while (i < lens1)
	{
		sjn[i] = s1[i];
		i++;
	}
	sjn[i] = symb;
	sjn[++i] = '\0';
	return (sjn);
}

int	main()
{
	char *str;
	char ch;
	char *str_finish;
	char ch2;
	char *str_finish2;

	str = "abc";
	ch = 'd';
	ch2 = 'e';
	str_finish = ft_strjoin_symb(str, ch);
	str_finish = ft_strjoin_symb(str_finish, ch2);
	str_finish = ft_strjoin_symb(str_finish, ch);
	printf("str finish = %s\n", str_finish);
	printf("str finish2 = %s\n", str_finish2);
	return 0;	
}
