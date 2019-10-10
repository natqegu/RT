/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 20:10:51 by tpokalch          #+#    #+#             */
/*   Updated: 2019/10/10 19:22:55 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	if_obj_spec(t_global *g, t_object *obj, t_hunia hu, int *obss)
{
	t_colbri	tmp;
	int			i;

	init_vector(&tmp.col, 0, 0, 0);
	i = -1;
	if (obj->spec)
	{
		while (++i < g->lights)
		{
			if (obss[i] == 0)
				do_1_spec(&tmp, cr_spec(hu.cur, hu.co.two, hu.co.three,
															*obj), g, i);
		}
		if (hu.o < g->lights)
		{
			tmp.col = scale(1 / (double)(g->lights - hu.o), tmp.col);
			hu.cur->col = tmp.col;
		}
	}
}

void	if_io_2(t_global *g, t_object *obj, double *soft, t_hunia hu)
{
	int i;
	int	darken[g->lights];

	i = -1;
	if (hu.o > 0)
	{
		if (obj->soft)
		{
			while (++i < g->lights)
			{
				darken[i] = ((hu.cur->bri - *g->ambient) / g->lights) * soft[i];
				hu.cur->bri = hu.cur->bri - darken[i];
			}
		}
		else
			hu.cur->bri = *g->ambient + ((g->lights - hu.o) * (hu.cur->bri -
										*g->ambient) / (double)g->lights);
	}
}

int		if_obj_id(t_3_vecs co, t_object *obj, t_global *g, t_masi m)
{
	t_dstpst	t;

	if (obj->id != g->obj[m.io[1]].id || 0)
	{
		t = g->obj[m.io[1]].hit(co.one, g->li[m.io[3]], co.two[m.io[3]],
													&g->obj[m.io[1]]);
		if (t.dst < 0.000001)
		{
			m.io[3]++;
			return (0);
		}
		if (t.dst < 1)
		{
			if (obj->soft)
			{
				m.s[m.io[3]] = dot(norm(diff(sum(scale(t.dst, co.two[m.io[3]]),
					co.one), *g->obj[m.io[1]].ctr)), norm(co.two[m.io[3]]));
				m.s[m.io[3]] = tothe2(m.s[m.io[3]], obj->soft);
			}
			m.io[2]++;
			m.obss[m.io[3]] = 1;
			return (0);
		}
	}
	return (1);
}

void	obstructed(t_colbri *cur, t_3_vecs co, t_object *obj, t_global *g)
{
	int			obss[g->lights];
	double		soft[g->lights];
	int			io[4];

	ft_bzero(obss, 4 * g->lights);
	io[2] = 0;
	io[3] = -1;
	while (++io[3] < g->lights)
	{
		io[0] = 0;
		io[1] = g->prim;
		while (++io[0] < g->argc + 1)
		{
			if (io[1] == 0)
				io[1] = (io[1] + 1) % (g->argc + 1);
			if (!if_obj_id(co, obj, g, cr_masi(soft, obss, io)))
				break ;
			io[1] = (io[1] + 1) % (g->argc + 1);
		}
	}
	if_obj_spec(g, obj, cr_hu(io[2], cur, co), obss);
	if_io_2(g, obj, soft, cr_hu(io[2], cur, co));
}

void	objecthit(t_dstpst *ret, t_3_vecs co, t_object *obj, int objc)
{
	int			i;
	int			legal_hit;
	t_dstpst	t_crt;
	double		closest_tmp;
	t_vector	ray;

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
