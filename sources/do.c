/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:51:57 by vkarpova          #+#    #+#             */
/*   Updated: 2019/02/01 17:51:58 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			pixel_put_img(t_all *all, int x, int y, int color)
{
	if (x < WIN_X && y < WIN_Y)
	{
		color = mlx_get_color_value(all->mlx_ptr, color);
		ft_memcpy(all->img + 4 * WIN_X * y + x * 4, &color, sizeof(int));
	}
	all->img =
	mlx_get_data_addr(all->img_ptr, &all->bpp, &all->size_line, &all->endian);
}

void	threads1(t_all *all)
{
	int			i;
	t_all		new_all[CORES];
	pthread_t	thread[CORES];

	
	i = -1;
	while (++i < CORES)
	{
		all->start = i * (WIN_X / CORES) - 1;
		all->end = (i + 1) * (WIN_X / CORES);
		new_all[i].start = all->start;
		new_all[i].end = all->end;
		new_all[i].obj = all->obj;
		new_all[i].clos = all->clos;

		new_all[i].cam = all->cam;
		new_all[i].obj = all->obj;
		new_all[i].light = all->light;
		new_all[i].fd = all->fd;
		new_all[i].rot = all->rot;
		new_all[i].closest = all->closest;
		new_all[i].d = all->d;
		new_all[i].mlx_ptr = all->mlx_ptr;
		new_all[i].win_ptr = all->win_ptr;
		new_all[i].img_ptr = all->img_ptr;

		new_all[i].mlx_ptr_2 = all->mlx_ptr_2;
		new_all[i].win_ptr_2 = all->win_ptr_2;
		new_all[i].img_ptr_2 = all->img_ptr_2;

		new_all[i].img = all->img;
		new_all[i].size_line = all->size_line;
		new_all[i].bpp = all->bpp;
		new_all[i].endian = all->endian;
		new_all[i].color = all->color;

		new_all[i].x = all->x;
		new_all[i].x_max = all->x_max;
		new_all[i].depth_refl = all->depth_refl;
		new_all[i].depth_refl_spec = all->depth_refl_spec;
		new_all[i].depth_transp = all->depth_transp;
		new_all[i].depth_max = all->depth_max;
		new_all[i].mouse = all->mouse;
		new_all[i].is_cam = all->is_cam;
		new_all[i].is_light = all->is_light;
		new_all[i].loading = all->loading;
		new_all[i].start = all->start;
		new_all[i].end = all->end;
		pthread_create(&thread[i], NULL, do_it, &new_all[i]);
	}
	i = -1;
	while (++i < CORES)
		pthread_join(thread[i], NULL);
	mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_PTR, 0, 0);
}

void			*do_it(void *data_ptr)
{
	// double		x;
	double		y;
	t_vector	d;
	t_all		*all;

	all = (t_all *)data_ptr;
	// x = -WIN_X / 2 - 1;
	// while (x++ < WIN_X / 2)
	while (++all->start < all->end)
	{
		y = -WIN_Y / 2;
		while (y++ < WIN_Y / 2)
		{
			all->depth_refl = 0;
			all->depth_refl_spec = 0;
			all->depth_transp = 0;
			d = rotation(all, canvas_to_viewport(all, all->start, y));
			all->color = trace_ray(all, all->obj, all->cam, d);
			// pixel_put_img(all, x + WIN_X / 2, WIN_Y / 2 - y, all->color);
			pixel_put_img(all, all->start, WIN_Y / 2 - y, all->color);
		}
	}
	pthread_exit(0);
	// mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_PTR, 0, 0);
}

t_vector		canvas_to_viewport(t_all *all, double x, double y)
{
	t_vector	d;

	d.x = (double)(x / WIN_X);
	d.y = (double)(y / WIN_Y);
	d.z = all->d;
	return (d);
}

int				trace_ray(t_all *all, t_list *list, t_vector o, t_vector d)
{
	t_clos		closer;
	t_vec		vec;
	t_vector			color;
	t_vector			local_color;

	closer.obj = 0;
	closer = closer_obj(list, o, d, 0.1);
	if (closer.obj == NULL)
		return (FON);
	vec.o = o;
	vec.d = d;
	vec.v = minus(init_vector(0, 0, 0, 0), d);
	vec.p = plus(o, times(closer.clost, d));
	fig_normal(&vec, &closer);

	color = init_vector(0,0,0,0);
	if (closer.obj != NULL)
	{
		local_color = int_to_rgb(reflected_color(all, closer, &vec));
		if ((fig_reflect(closer.obj)) > 0)
			color = plus(color, reflect(all, &vec, closer, local_color));
		if (fig_transp(closer.obj) > 0)
			color = plus(color, transp(all, &vec, closer, local_color));
		if ((fig_reflect(closer.obj)) == 0 && (fig_transp(closer.obj) == 0))
			color = local_color;
	}
	return (rgb_to_int(color));
}

t_clos			closer_obj(t_list *list, t_vector o, t_vector d, double min)
{
	t_clos		closer;
	t_vector	a;

	a = init_vector(600000, 600000, 600000, 600000);
	closer.clost = 600000;
	closer.obj = 0;
	while (list && (list->content_size) > 0)
	{
		a = intersect_ray(list, o, d);
		if (a.t1 >= min && a.t1 <= 600000 && a.t1 < closer.clost)
		{
			closer.obj = list;
			closer.clost = a.t1;
		}
		if (a.t2 >= min && a.t2 <= 600000 && a.t2 < closer.clost)
		{
			closer.obj = list;
			closer.clost = a.t2;
		}
		list = list->next;
	}
	return (closer);
}
