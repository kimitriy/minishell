#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int		**give_memory(int axlr[10000][2], int w)
{
	int		**arr;
	int		i;

	i = -1;
	if (!(arr = (int**)malloc(w * sizeof(int*))))
		return (NULL);
	i = -1;
	while (++i < w)
	{
		if (!(arr[i] = (int*)malloc(2 * sizeof(int))))
			return (NULL);
		arr[i][0] = axlr[i][0];
		arr[i][1] = axlr[i][1];
	}
	return (arr);
}

int		**wrd_cntr(int *wn, char const *s, char c)
{
	int		i; //line symbol counter
	int		w; //words(lines) counter
	int		f; //flag
	int		axlr[10000][2];
	int		**arr;
	
	i = -1;
	w = 0;
	f = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			if (f == 0 && (f = 1))
				axlr[w][0] = i;
			if (s[i + 1] == '\0' && (axlr[w][1] = i - axlr[w][0] + 1))
				w++;
		}
		else if (s[i] == c && f == 1 && (axlr[w++][1] = i - axlr[w][0]))
			f = 0;
	}
	arr = give_memory(axlr, w);
	*wn = w;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	int		wn;
	int		**axlr;
	char	**arr;
	
	if (!s)
		return (NULL);
	axlr = wrd_cntr(&wn, s, c);
	if (!(arr = (char**)malloc(wn * sizeof(char*))))
		return (NULL);
	i = -1;
	while (++i < wn)
	{
		if (!(arr[i] = (char*)malloc(axlr[i][1] * sizeof(char))))
			return (NULL);
		k = -1;
		while (++k < axlr[i][1])
			arr[i][k] = s[k + axlr[i][0]];
	}
	arr[i] = NULL;
	free(axlr);
	return (arr);
}

int		main(void)
{
	// while (1)
	// {
		char	str[] = "3   lorem   ipsum dolor     1";
		// char	str[] = "   lorem   ipsum dolor     sit amet, consectetur   adipiscing elit. Sed non risus. Suspendisse 1";
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
		
		// printf("arrofp[0]:%s\n", arrofp[0]);
		// printf("arrofp[1]:%s\n", arrofp[1]);
		// printf("arrofp[2]:%s\n", arrofp[2]);
		// printf("arrofp[3]:%s\n", arrofp[3]);
		// printf("arrofp[4]:%s\n", arrofp[4]);
		// printf("arrofp[5]:%s\n", arrofp[5]);
		// printf("arrofp[25]:%s\n", arrofp[25]);
		// printf("arrofp[26]:%s\n", arrofp[26]);
	// }
	return (0);
}
