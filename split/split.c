#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	if (start < 0 || len < 0 || s == NULL)
		return (NULL);
	substr = (char*)malloc((len + 1) * sizeof(char));
	if (NULL == substr)
		return (NULL);
	i = start;
	j = 0;
	while (i < (start + len) && start < ft_strlen(s))
	{
		substr[j] = s[i];
		i++;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}

// char	**ft_split(char const *s, char c)
// {
// 	char	**arr;
// 	size_t	wrdn;
// 	size_t	i;
// 	size_t	strt;

// 	if (!s)
// 		return (NULL);
// 	i = -1;
// 	wrdn = 0;
// 	while (s[++i])
// 		if ((s[i] == c && (s[i + 1] != c &&
// 		s[i + 1] != 0)) || (s[i] != c && s[i + 1] == 0))
// 			wrdn++;
// 	if (!(arr = (char**)malloc((wrdn + 1) * sizeof(char*))))
// 		return (NULL);
// 	i = -1;
// 	wrdn = 0;
// 	strt = 0;
// 	while (s[++i])
// 		if (s[i] == c && s[i + 1] != c)
// 			strt = i + 1;
// 		else if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
// 			arr[wrdn++] = ft_substr(s, strt, i - strt + 1);
// 	arr[wrdn] = NULL;
// 	return (arr);
// }

int		*wrd_cntr(char const *s, char c)
{
	int		i; //counter
	int		f; //flag
	int		**axlr; //[0] - word number, [1] - start i, [2] - length
	
	i = 0;
	f = 0;
	while (s[i])
	{
		if (s[i] != c && f == 0)
		{
			axlr[0]++;
			axlr[1] = i;
			f = 1;
		}
		else if (s[i] == c)
		{
			axlr[2] = i - axlr[1];
			f = 0;
		}
		i++;
	}
	return (axlr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		**axlr; //[0] - word number, [1] - start i, [2] - end i
	int		i; //line counter
	int		j; //symb counter
	
	if (!s)
		return (NULL);
	axlr = wrd_cntr(s, c);
	if (axlr[0] == 0)
		return (NULL);
	if (!(arr = (char**)malloc(axlr[0] * sizeof(char*))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < axlr[0])
	{
		while(s[l] != c)
		{
			arr[w][l] = c;
			l++;
		}
		w++;
		l = 0;
	}
	return (arr);
}

int		main(void)
{
	// while (1)
	// {
		// char	str[] = "   lorem   ipsum dolor  ";
		char	str[] = "   lorem   ipsum dolor     sit amet, consectetur   adipiscing elit. Sed non risus. Suspendisse 1";
		char		c;
		char		**arrofp;
		//size_t		i;	

		c = ' ';
		
		arrofp = ft_split(str, c);
		
		/*
		i = 0;
		while (arrofp[i])
		{
			printf("arrofp[i]:%s\n", arrofp[i]);
			i++;
		}
		*/
		printf("arrofp[0]:%s\n", arrofp[0]);
		printf("arrofp[1]:%s\n", arrofp[1]);
		printf("arrofp[2]:%s\n", arrofp[2]);
		printf("arrofp[3]:%s\n", arrofp[3]);
		printf("arrofp[4]:%s\n", arrofp[4]);
		printf("arrofp[5]:%s\n", arrofp[5]);
		printf("arrofp[25]:%s\n", arrofp[25]);
		printf("arrofp[26]:%s\n", arrofp[26]);
	// }
	return (0);
}
