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

	// while (s->set)
	// {
	// 	while (s->set->ppline)
	// 	{
	// 		while (s->set->ppline->cmnd)
	// 		{
	// 			print2darr(s->set->ppline->cmnd);
	// 			s->set->ppline->cmnd++;
	// 		}
	// 		s->set->ppline++;
	// 	}
	// 	s->set++;
	// }
	print2darr(s->set[0].ppline[0].cmnd);
	
	// print2darr(s->env);
}