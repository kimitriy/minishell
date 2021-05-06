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

void	print2darr_int(int **arr)
{
	int		n;
	int		i;
	int		j;

	n = 0;
	// while (arr[n])
	// 	n++;
	i = 0;
	j = 0;
	while (arr[i])
	{
		while (arr[i][j])
		{
			printf("PIPE FD: %d\n", arr[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
}

void	print_arr_int(int *arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		printf("%d\n", arr[i]);
		i++;
	}
}

void	print_set(t_set *s)
{
	int		pi; //pipeline indx
	int		ci; //command indx
	int		i;

	pi = ci = i = 0;

	while (pi < s->pn)
	{
		while (ci < s->set[pi].cn)
		{
			while (i < s->set[pi].ppline[ci].n)
			{
				printf("s->set[%d].ppline[%d].cmnd[%d]: %s\n", pi, ci, i, s->set[pi].ppline[ci].cmnd[i]);
				i++;
			}
			i = 0;
			pi++;
		}
		ci = 0;
		pi++;
	}

	print2darr(s->env, 0);
}