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

int		key_press(int kk, void *param)
{
	t_global *g;

	g = param;
	shot.x = -WIDTH;
	ft_bzero((int *)g->data_ptr, g->sz_l * HEIGHT);
	if (kk == 53)
	{//	system("leaks -s rtv1");
//		system("leaks -s rtv1");	
		exit(free_hits(g));
	}
	else if (kk == 13 || kk == 1 || kk == 0 || kk == 2 || kk == 3 || kk == 125
		|| kk == 126 || kk == 38 || kk == 40 || kk == 37 || kk == 34
		|| kk == 123 || kk == 124)
		return(move_obj(kk, g));
	else if (kk == 16)
		g->objn = (g->objn + 1) % (g->argc + 1);
	else if (kk == 4 || kk == 5)
	{
		g->ray->z = fabs(g->ray->z + 10 * (2 * (kk == 4) - 1));
		copy_tcps(g);
		return (start_threads(recalc, g));
	}
	else if (kk == 17 || kk == 15)
		g->liz = g->liz + 15 * (2 * (kk == 15) - 1);
	else if (kk == 49)
	{
		g->light_switch = (g->light_switch + 1) % 3;
		return (1);
	}
	return (start_threads(toimg, g));
}

int		move_phys(int keycode, t_global *g)
{
	if (keycode == 1 || keycode == 13)
		g->obj[g->objn].ctr->z += 5 * (2 * (keycode == 13) - 1);
	else if	(keycode == 126 || keycode == 125)
		g->obj[g->objn].ctr->y += 5 * (2 * (keycode == 126) - 1);
	else if	(keycode == 0)
		g->obj[g->objn].ctr->x += -5;
	else if	(keycode == 2)
		g->obj[g->objn].ctr->x += 5;
	else if (keycode == 34)
		g->obj[g->objn].ang.x -= 0.05;
	else if (keycode == 40)
		g->obj[g->objn].ang.x += 0.05;
	else if (keycode == 38)
		g->obj[g->objn].ang.y -= 0.05;
	else if (keycode == 37)
		g->obj[g->objn].ang.y += 0.05;
	else if (keycode == 43 || keycode == 124)
		g->obj[g->objn].ang.z -= 0.05;
	else if (keycode == 47 || keycode == 123)
		g->obj[g->objn].ang.z += 0.05;
	if (keycode == 34 || keycode == 40 || keycode == 38 || keycode == 37
	|| keycode == 43 || keycode == 47 || keycode == 123 || keycode == 124)
	{
		g->obj[g->objn].base[0] = rotate(g->base[0], g->obj[g->objn].ang);
		g->obj[g->objn].base[1] = rotate(g->base[1], g->obj[g->objn].ang);
		g->obj[g->objn].base[2] = rotate(g->base[2], g->obj[g->objn].ang);
//		printf("base is %f,%f,%f\n", g->obj[g->objn].base[0].x, g->obj[g->objn].base[1].y, g->obj[g->objn].base[2].z);
	}

	return (start_threads(move, g));
}

int	move_obj(int kk, t_global *g)
{
	if (g->objn != 0)
		return (move_phys(kk, g));
	if (kk == 126 || kk == 125 || kk == 38 || kk == 37
		|| kk == 0 || kk == 2 || kk == 123 || kk == 124)
	{
		if (kk == 125)
			g->angle->x += 0.05;
		else if (kk == 126)
			g->angle->x -= 0.05;
		else if (kk == 38)
			g->angle->z -= 0.05;
		else if (kk == 37)
			g->angle->z += 0.05;
		else if (kk == 0 || kk == 123)
			g->angle->y -= 0.05;
		else if (kk == 2 || kk == 124)
			g->angle->y += 0.05;
		*g->normal = rotate(g->_0015, *g->angle);
		return (start_threads(recalc, g));
	}
	else if (kk == 1)
		*g->cam_pos = diff(*g->cam_pos, *g->normal);
	else if (kk == 13)
		*g->cam_pos = sum(*g->cam_pos, *g->normal);
	return (start_threads(move, g));
}

void		move_cam(char s, t_global *g)
{
	int i;

	i = 0;
	while (i < g->argc)
	{
		if (s == '+')
			*g->obj[i].ctr = sum(*g->obj[i].ctr, *g->normal);
		else
			*g->obj[i].ctr = diff(*g->obj[i].ctr, *g->normal);
		i++;
	}
}

int		mouse_move(int x, int y, void *param)
{
	t_global *g;
	int	i;
	t_vector p;
	double block;

	i = -1;
	g = param;
	mousex = x;
	if (g->light_switch == 1)
	{
			ft_bzero((int *)g->data_ptr, g->sz_l * HEIGHT);
			block = g->liz / g->ray->z;
			p.x = (-WIDTH / 2 + x) * block;
			p.y = (-y + HEIGHT / 2) * block;
			p.z = g->liz;
			*g->li = sum(*g->cam_pos, rotate(p, *g->angle));
			printf("starting threads with toimg\n");
			start_threads(toimg, g);
	}
	else if (g->light_switch == 2)
	{
		ft_bzero((int *)g->data_ptr, g->sz_l * HEIGHT);
		p.y = /*sin*/((-WIDTH / 2 + x )* 0.001);
		p.x = /*sin*/(0.001 * (y - HEIGHT / 2));
		p.z = 0;

//		*g->normal = rotate(g->_0015, p);

//		*g->angle = sum(p, *g->angle);
		*g->angle = p;

		*g->normal = rotate(g->_0015, p);

	
		start_threads(recalc, g);
	}
	return (1);
}
