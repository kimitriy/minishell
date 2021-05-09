#include <stdio.h>

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

int     main(void)
{
    char    *str1 = NULL;
    char    *str2 = "";

    int     res;

    res = ft_strcmp(str1, str2);

    printf("%d", res);

    return (0);
}