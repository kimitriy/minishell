#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static char **ft_free(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
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

char	**arr2d_copy(char **arr, int en)
{
	int		i; //arr indx
	char	**narr;

	narr = (char**)malloc((en + 1) * sizeof(char*));
	if (NULL == narr)
		return (NULL);
	i = -1;
	while (++i < en)
	{
		if (NULL == arr[i])
			break;
		else
		{
			narr[i] = (char*)malloc(ft_strlen(arr[i]) * sizeof(char));
			ft_strcpy(narr[i], arr[i]);
		}
	}
	narr[i] = NULL;
	return(narr);
}

void	mark_str_to_del(char **arr, char *str)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (0 == ft_strcmp(arr[i], str))
			arr[i][0] = '\0';
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
		{
			narr[j] = (char*)malloc((nsize + 1) * sizeof(char));
			if (NULL == narr)
				err_message("realloc error");
			ft_strcpy(narr[j], arr[i]);
		}
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
	narr[nsize - 1] = (char*)malloc(ft_strlen(str) * sizeof(char));
	ft_strcpy(narr[nsize - 1], str);
	return (narr);
}

char	**ft_realloc(char **arr, int osize, int nsize, char *str)
{
	char	**narr_1 = NULL;
	char	**narr_2 = NULL;

	if (NULL != str_in_arr(arr, str))
	{
		if (nsize < osize) //соответствует unset
		{
			narr_1 = arr2d_copy(arr, osize);
			mark_str_to_del(narr_1, str);
			narr_2 = ft_rlcc_del(narr_1, nsize);
			return (narr_2);
		}
		else
			return (arr);
	}
	else
	{
		if (osize < nsize) //соответствует export
		{
			narr_1 = ft_rlcc_add(arr, nsize, str);
			return (narr_1);
		}
		else
			return (arr);
	}
}

int		main()
{
    int		i;
	int		j;
	size_t	size = 5;
	size_t	n_size = 4;
	char	**arr;
	char	**tmp;

	arr = (char**)malloc((size + 1) * sizeof(char*));

	i = 0;
	while (i < (int)size)
	{
		arr[i] = (char*)malloc((i + 1) * sizeof(char));
		j = 0;
		while (j < (i + 1))
		{
			arr[i][j] = 'q';
			j++;
		}
		arr[i][j] = '\0';
		i++;
	}
	arr[i] = NULL;

	printf("before:\n");
	print2darr(arr, 0);

	tmp = arr;
	arr = ft_realloc(arr, size, n_size, "qqq");
	
	printf("after:\n");
	print2darr(arr, 0);
	ft_free(tmp);
	while (1)
	{
		
	}
	return (0);
}