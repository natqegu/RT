/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:33:26 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 20:33:27 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int				con(t_global *g)
{
	return (shot.x == g->ray->x && shot.y == g->ray->y);
}

void			free_arr(char **arr)
{
	int			i;

	i = 0;
	while (*(arr + i) != NULL)
	{
		free(*(arr + i));
		i++;
	}
}

int				putstr(char *s, int ret)
{
	int			i;

	i = 0;
	while (*(s + i) != '\0')
	{
		write(1, s + i, 1);
		i++;
	}
	return (ret);
}

void			screen(int *a, int x, int y, t_global *g)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (j < y)
	{
		i = 0;
		while (i < x)
		{
			mlx_pixel_put(g->mlx_ptr, g->win_ptr, i, j, *(a + j * x + i));
			i++;
		}
		j++;
	}
}

void			draw_vectile(t_vector *t, int w, int h, t_global *g)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			mlx_pixel_put(g->mlx_ptr, g->win_ptr, i, j,
							brg(scale(255, *(t + j * h + i))));
			i++;
		}
		j++;
	}
}

void			draw_func(t_global *g)
{
	int			i;

	i = -WIDTH / 2;
	while (i < WIDTH / 2)
	{
		mlx_pixel_put(g->mlx_ptr, g->win_ptr, i + WIDTH / 2,
									HEIGHT / 2 - i % 10, 0xFFFFFF);
		i++;
	}
}

int				x_close(t_global *g)
{
	if (g->music == 1)
		system("killall afplay");
	mlx_clear_window(g->mlx_ptr, g->win_ptr);
	system("leask RT");
	exit(free_hits(g));
	return (0);
}

void			first(t_global g)
{
	void		*menu;
	int			h;
	int			w;

	h = WIDTH;
	w = HEIGHT;
	menu = mlx_new_image(g.mlx_ptr, WIDTH, HEIGHT);
	g.data_ptr = (int *)mlx_get_data_addr(g.img_ptr, &g.bpp, &g.sz_l, &g.e);
	g.win_ptr = mlx_new_window(g.mlx_ptr, WHOLE_MENU, WHOLE_MENU, "RT");
	menu = mlx_xpm_file_to_image(g.mlx_ptr, "./menuu.XPM", &h, &w);
	mlx_put_image_to_window(g.mlx_ptr, g.win_ptr, menu, 0, 0);
}

void			finish(t_global g)
{
	mlx_hook(g.win_ptr, 4, 4, mouse_press, &g);
	mlx_hook(g.win_ptr, 2, 2, key_press, &g);
	mlx_hook(g.win_ptr, 6, 6, mouse_move, &g);
	mlx_hook(g.win_ptr, 17, 1L << 17, x_close, &g);
	mlx_loop(g.mlx_ptr);
}

int				main(int argc, char **argv)
{
	t_global	g;
	t_vector	ctr[argc];
	t_vector	kenobi[5];

	g.cam_pos = &kenobi[0];
	g.angle = &kenobi[1];
	g.ray = &kenobi[2];
	g.li = &kenobi[3];
	g.normal = &kenobi[4];
	g.mlx_ptr = mlx_init();
	if (!check_arg(argv, argc, &g, ctr))
		return (0);
	g.img_ptr = mlx_new_image(g.mlx_ptr, WIDTH, HEIGHT);
	first(g);

	copy_tcps(&g);

	t_tile		a;
	int			i;
	
	i = 0;
	while (i < 0)
	{
		a = g.obj[1].tile[2];
		screen(a.data_ptr, a.w, a.h, &g);
		i++;
	}
	start_threads(recalc, &g);

}
