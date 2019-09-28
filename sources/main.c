
#include "../includes/rt.h"

int			con(t_global *g)
{
	return (shot.x == g->ray->x && shot.y == g->ray->y);
}

void		free_arr(char **arr)
{
	int i;

	i = 0;
	while (*(arr + i) != NULL)
	{
		printf("now freeing %s\n", *(arr + i));
		free(*(arr + i));
		i++;
	}
}

int		putstr(char *s, int ret)
{
	int i;

	i = 0;
	while (*(s + i) != '\0')
	{
		write(1, s + i, 1);
		i++;
	}
	return (ret);
}

void		screen(int *a, int x, int y, t_global *g)
{
	int i = 0;
	int j = 0;
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

void		draw_vectile(t_vector *t, int w, int h, t_global *g)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			printf("we are at %d,%d\n", i, j);
			mlx_pixel_put(g->mlx_ptr, g->win_ptr, i, j, brg(scale(255, *(t + j * h + i))));
			i++;
		}
		j++;
	}
}


void		draw_func(t_global *g)
{
	int i = -WIDTH / 2;

	while (i < WIDTH / 2)
	{
		mlx_pixel_put(g->mlx_ptr, g->win_ptr, i + WIDTH / 2, HEIGHT / 2- i % 10, 0xFFFFFF);
		i++;
	}
}


int			x_close(t_global *g)
{
	if (g->music == 1)
			system("killall afplay");
	mlx_clear_window(g->mlx_ptr, g->win_ptr);
	exit(free_hits(g));;
	return (0);
}


int		main(int argc, char **argv)
{
	t_global g;
	t_vector ctr[argc];
	t_vector kenobi[5];
	int h;
	int w;

	h = WIDTH;
	w = HEIGHT;
	g.cam_pos = &kenobi[0];
	g.angle = &kenobi[1];
	g.ray = &kenobi[2];
	g.li = &kenobi[3];
	g.normal = &kenobi[4];
//	g.obj = (t_object *)malloc(sizeof(t_object) * (argc + 1));
	g.mlx_ptr = mlx_init();

    //    init_vector(&g.base[0], 1, 0, 0);
  //      init_vector(&g.base[1], 0, 1, 0);
//       init_vector(&g.base[2], 0, 0, 1);

	// ginit(&g);
	if (!check_arg(argv, argc, &g, ctr))
		return (0);

	g.img_ptr = mlx_new_image(g.mlx_ptr, WIDTH, HEIGHT);
	void *menu = mlx_new_image(g.mlx_ptr, WIDTH, HEIGHT);

	g.data_ptr = (int *)mlx_get_data_addr(g.img_ptr, &g.bpp, &g.sz_l, &g.e);
	g.win_ptr = mlx_new_window(g.mlx_ptr, WHOLE_MENU, WHOLE_MENU, "RT");

	menu = mlx_xpm_file_to_image(g.mlx_ptr, "./menuu.XPM", &h, &w);
	mlx_put_image_to_window(g.mlx_ptr, g.win_ptr, menu, 0, 0);
//	g.tile_ptr = mlx_new_image(g.mlx_ptr, WIDTH, HEIGHT);
//	g.tile_ptr = mlx_xpm_file_to_image(g.mlx_ptr, "./tiles/earth.xpm", &w, &h);
//	printf("%d,%d\n", w, h);
//	g.tile_data_ptr = (int *)mlx_get_data_addr(g.tile_ptr, &g.bpp1, &g.sz_l1, &g.e1);
//	mlx_put_image_to_window (g.mlx_ptr, g.win_ptr, g.tile_data_ptr, 0, 0);
//	printf("%d\n", *(g.tile_data_ptr + 2));
//	screen(700, 700, &g);
	printf("initing g\n");
//	ginit(&g);
	copy_tcps(&g);
	printf("hi\n");
	t_tile a;

	int i = 0;
	while (i < 0)
	{
		a = g.obj[1].tile[2];
		printf("h w is %d, %d\n", a.h, a.w);
//		stretch(a.data_ptr, a.h);
		screen(a.data_ptr, a.w, a.h, &g);
		i++;
	}
//	draw_func(&g);
//	printf("first obj bounds is %f,%f,%f\n", g.obj[1].tris[0].bd1.x, g.obj[1].tris[0].bd1.y, g.obj[1].tris[0].bd1.z);
//	printf("first obj bounds is %f,%f,%f\n", g.obj[1].tris[0].bd2.x, g.obj[1].tris[0].bd2.y, g.obj[1].tris[0].bd2.z);
//	printf("first obj bounds is %f,%f,%f\n", g.obj[1].tris[0].bd3.x, g.obj[1].tris[0].bd3.y, g.obj[1].tris[0].bd3.z);



//	printf("first obj bounds is %f,%f,%f\n", g.obj[1].tris[1].bd1.x, g.obj[1].tris[1].bd1.y, g.obj[1].tris[1].bd1.z);
//	printf("first obj bounds is %f,%f,%f\n", g.obj[1].tris[1].bd2.x, g.obj[1].tris[1].bd2.y, g.obj[1].tris[1].bd2.z);
//	printf("first obj bounds is %f,%f,%f\n", g.obj[1].tris[1].bd3.x, g.obj[1].tris[1].bd3.y, g.obj[1].tris[1].bd3.z);
//	printf("first complex obj is %d %s\n", g.obj[1].tris[0].id, g.obj[1].tris[0].name);
//	printf("second complex obj is %d %s\n", g.obj[1].tris[1].id, g.obj[1].tris[1].name);

	printf("starting threads\n");
	start_threads(recalc, &g);
	mlx_hook(g.win_ptr, 4, 4, mouse_press, &g);
	mlx_hook(g.win_ptr, 2, 2, key_press, &g);
	mlx_hook(g.win_ptr, 6, 6, mouse_move, &g);
	mlx_hook(g.win_ptr, 17, 1L << 17, x_close, &g);
	mlx_loop(g.mlx_ptr);
}


