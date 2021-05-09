#include <stdio.h>
#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

// char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
// {
// 	size_t	i;
// 	char	*return_value;
// 	char	*inner_hstck;

// 	i = 0;
// 	return_value = NULL;
// 	inner_hstck = (char*)haystack;
// 	if (strlen(needle) == 0)
// 		return (inner_hstck);
// 	while(inner_hstck[i] && i < len)
// 	{
// 		if (ft_strncmp(&inner_hstck[i], needle, ft_strlen(needle)) == 0)
// 		{
// 			return_value = &inner_hstck[i];	
// 			break;
// 		}
// 		i++;
// 	}
// 	if ((i - 1) + ft_strlen(needle) < len)
// 		return (return_value);
// 	else
// 		return (NULL);
// }

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*return_value;
	char	*inner_hstck;

	i = 0;
	return_value = NULL;
	inner_hstck = (char*)haystack;
	if (strlen(needle) == 0)
		return (inner_hstck);
	while(inner_hstck[i] && i < len)
	{
		if (ft_strncmp(&inner_hstck[i], needle, ft_strlen(needle)) == 0)
		{
			return_value = &inner_hstck[i];	
			break;
		}
		i++;
	}
	if ((i - 1) + ft_strlen(needle) < len)
		return (return_value);
	else
		return (NULL);
}

int		main(void)
{
	const char	*needle = "15";
	const char	*haystack = "015234556789";

	printf("ft %s\n", ft_strnstr(haystack, needle, 5));
	printf("lib %s\n", strnstr(haystack, needle, 5));

	return (0);
}
