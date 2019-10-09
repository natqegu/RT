/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 20:10:51 by tpokalch          #+#    #+#             */
/*   Updated: 2019/07/03 20:36:09 by tpokalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	obs1()
{
	
}

void	obstructed(t_colbri *cur, t_3_vecs co, t_object *obj, t_global *g)
{
	int i;
	int	iobjn[2];
	t_dstpst	t;
	int	obsc;
	int	darken[g->lights];
	int obss[g->lights];
	double soft[g->lights];
	t_vector obstructed;
	int	specscal;
	t_colbri tmp;

	ft_bzero(obss, 4 * g->lights);
	init_vector(&tmp.col, 0, 0, 0);
	obsc = 0;
	i = -1;
	while(++i < g->lights)
	{
		iobjn[0] = 0;
		iobjn[1] = g->prim;
		while (++iobjn[0] < g->argc + 1)
		{
			if (iobjn[1] == 0)
				iobjn[1] = (iobjn[1] + 1) % (g->argc + 1);
			if (obj->id != g->obj[iobjn[1]].id || 0)
			{
				t = g->obj[iobjn[1]].hit(co.one, g->li[i], co.two[i], &g->obj[iobjn[1]]);
				if (t.dst < 0.000001)
				{
					i++;
					break;
				}
				if (t.dst < 1)
				{
					if (obj->soft)
					{
						obstructed = sum(scale(t.dst, co.two[i]), co.one);
						soft[i] = dot(norm(diff(obstructed, *g->obj[iobjn[1]].ctr)), norm(co.two[i]));
						soft[i] = tothe2(soft[i], obj->soft);
					}
					obsc++;
					obss[i] = 1;
					break;
				}
			}
			iobjn[1] = (iobjn[1] + 1) % (g->argc + 1);
		}
	}
	i = -1;
	if (obj->spec)
	{
		while (++i < g->lights)
			if (obss[i] == 0)
				do_1_spec(&tmp, cr_spec(cur, co.two, co.three, *obj, i), g);
		specscal = g->lights - obsc;
		if (obsc < g->lights)
		{
			tmp.col = scale(1 / (double)specscal, tmp.col);
			cur->col = tmp.col;
		}
	}
	if (obsc > 0)
	{
		if (obj->soft)
		{
			int briscale;
			briscale = (cur->bri - *g->ambient) / g->lights;
			i = -1;
			while (++i < g->lights)
			{
				darken[i] = (briscale) * soft[i];
				cur->bri = cur->bri - darken[i];
			}
		}
		else
			cur->bri = *g->ambient + ((g->lights - obsc) * (cur->bri - *g->ambient) / (double)g->lights);
	}
}

void	objecthit(t_dstpst *ret, t_3_vecs co, t_object *obj, int objc)
{
	int i;
	int legal_hit;
	t_dstpst t_crt;
	double closest_tmp;
	t_vector ray;

	i = 0;
	legal_hit = 0;
	ray = diff(co.three, co.one);
	while (++i < objc)
	{
		t_crt = obj[i].hit(co.one, co.three, ray, &obj[i]);
		if ((t_crt.dst >= 0.0000001) && (!legal_hit || t_crt.dst < closest_tmp))
		{
			legal_hit = 1;
			closest_tmp = t_crt.dst;
			*ret = t_crt;
			ret->obj.cam_pos = t_crt.pst;
 		}
	}
	if (!legal_hit)
		ret->obj.name = NULL;
}

void	*toimg(void *tcp)
{
	int			j;
	int			i;
 	t_colbri	bright;
	t_global	*g;
	int			jheight;

	g = tcp;
	j = g->core * HEIGHT / CORES - 1;
	jheight = j * HEIGHT;
	while ((++j < (g->core + 1) * HEIGHT / CORES) && (i = -1))
	{
		jheight += HEIGHT; 
		while (++i < WIDTH)
		{
			if (g->hits[j][i]->obj.name != NULL)
			{
				bright = (g->hits[j][i])->obj.
				simple_bright(*g->cam_pos, (g->hits[j][i])->hit, &(g->hits)[j][i]->obj, g);
				g->data_ptr[jheight + i] = color(bright.bri, bright.col);
			}
		}
	}
	return (NULL);
}

void	move_row(int j, int jheight, t_global *g)
{
	int			i;
	t_dstpst	ret;
	t_colbri	bright;

	i = -1;
	while (++i < WIDTH)
	{
		objecthit(&ret, create_3_vecs(*g->cam_pos, NULL, sum(*g->rays[j][i], *g->cam_pos)), g->obj, g->argc + 1);
		g->hits[j][i]->hit = sum(scale(ret.dst, *g->rays[j][i]), *g->cam_pos);
		g->hits[j][i]->obj = ret.obj;
		if (g->hits[j][i]->obj.name != NULL)
		{
			bright = ret.obj.bright(*g->cam_pos, (g->hits[j][i])->hit, &(g->hits)[j][i]->obj, g);
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
	t_dstpst	ret;
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

void	recalc_row(int jheight, int j, t_global *g)
{
	t_vector	ray;
	t_dstpst	ret;
	int			i;
	t_colbri	bright;

	i = -1;
	if (g->core == 0)
		printf("LOADING %d%c\n", (int)((j / (double)(HEIGHT / (double)CORES)) * 100 + 4), '%');
	while (++i < WIDTH)
	{
		init_vector(&ray, i - WIDTH_2, HEIGHT_2 - j, g->ray->z);
		ray = rotate(ray, *g->angle);
		*g->rays[j][i] = ray;
		objecthit(&ret, create_3_vecs(*g->cam_pos, NULL, sum(ray, *g->cam_pos)), g->obj, g->argc + 1);
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
