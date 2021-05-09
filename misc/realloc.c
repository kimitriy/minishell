#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



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

char	**arr2d_copy(char **arr, int en)
{
	int		i;
	char	**narr;

	narr = (char**)malloc(en * sizeof(char*));
	if (NULL == narr)
		return (NULL);
	i = 0;
	while (i < en)
	{
		narr[i] = (char*)malloc(ft_strlen(arr[i]) * sizeof(char));
		if (arr[i] == NULL)
		{
			i++;
			break;
		}
		ft_strcpy(narr[i], arr[i]);
		write(1, "narr[i]: ", 9);
		write(1, narr[i], ft_strlen(narr[i]));
		write(1, "\n", 1);
		// printf("narr[%d]: %s", j, narr[j]);
		i++;
	}
	narr[i] = NULL;
	return(narr);
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
			printf("declare -x ");
		printf("%s\n", arr[i]);
		// printf("line:%d, %s\n", i, arr[i]);
	}
}

char	**ft_realloc(char **arr, int osize, int nsize, char *str)
{
	char	**narr = NULL;
	// char	*tmp;

	if (NULL != str_in_arr(arr, str))
	{
		if (nsize < osize) //соответствует unset
		{
			//subtract a string
			free(str_in_arr(arr, str));
			narr = arr2d_copy(arr, nsize);
		}
	}
	else
	{
		if (osize < nsize) //соответствует export
		{
			//add a string
			narr = arr2d_copy(arr, nsize);
			ft_strcpy(narr[nsize - 1], str);
		}
	}
	//in other cases do nothing
	return (narr);
}

int		main()
{
    int		i;
	int		j;
	size_t	size = 5;
	size_t	n_size = 6;
	char	**arr;

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

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		while (arr[i][j] != '\0')
		{
			printf("arr[%d][%d]: %c ; ", i, j, arr[i][j]);
			j++;
		}
		j = 0;
		i++;
		printf("\n");
	}

	arr = ft_realloc(arr, size, n_size, "bbb");

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		printf("arr[%d][%d]: %c ; ", i, j, arr[i][j]);
		while (arr[i][j])
		{
			// write(1, "arr[i]: ", 8);
			// write(1, arr[i], ft_strlen(arr[i]));
			// write(1, "\n", 1);
			printf("arr[%d][%d]: %c ; ", i, j, arr[i][j]);
			j++;
		}
		j = 0;
		i++;
		printf("\n");
	}
}