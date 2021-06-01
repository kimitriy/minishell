#include "minishell.h"

void	print2darr(char **arr, int exprt_f)
{
	int		i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (exprt_f != 0)
			write(1, "declare -x ", 11);
		write(1, arr[i], ft_strlen(arr[i]));
		write(1, "\n", 1);
		// write(1, arr[i], ft_strlen(arr[i]));
		// write(1, "\n", 1);
		i++;
	}
}

// void	print2darr(char **arr, int exprt_f)
// {
// 	int		i;

// 	i = 0;
// 	while (arr[i] != NULL)
// 	{
// 		if (exprt_f != 0)
// 			write(1, "declare -x ", 12);
// 		write(1, arr[i], ft_strlen(arr[i]));
// 		write(1, "\n", 1);
// 		i++;
// 	}
// }

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
			printf("PIPE FD[%d][%d]: %d\n", i, j, arr[i][j]);
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
	int		i; //i == 0 - command, i >= 1 - args

	pi = ci = i = 0;

	while (pi < s->pn)
	{
		while (ci < s->st[pi].cn)
		{
			while (i < s->st[pi].pln[ci].n)
			{
				printf("s->st[%d].pln[%d].cmd[%d]: %s\n", pi, ci, i, s->st[pi].pln[ci].cmd[i]);
				i++;
			}
			i = 0;
			ci++;
		}
		ci = 0;
		pi++;
	}

	// print2darr(s->env, 0);
}