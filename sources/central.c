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

#include "../includes/rt.h"

void	obstructed(t_colbri *cur, t_vector hit, t_vector *hitli, t_vector reflrayv, /*t_vector nrm,*/ t_object obj, t_global *g)
{
	int i;
	t_vector nrm;
	int	iobjn[2];
	t_dstpst	t;
	t_vector ray;
	int	obsc;
	t_colbri tmp;
	int obss[g->lights];
	int	specscal;
	double soft[g->lights];
	t_vector obstructed;

	ft_bzero(obss, 4 * g->lights);
	init_vector(&tmp.col, 0, 0, 0);
	obsc = 0;
	i = 0;
	obj.nr = nrm;
	while (i < g->lights)
	{
		ray = hitli[i];
		iobjn[0] = 0;
		iobjn[1] = g->prim;
		while (++iobjn[0] < g->argc + 1)
		{
			if (iobjn[1] == 0)
				iobjn[1] = (iobjn[1] + 1) % (g->argc + 1);
			if (obj.id != g->obj[iobjn[1]].id || 0)
			{
				t = g->obj[iobjn[1]].hit(hit, g->li[i], ray, g->obj[iobjn[1]], g);
				if (t.dst < 0.000001)
				{
					i++;
					break;
				}
				if (t.dst < 1)
				{
					if (obj.soft)
					{
						obstructed = sum(scale(t.dst, ray), hit);
						soft[i] = dot(norm(diff(obstructed, *g->obj[iobjn[1]].ctr)), norm(ray));
						soft[i] = tothe2(soft[i], obj.soft);
					}
					g->prim = iobjn[1];
					obsc++;
					obss[i] = 1;
					break;
				}
			}
			iobjn[1] = (iobjn[1] + 1) % (g->argc + 1);
		}
		i++;
	}
	i = -1;
	if (obj.spec)
	{
		while (++i < g->lights)
		{
			if (obss[i] == 0)
				do_1_spec(&tmp, cur, hit, hitli, nrm, reflrayv, obj, i, g);
		}
		specscal = g->lights - obsc;
		if (obsc < g->lights)
		{
			tmp.col = scale(1 / (double)specscal, tmp.col);
			cur->col = tmp.col;
		}
	}
	if (obsc > 0)
	{	
		if (obj.soft)
			cur->bri = fmax(*g->ambient, cur->bri * (1 - soft[0])) + ((g->lights - obsc) * (cur->bri - *g->ambient) / (double)g->lights);
		else
			cur->bri = *g->ambient + ((g->lights - obsc) * (cur->bri - *g->ambient) / (double)g->lights);
	}
}

void	objecthit(t_dstpst *ret, t_vector st, t_vector end, t_object *obj, int objc, t_global *g)
{
	int i;
	int legal_hit;
	t_dstpst t_crt;
	double closest_tmp;
	t_vector ray;

	i = 0;
	legal_hit = 0;
	ray = diff(end, st);
	while (++i < objc)
	{
		t_crt = obj[i].hit(st, end, ray, obj[i], g);
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

int		empty_line(int current, int *line_taken)
{
	int i;

	i = current;
	while (line_taken[i])
		i++;
	if (i >= STRIPS)
		return (-1);
	return (i);
}

void		*toimg(void *tcp)
{
	int j;
	int	i;
 	t_colbri	bright;
	t_global *g;
	int end;
	int jheight;

	g = tcp;
	end = (g->core + 1) * HEIGHT / CORES;
	j = g->core * HEIGHT / CORES - 1;
	jheight = j * HEIGHT;
	while ((++j < end) && (i = -1))
	{
		jheight += HEIGHT; 
		while (++i < WIDTH)
		{
			init_vector(g->ray, i - WIDTH_2, HEIGHT_2 - j, g->ray->z);
			if (g->hits[j][i]->obj.name != NULL)
			{
				bright = (g->hits[j][i])->obj.
				simple_bright(*g->cam_pos, (g->hits[j][i])->hit, (g->hits)[j][i]->obj, g);
				g->data_ptr[jheight + i] = color(bright.bri, bright.col);
			}
		}
	}
	pthread_exit(0);
}

void		*move(void *p)
{
	t_global *g;
	int i;
	int j;
	int end;
	t_colbri bright;
	t_dstpst ret;
	int	jheight;

	g = (t_global *)p;
	end = (g->core + 1) * HEIGHT / CORES;
	j = g->core * HEIGHT / CORES - 1;
	jheight = j * HEIGHT;
	while (++j < end && (i = -1))
	{
		jheight += HEIGHT;
		while (++i < WIDTH)
		{
			objecthit(&ret, *g->cam_pos,
			sum(*g->rays[j][i], *g->cam_pos), g->obj, g->argc + 1, g);
			g->hits[j][i]->hit = sum(scale(ret.dst, *g->rays[j][i]), *g->cam_pos);
			g->hits[j][i]->obj = ret.obj;
			if (g->hits[j][i]->obj.name != NULL)
			{
				bright = (g->hits[j][i])->obj.bright(*g->cam_pos, (g->hits[j][i])->hit, (g->hits)[j][i]->obj, g);
				g->hits[j][i]->obj.bright = g->hits[j][i]->obj.simple_bright;
				g->hits[j][i]->obj.color = bright.colself;
				g->hits[j][i]->obj.nr = bright.nrm;
				g->data_ptr[jheight + i] = color(bright.bri, bright.col);
			}
			else
				g->data_ptr[jheight + i] = 0;			
		}
	}
	pthread_exit(0);
}

void		*recalc(void *p)
{
	t_global *g;
	int i;
	int j;
	t_vector ray;
	int end;
	t_colbri bright;
	t_dstpst ret;
	int jheight;
	
	g = (t_global *)p;

	end = (g->core + 1) * HEIGHT / CORES;
	j = g->core * HEIGHT / CORES - 1;
	jheight = j * HEIGHT;
	while (++j < end && (i = -1))
	{
		// if (g->core == 0)
			// printf("LOADING = %f%s\n", j / (double)(HEIGHT / (double)CORES) + 1 - g->core, "\%");
		jheight += HEIGHT;
		while (++i < WIDTH)
		{
			init_vector(g->ray, i - WIDTH_2, HEIGHT_2 - j, g->ray->z);
			init_vector(&ray, i - WIDTH_2, HEIGHT_2 - j, g->ray->z);
			ray = rotate(ray, *g->angle);
			*g->rays[j][i] = ray;
			objecthit(&ret, *g->cam_pos, sum(ray, *g->cam_pos), g->obj, g->argc + 1, g);
			g->hits[j][i]->obj = ret.obj;
			g->hits[j][i]->hit = sum(scale(ret.dst, *g->rays[j][i]), *g->cam_pos);
			if (g->hits[j][i]->obj.name != NULL)
			{
				bright = g->hits[j][i]->obj.
				bright(*g->cam_pos, g->hits[j][i]->hit, (g->hits)[j][i]->obj, g);
				g->hits[j][i]->obj.color = bright.colself;
				g->hits[j][i]->obj.nr = bright.nrm;
				g->data_ptr[jheight + i] = color(bright.bri, bright.col);
			}
			else
				g->data_ptr[jheight + i] = 0;
		}
	}
	pthread_exit(0);
}