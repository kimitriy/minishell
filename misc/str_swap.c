#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>



void	ft_bzero(void *s, int n)
{
	int				i;
	char	*mem;

	mem = s;
	i = 0;
	while (i < n)
	{
		mem[i] = '\0';
		i++;
	}
}

int		ft_strlen(const char *s)
{
	int		i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	err_message(char *error)
{
    write(1, "Error!\n", 7);
	write(1, error, ft_strlen(error));
    write(1, "\n", 1);
    exit(0);
}

char	*ft_strjoin(char const *s1, char const *s2)
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

void	ft_strcpy(char *dst, const char *src)
{
	int		i;

	if (dst == NULL || src == NULL)
		err_message("ft_strcpy error");
	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
}

// void	str_swap(char *str1, char *str2)
// {
// 	char	*tmp;
	
// 	tmp = str1;
// 	str1 = str2;
// 	str2 = tmp;
// }

void	str_swap(char *str1, char *str2)
{
	char	*tmp;
	int		l1;
	int		l2;

	l1 = ft_strlen(str1);
	l2 = ft_strlen(str2);

	tmp = (char*)malloc(1 * sizeof(char));
	tmp = ft_strjoin(tmp, str1);
	
	str1 = NULL;
	str1 = (char*)malloc(1 * sizeof(char));
	str1 = ft_strjoin(str1, str2);
	
	str2 = NULL;
	str2 = (char*)malloc(1 * sizeof(char));
	str2 = ft_strjoin(str2, tmp);
}

int		main(void)
{
	char	*str1 = "abc";
	char	*str2 = "def";

	str_swap(&str1, &str2);

	printf("str1: %s\n", str1);
	printf("str2: %s\n", str2);
}