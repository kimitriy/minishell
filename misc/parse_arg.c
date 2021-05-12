#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

void	print2darr(char **arr, int exprt_f)
{
	int		n;
	int		i;

	n = 0;
	while (arr[n] != NULL)
		n++;
	i = -1;
	while (++i < n)
	{
		if (exprt_f != 0)
			write(1, "declare -x ", 11);
			// printf("declare -x ");
		write(1, arr[i], ft_strlen(arr[i]));
		write(1, "\n", 1);
		// printf("%s\n", arr[i]);
		// printf("line:%d, %s\n", i, arr[i]);
	}
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

////ft_strtrim()

size_t	lindx(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	nomatch;

	i = -1;
	nomatch = 0;
	while (s1[++i])
	{
		j = -1;
        while (set[++j])
			if (s1[i] != set[j])
				nomatch++;
		if (nomatch < (size_t)ft_strlen(set))
			nomatch = 0;
		else
			return (i);		
	}
	return (0);
}

size_t	rindx(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	nomatch;

	i = ft_strlen(s1);
	nomatch = 0;
	while (--i > 0)
	{
		j = -1;
        while (set[++j])
			if (s1[i] != set[j])
				nomatch++;
		if (nomatch < (size_t)ft_strlen(set))
			nomatch = 0;
		else
			return (i);		
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return (NULL);
	strtrim = (char*)malloc((rindx(s1, set) - lindx(s1, set) + 2) * sizeof(char));
	if (NULL == strtrim)
		return (NULL);
	i = -1;
	j = lindx(s1, set) - 1;
	while (++i < (rindx(s1, set) - lindx(s1, set) + 1))
		strtrim[i] = s1[++j];
	if (lindx(s1, set) == 0 && rindx(s1, set) == 0)
		strtrim[0] = '\0';
	strtrim[i] = '\0';
	return (strtrim);
}

////

char	*fill_str(char *str, int len, int offset, int trm)
{
	char	*arr;
	char	*tmp;
	int		i;

	arr = (char*)malloc((len + 1) * sizeof(char));
	if (NULL == arr)
		err_message("pzdts");
	i = -1;
	while (++i < len)
		arr[i] = str[offset + i];
	arr[i] = '\0';
	tmp = arr;
	if (trm != 0)
		arr = ft_strtrim(arr, "+");
	free(tmp);
	return (arr);
}

// char	**parse_arg(char *str)
// {
// 	char	**arr;
// 	int		len;
// 	int		offset;

// 	arr = (char**)malloc(3 * sizeof(char*));
// 	if (NULL == arr)
// 		err_message("pzdts");
// 	arr[2] = NULL;
// 	len = 0;
// 	while (str[len] && str[len] != 61)
// 		len++;
// 	arr[0] = fill_str(str, len, 0);
// 	offset = len;
// 	offset++;
// 	len = 0;
// 	while(str[offset + len])
// 		len++;
// 	arr[1] = fill_str(str, len, offset);
// 	return (arr);
// }

char	**parse_arg(char *str)
{
	char	**arr;
	char	*tmp;
	int		len;
	int		offset;

	arr = (char**)malloc(4 * sizeof(char*));
	if (NULL == arr)
		err_message("pzdts");
	arr[3] = NULL;
	len = 0;
	while (str[len] && str[len] != 61)
		len++;
	arr[0] = fill_str(str, len, 0, 43);
	arr[1] = fill_str(str, len, 0, 43);
	tmp = arr[1];
	arr[1] = ft_strjoin(arr[0], "=");
	free(tmp);
	offset = len;
	offset++;
	len = 0;
	while(str[offset + len])
		len++;
	arr[2] = fill_str(str, len, offset, 0);
	return (arr);
}

int     main()
{
    char    *str = "QW+=qwerty=123+";
    char    **arr;

    arr = parse_arg(str);

    print2darr(arr, 0);
	while (1)
	{

	}
}