#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*mem;

	mem = s;
	i = -1;
	while (++i < n)
		mem[i] = '\0';
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

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (NULL == s)
		return (NULL);
	i = 0;
	if (c == '\0')
	{
		while (s[i])
			i++;
		return ((char*)&s[i]);
	}
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char*)&s[i]);
		i++;
	}
	return (NULL);
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
	i = -1;
	while (arr[++i])
	{
		if (exprt_f != 0)
			write(1, "declare -x ", 12);
		write(1, arr[i], ft_strlen(arr[i]));
		write(1, "\n", 1);
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


//////////ft_strtrim.c
int	ft_check_set(char smb, char const *check)
{
	int	i;

	i = 0;
	while (check[i] != '\0')
	{
		if (smb == check[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	char	*trimstr;
	size_t	i;
	size_t	len;
	size_t	j;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (str[i] != '\0' && ft_check_set(str[i], set))
		i++;
	if (i < len)
		while (ft_check_set(str[len - 1], set))
			len--;
	trimstr = (char *)malloc(sizeof(*str) * (len - i + 1));
	if (!trimstr)
		return (NULL);
	while (i + j < len)
	{
		trimstr[j] = str[i + j];
		j++;
	}
	trimstr[j] = '\0';
	return (trimstr);
}
// ////ft_strtrim()

// int		lindx(char const *s1, char const *set)
// {
// 	int		i;
// 	int		j;
// 	int		nomatch;

// 	i = -1;
// 	nomatch = 0;
// 	while (s1[++i])
// 	{
// 		j = -1;
//         while (set[++j])
// 			if (s1[i] != set[j])
// 				nomatch++;
// 		if (nomatch < ft_strlen(set))
// 			nomatch = 0;
// 		else
// 			return (i);		
// 	}
// 	return (0);
// }

// int		rindx(char const *s1, char const *set)
// {
// 	int		i;
// 	int		j;
// 	int		nomatch;

// 	i = ft_strlen(s1);
// 	nomatch = 0;
// 	while (--i > 0)
// 	{
// 		j = -1;
//         while (set[++j])
// 			if (s1[i] != set[j])
// 				nomatch++;
// 		if (nomatch < ft_strlen(set))
// 			nomatch = 0;
// 		else
// 			return (i);		
// 	}
// 	return (0);
// }

// char	*ft_strtrim(char *s1, char const *set)
// {
// 	char	*strtrim;
// 	int		i;
// 	int		j;

// 	if (s1 == NULL)
// 		return (NULL);
// 	i = rindx(s1, set);
// 	j = lindx(s1, set);
// 	strtrim = (char*)malloc((rindx(s1, set) - lindx(s1, set) + 2) * sizeof(char));
// 	if (NULL == strtrim)
// 		return (NULL);
// 	i = -1;
// 	j = lindx(s1, set) - 1;
// 	while (++i < (rindx(s1, set) - lindx(s1, set) + 1))
// 		strtrim[i] = s1[++j];
// 	if (lindx(s1, set) == 0 && rindx(s1, set) == 0)
// 		strtrim[0] = '\0';
// 	strtrim[i] = '\0';
// 	free(s1);
// 	return (strtrim);
// }

// ////

void	*ft_calloc(size_t count, size_t size)
{
	void	*pntr;

	pntr = (void *)malloc(count * size);
	if (NULL == pntr)
		err_message("Memory allocation error! Exit!");
	ft_bzero(pntr, count * size);
	return (pntr);
}

char	*fill_str(char *str, int len, int offset, int trm)
{
	char	*arr;
	int		i;

	arr = ft_calloc(len + 1, sizeof(char));
	// arr = (char*)malloc((len + 1) * sizeof(char));
	// if (NULL == arr)
	// 	err_message("pzdts");
	i = -1;
	while (++i < len)
		arr[i] = str[offset + i];
	arr[i] = '\0';
	if (trm != 0)
		arr = ft_strtrim(arr, "+");
	return (arr);
}

char	**parse_arg(char *str)
{
	char	**arr;
	int		len;
	int		offset;

	arr = ft_calloc(3, sizeof(char*));
	// arr = (char**)malloc(3 * sizeof(char*));
	// if (NULL == arr)
	// 	err_message("pzdts");
	arr[2] = NULL;
	len = 0;
	while (str[len] && str[len] != 61)
		len++;
	arr[0] = fill_str(str, len, 0, 43);
	if (NULL == ft_strchr(str, 61))
		offset = len;
	else
		offset = len + 1;
	len = 0;
	while(str[offset + len])
		len++;
	arr[1] = fill_str(str, len, offset, 0);
	return (arr);
}

// char	**parse_arg(char *str)
// {
// 	char	**arr;
// 	char	*tmp;
// 	int		len;
// 	int		offset;

// 	arr = (char**)malloc(4 * sizeof(char*));
// 	if (NULL == arr)
// 		err_message("pzdts");
// 	arr[3] = NULL;
// 	len = 0;
// 	while (str[len] && str[len] != 61)
// 		len++;
// 	arr[0] = fill_str(str, len, 0, 43);
// 	arr[1] = fill_str(str, len, 0, 43);
// 	tmp = arr[1];
// 	arr[1] = ft_strjoin(arr[0], "=");
// 	free(tmp);
// 	offset = len;
// 	offset++;
// 	len = 0;
// 	while(str[offset + len])
// 		len++;
// 	arr[2] = fill_str(str, len, offset, 0);
// 	return (arr);
// }

int     main()
{
    char    *str = "_=/Applications/Visual Studio Code.app/Contents/MacOS/Electron";
    char    **arr;

    arr = parse_arg(str);

    print2darr(arr, 0);
	while (1)
	{

	}
}