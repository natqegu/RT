/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:40:40 by nnovikov          #+#    #+#             */
/*   Updated: 2019/10/10 20:40:42 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	move_row(int j, int jheight, t_global *g)
{
	int			i;
	t_dstpst	ret;
	t_colbri	bright;

	i = -1;
	while (++i < WIDTH)
	{
		objecthit(&ret, create_3_vecs(*g->cam_pos, NULL, sum(*g->rays[j][i],
										*g->cam_pos)), g->obj, g->argc + 1);
		g->hits[j][i]->hit = sum(scale(ret.dst, *g->rays[j][i]), *g->cam_pos);
		g->hits[j][i]->obj = ret.obj;
		if (g->hits[j][i]->obj.name != NULL)
		{
			bright = ret.obj.bright(*g->cam_pos, (g->hits[j][i])->hit,
												&(g->hits)[j][i]->obj, g);
			g->data_ptr[jheight + i] = color(bright.bri, bright.col);
		}
		else
			g->data_ptr[jheight + i] = 0;
	}
}

void	*move(void *p)
{
	t_global	*g;
	int			j;
	int			end;
	int			jheight;

	g = (t_global *)p;
	end = (g->core + 1) * HEIGHT / CORES;
	j = g->core * HEIGHT / CORES - 1;
	jheight = j * HEIGHT;
	while (++j < end)
	{
		jheight += HEIGHT;
		move_row(j, jheight, g);
	}
	return (NULL);
}

void	load(t_global *g, int j)
{
	if (g->core == 4)
		printf("LOADING %d%c\n", (int)((j / (double)(HEIGHT
						/ (double)CORES)) * 100 + 4), '%');
}

void	recalc_row(int jheight, int j, t_global *g)
{
	t_vector	ray;
	t_dstpst	ret;
	int			i;
	t_colbri	bright;

	i = -1;
	load(g, j);
	while (++i < WIDTH)
	{
		init_vector(&ray, i - WIDTH_2, HEIGHT_2 - j, g->ray->z);
		ray = rotate(ray, *g->angle);
		*g->rays[j][i] = ray;
		objecthit(&ret, create_3_vecs(*g->cam_pos, NULL, sum(ray, *g->cam_pos)),
														g->obj, g->argc + 1);
		g->hits[j][i]->obj = ret.obj;
		g->hits[j][i]->hit = sum(scale(ret.dst, *g->rays[j][i]), *g->cam_pos);
		if (g->hits[j][i]->obj.name != NULL)
		{
			bright = g->hits[j][i]->obj.
			bright(*g->cam_pos, g->hits[j][i]->hit, &(g->hits)[j][i]->obj, g);
			g->data_ptr[jheight + i] = color(bright.bri, bright.col);
		}
		else
			g->data_ptr[jheight + i] = 0;
	}
}

void	*recalc(void *p)
{
	t_global	*g;
	int			j;
	int			end;
	int			jheight;

	g = (t_global *)p;
	end = (g->core + 1) * HEIGHT / CORES;
	j = g->core * HEIGHT / CORES - 1;
	jheight = j * HEIGHT;
	while (++j < end)
	{
		jheight += HEIGHT;
		recalc_row(jheight, j, g);
	}
	return (NULL);
}
