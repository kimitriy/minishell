#include "minishell.h"

void	print2darr(char **arr)
{
	int		n;
	int		i;

	n = 0;
	while (arr[n] != NULL)
		n++;
	i = -1;
	while (++i < n)
		printf("line:%d, %s\n", i, arr[i]);
}

// print_ppln(t_ppline *ppln)
// {

// }

void	print_set(t_set *s)
{
	int		si; //set indx
	int		pi; //ppln indx
	int		i;

	si = pi = i = 0;

	while (si < s->sn)
	{
		while (pi < s->set->pn)
		{
			while (i < s->set->ppline->n)
			{
				printf("s->set->ppline->cmnd:%s\n", s->set[si].ppline[pi].cmnd[i]);
				i++;
			}
			i = 0;
			pi++;
		}
		pi = 0;
		si++;
	}
}