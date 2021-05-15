#include "minishell.h"

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

void	print_set(t_set *s)
{
	int		si; //set indx
	int		pi; //ppln indx
	int		i;

	si = pi = i = 0;

	while (si < s->sn)
	{
		while (pi < s->set[si].pn)
		{
			while (i < s->set[si].ppline[pi].n)
			{
				printf("s->set[%d].ppline[%d].cmnd[%d]: %s\n", si, pi, i, s->set[si].ppline[pi].cmnd[i]);
				i++;
			}
			i = 0;
			pi++;
		}
		pi = 0;
		si++;
	}

	print2darr(s->env, 0);
}