#include "rt.h"

int		myintmod(int x, int m)
{
	int ret;

	ret = fmod(x, m);
	if (x >= 0)
		return (ret);
	return (ret + m);
}

double	mymod(double x, int m)
{
	double ret;

	ret = fmod(x, m);
	if (x >= 0)
		return (ret);
	return (ret + m);
}

int		start_threads(void *f, t_global *g)
{
	int	i;

	i = -1;
	while (++i < CORES)
		pthread_create(&g->tid[i], NULL, f, g->tcps[i]);
	i = -1;
	while (++i < CORES)
		pthread_join(g->tid[i], NULL);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->img_ptr, 300, 120);
	return (1);
}
