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

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*mem;

	mem = s;
	i = -1;
	while (++i < n)
		mem[i] = '\0';
}

void	err_message(char *error)
{
    write(1, "Error!\n", 7);
	write(1, error, ft_strlen(error));
    write(1, "\n", 1);
    exit(0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*pntr;

	pntr = (void *)malloc(count * size);
	if (NULL == pntr)
		err_message("Memory allocation error! Exit!");
	ft_bzero(pntr, count * size);
	return (pntr);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*pntr;

	pntr = (char*)ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	// if (NULL == pntr)
	// 	return (NULL);
	i = -1;
	while (s1[++i])
		pntr[i] = s1[i];
	i++;
	pntr[i] = '\0';
	return (pntr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str_n;
	size_t		k;
	size_t		sl;

	if (!s)
		return (0);
	sl = ft_strlen(s);
	if (start >= sl)
		return (ft_strdup(""));
	str_n = ft_calloc((len + 1), sizeof(char));
	if (!str_n)
		return (NULL);
	k = 0;
	while (k + start < sl && k < len)
	{
		*(str_n + k) = *(s + start + k);
		k++;
	}
	str_n[k] = '\0';
	return (str_n);
}

void	ft_free_str(char **arr)
{
	int		i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
	arr = NULL;
}

int		words_counter(const char *str, char dlmtr)
{
	int		wn; //words number
	int		ndf; //non dlmtr flag
	int		i;

	i = 0;
	wn = 0;
	ndf = 0;
	while (str[i])
	{
		if (str[i] != dlmtr && ndf == 0 && str[i + 1] != '\0')
			ndf = 1;
		else if (str[i] != dlmtr && ndf == 0 && str[i + 1] == '\0')
			wn++;
		else if (str[i] == dlmtr && ndf == 1)
		{
			wn++;
			ndf = 0;
		}
		i++;
	}
	return (wn);
}

void	parse_and_write_to_arr(char **arr, const char *str, char dlmtr, int wn)
{
	int				i;
	int				wi; //word indx
	size_t			len; //length number
	unsigned int	strt; //start indx

	i = -1;
	wi = 0;
	len = 0;
	strt = 0;
	while (wi < wn && str[++i])
	{
		if (str[i] != dlmtr)
		{
			strt = i;
			len = 1;
			while (str[++i] != dlmtr)
				len++;
			arr[wi] = ft_substr(str, strt, len);
			wi++;
			len = 0;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		wn; //words number

	wn = words_counter(s, c);
	arr = (char**)ft_calloc(wn + 1, sizeof(char*));
	parse_and_write_to_arr(arr, s, c, wn);
	return (arr);
}

int		main(void)
{
		// char	*str = ft_strdup("3   lorem   ipsum dolor     1");
		char	*str = ft_strdup("   lorem   ipsum dolor     sit amet, consectetur   adipiscing elit. Sed non risus. Suspendisse 1");
		char		c;
		char		**arrofp;
		int		i;	

		c = ' ';
		
		arrofp = ft_split(str, c);
		
		
		i = 0;
		while (arrofp[i] != NULL)
		{
			printf("arrofp[%d]:%s\n", i, arrofp[i]);
			i++;
		}
		
		while(1)
		{

		}
	return (0);
}
