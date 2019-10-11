/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:10:51 by tpokalch          #+#    #+#             */
/*   Updated: 2019/07/17 21:25:14 by tpokalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		move_phys_1(int keycode, t_global *g)
{
	if (keycode == 0)
		g->obj[g->objn].ctr->x += -5;
	if (keycode == 2)
		g->obj[g->objn].ctr->x += 5;
	if (keycode == 34)
		g->obj[g->objn].ang.x -= 0.05;
	return (start_threads(move, g));
}

int		key_press_1(int kk, t_global *g)
{
	if (kk == 13 || kk == 1 || kk == 0 || kk == 2 || kk == 3 || kk == 125
		|| kk == 126 || kk == 38 || kk == 40 || kk == 37 || kk == 34
		|| kk == 123 || kk == 124)
		return (move_obj(kk, g));
	if (kk == 16)
		g->objn = (g->objn + 1) % (g->argc + 1);
	if (kk == 4 || kk == 5)
	{
		g->ray->z = fabs(g->ray->z + 10 * (2 * (kk == 4) - 1));
		copy_tcps(g);
		return (start_threads(recalc, g));
	}
	return (start_threads(toimg, g));
}

int		key_press(int kk, void *param)
{
	t_global	*g;

	g = param;
	g->shot.x = -WIDTH;
	ft_bzero((int *)g->data_ptr, g->sz_l * HEIGHT);
	if (kk == 53)
	{
		if (g->music == 1)
			system("killall afplay");
		exit(free_hits(g));
	}
	key_press_1(kk, g);
	if ((kk == 17 || kk == 15) && g->light_switch > 0 &&
							g->light_switch <= g->lights)
		g->liz[g->light_switch - 1] = g->liz[g->light_switch - 1]
									+ 15 * (2 * (kk == 15) - 1);
	if (kk == 49)
	{
		g->light_switch = (g->light_switch + 1) % (2 + g->lights);
		return (1);
	}
	return (start_threads(toimg, g));
}

int		move_phys(int keycode, t_global *g)
{
	if (keycode == 1 || keycode == 13)
		g->obj[g->objn].ctr->z += 5 * (2 * (keycode == 13) - 1);
	if (keycode == 126 || keycode == 125)
		g->obj[g->objn].ctr->y += 5 * (2 * (keycode == 126) - 1);
	move_phys_1(keycode, g);
	if (keycode == 40)
		g->obj[g->objn].ang.x += 0.05;
	if (keycode == 38)
		g->obj[g->objn].ang.y -= 0.05;
	if (keycode == 37)
		g->obj[g->objn].ang.y += 0.05;
	if (keycode == 43 || keycode == 124)
		g->obj[g->objn].ang.z -= 0.05;
	if (keycode == 47 || keycode == 123)
		g->obj[g->objn].ang.z += 0.05;
	if (keycode == 34 || keycode == 40 || keycode == 38 || keycode == 37
	|| keycode == 43 || keycode == 47 || keycode == 123 || keycode == 124)
	{
		g->obj[g->objn].base[0] = rotate(g->base[0], g->obj[g->objn].ang);
		g->obj[g->objn].base[1] = rotate(g->base[1], g->obj[g->objn].ang);
		g->obj[g->objn].base[2] = rotate(g->base[2], g->obj[g->objn].ang);
	}
	return (start_threads(move, g));
}

int		move_obj(int kk, t_global *g)
{
	if (g->objn != 0)
		return (move_phys(kk, g));
	if (kk == 126 || kk == 125 || kk == 38 || kk == 37
		|| kk == 0 || kk == 2 || kk == 123 || kk == 124)
	{
		if (kk == 125)
			g->angle->x += 0.05;
		if (kk == 126)
			g->angle->x -= 0.05;
		if (kk == 38)
			g->angle->z -= 0.05;
		if (kk == 37)
			g->angle->z += 0.05;
		if (kk == 0 || kk == 123)
			g->angle->y -= 0.05;
		if (kk == 2 || kk == 124)
			g->angle->y += 0.05;
		*g->normal = rotate(g->fifteen, *g->angle);
		return (start_threads(recalc, g));
	}
	if (kk == 1)
		*g->cam_pos = diff(*g->cam_pos, *g->normal);
	if (kk == 13)
		*g->cam_pos = sum(*g->cam_pos, *g->normal);
	return (start_threads(move, g));
}
