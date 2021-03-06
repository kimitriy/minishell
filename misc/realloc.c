#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static char **ft_free(char **arr)
{
	int		i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
	arr = NULL;
	return (arr);
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

int		ft_strcmp(char *s1, char *s2)
{
	int		i;
	int		output;

	i = 0;
	output = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			break ;
		else
			i++;
	}
	output = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (output);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i] != '\0') && (s2[i] != '\0') && (i < (n - 1)))
	{
		if (s1[i] != s2[i])
			break ;
		else
			i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*pntr;

	pntr = (char*)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (NULL == pntr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		pntr[i] = s1[i];
		i++;
	}
	pntr[i] = '\0';
	return (pntr);
}

void	err_message(char *error)
{
    write(1, "Error!\n", 7);
	write(1, error, ft_strlen(error));
    write(1, "\n", 1);
    exit(0);
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

char	*str_in_arr(char **arr, char *str)
{
	int		i;

	i = -1;
	while (arr[++i])
	{
		if (0 == ft_strcmp(arr[i], str))
			return (arr[i]);
	}
	return (NULL);
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

char	**arr2d_copy(char **arr, int en)
{
	int		i; //arr indx
	char	**narr;

	narr = (char**)malloc((en + 1) * sizeof(char*));
	if (NULL == narr)
		err_message("pzdts");
	i = -1;
	while (++i < en)
	{
		if (NULL != arr[i])
			narr[i] = ft_strdup(arr[i]);
		else
			narr[i] = NULL;
	}
	narr[i] = NULL;
	return(narr);
}

char	*fill_str(char *str, int len, int offset, int trm)
{
	char	*arr;
	int		i;

	arr = (char*)malloc((len + 1) * sizeof(char));
	if (NULL == arr)
		err_message("pzdts");
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

	arr = (char**)malloc(3 * sizeof(char*));
	if (NULL == arr)
		err_message("pzdts");
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

char	*key_in_arr(char **arr, char *key)
{
	int		i;
	char 	**prsd_arr;

	i = -1;
	while (arr[++i])
	{
		prsd_arr = parse_arg(arr[i]);
		if (0 == ft_strcmp(prsd_arr[0], key))
		{
			ft_free(prsd_arr);
			return (arr[i]);
		}
		ft_free(prsd_arr);
	}
	return (NULL);
}

void	mark_str_to_del(char **arr, char *key)
{
	char	**prsd_arr;
	int		i;

	i = 0;
	while (arr[i])
	{
		prsd_arr = parse_arg(arr[i]);
		if (0 == ft_strcmp(prsd_arr[0], key))
		{
			arr[i][0] = '\0';
			ft_free(prsd_arr);
			return ;
		}
		ft_free(prsd_arr);
		i++;
	}
}

char	**ft_rlcc_del(char **arr, int nsize)
{
	char	**narr;
	int		i;
	int		j;

	narr = (char**)malloc((nsize + 1) * sizeof(char*));
	if (NULL == narr)
		err_message("realloc error");
	i = -1;
	j = 0;
	while (arr[++i])
	{
		if (arr[i][0] != '\0')
			narr[j] = ft_strdup(arr[i]);
		else
			continue;
		j++;
	}
	narr[j] = NULL;
	ft_free(arr);
	return (narr);
}

char	**ft_rlcc_add(char **arr, int nsize, char *str)
{
	char	**narr;

	narr = arr2d_copy(arr, nsize);
	narr[nsize - 1] = ft_strdup(str);
	return (narr);
}

char	**unst(char **arr, int osize, int nsize, char **prsd_str)
{
	char	**narr_1 = NULL;
	char	**narr_2 = NULL;

	narr_1 = arr2d_copy(arr, osize);
	mark_str_to_del(narr_1, prsd_str[0]);
	narr_2 = ft_rlcc_del(narr_1, nsize);
	ft_free(prsd_str);
	ft_free(arr);
	return (narr_2);
}

void	str_ovrwrite(char *pstr, char *str)
{
	free(pstr);
	pstr = NULL;
	pstr = ft_strdup(str);
	// return (pstr);
}

char	**exprt(char **arr, int nsize, char *str)
{
	char	**narr;

	narr = ft_rlcc_add(arr, nsize, str);
	ft_free(arr);
	return(narr);
}

char**	ft_realloc(char **arr, int osize, int nsize, char *str)
{
	char	**narr;
	char	**prsd_str;

	prsd_str = parse_arg(str);
	if (NULL != key_in_arr(arr, prsd_str[0])) //searches corresponding str upon the keys
	{
		if (nsize < osize) //?????????????????????????? unset
		{
			narr = unst(arr, osize, nsize, prsd_str);
			return (narr);
		}
		else if (nsize == osize)
			str_ovrwrite(key_in_arr(arr, prsd_str[0]), str);
		ft_free(prsd_str);
		return (arr);
	}
	else //there is no such key in the arr
		if (osize < nsize) //?????????????????????????? export
		{
			narr = exprt(arr, nsize, str);
			ft_free(prsd_str);
			return(narr);
		}
	ft_free(prsd_str);
	return (arr);
}

int		main()
{
	size_t	size = 4;
	size_t	n_size = 3;
	char	**arr;
	// char	**tmp;

	arr = (char**)malloc((size + 1) * sizeof(char*));

	arr[0] = ft_strdup("QW=111111");
	arr[1] = ft_strdup("QWE=22222");
	arr[2] = ft_strdup("WERT=3333");
	arr[3] = ft_strdup("ER=444444");
	arr[4] = NULL;

	printf("before:\n");
	print2darr(arr, 0);

	arr = ft_realloc(arr, size, n_size, "WERT");
	// arr = ft_realloc(arr, size, n_size, "TY=123456");
	
	printf("after:\n");
	print2darr(arr, 0);
	
	while (1)
	{

	}
	return (0);
}