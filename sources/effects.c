/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:01:22 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 18:01:23 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void			make_gray_scale(t_global *g)
{
	t_vector	c;
	int			j;
	double		a;

	g->filter_switch = 2;
	j = g->objn;
	if (j == 0)
		j = 1;
	while (j < g->argc + 1)
	{
		c = g->obj[j].color;
		a = (c.x * 0.3f + c.y * 0.59f + c.z * 0.11f);
		g->obj[j].color.x = a;
		g->obj[j].color.y = a;
		g->obj[j].color.z = a;
		j++;
	}
}

void			make_negative(t_global *g)
{
	t_vector	c;
	int			j;

	g->filter_switch = 3;
	j = g->objn;
	if (j == 0)
		j = 1;
	while (j < g->argc + 1)
	{
		c = g->obj[j].color;
		g->obj[j].color.x = (fabs(1.0f - g->obj[j].color.x));
		g->obj[j].color.y = (fabs(1.0f - g->obj[j].color.y));
		g->obj[j].color.z = (fabs(1.0f - g->obj[j].color.z));
		j++;
	}
}

void			blue_stereo(t_global *g)
{
	int			x;
	int			y;
	int			pos;

	pos = 0;
	x = -1;
	while (++x <= WIDTH)
	{
		y = -1;
		while (++y <= HEIGHT)
		{
			pos = (y * WIDTH + x);
			*(g->data_ptr_2 + pos) += (*(g->data_ptr + pos));
			*(g->data_ptr_2 + pos + 1) += (*(g->data_ptr + pos + 1));
		}
	}
}

void			red_stereo(t_global *g)
{
	int			x;
	int			y;
	int			pos;

	pos = 0;
	x = -1;
	while (++x <= WIDTH)
	{
		y = -1;
		while (++y <= HEIGHT)
		{
			pos = (y * WIDTH + x);
			*(g->data_ptr_2 + pos + 2) += (*(g->data_ptr + pos + 2) -
											*(g->data_ptr_2 + pos) / 16);
		}
	}
}

void			make_stereo(t_global *g)
{
	int			j;

	g->filter_switch = 4;
	j = g->objn;
	if (j == 0)
		j = 1;
	while (j < g->argc + 1)
	{
		g->img_ptr_2 = mlx_new_image(g->mlx_ptr, WIDTH, HEIGHT);
		g->data_ptr_2 =
		(int*)mlx_get_data_addr(g->img_ptr_2, &g->bpp, &g->sz_l, &g->e);
		init_vector(g->cam_pos, -6, 0, -100);
		start_threads(recalc, g);
		blue_stereo(g);
		init_vector(g->cam_pos, 6, 0, -90);
		start_threads(recalc, g);
		red_stereo(g);
		j++;
	}
	g->img_ptr = g->img_ptr_2;
}
