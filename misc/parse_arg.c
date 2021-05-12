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

char	*fill_str(char *str, int len, int offset)
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
	arr[0] = fill_str(str, len, 0);
	offset = len;
	offset++;
	len = 0;
	while(str[offset + len])
		len++;
	arr[1] = fill_str(str, len, offset);
	return (arr);
}

int     main()
{
    char    *str = "QW=qwerty=123";
    char    **arr;

    arr = parse_arg(str);

    print2darr(arr, 0);
	while (1)
	{

	}
}