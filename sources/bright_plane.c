/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bright_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 20:37:08 by tpokalch          #+#    #+#             */
/*   Updated: 2019/07/03 20:49:07 by tpokalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_colbri	simple_bright_plane(t_vector st, t_vector hit, t_object obj,
															t_global *g)
{
	t_colbri	ret;
	t_vector	reflrayv;
	t_vector	hitli[g->lights];

	init_hitli(hitli, hit, g);
	if (obj.cam_pos)
	{
		obj.base[1].x = -obj.base[1].x;
		obj.base[1].y = -obj.base[1].y;
		obj.base[1].z = -obj.base[1].z;
	}
	init_bri(&ret.bri, hitli, obj.base[1], g);
	ret.col = obj.color;
	if (obj.spec || obj.re)
		reflrayv = reflray(st, hit, obj.base[1], g);
	if (obj.re)
		do_re(reflrayv, &ret.col, ret.col, hit, obj.base[1], obj, g);
	obj.nr = obj.base[1];
	obstructed(&ret, hit, hitli, reflrayv, obj, g);
	if (ret.bri < *g->ambient)
	{
		ret.bri = *g->ambient;
		return (ret);
	}
	return (ret);
}

t_colbri	*tile_plane(t_colbri *retorig, t_vector hit, t_object obj,
														t_colbri *ret)
{
	t_vector	v;
	double		x;
	double		y;
	t_vector	colself;

	if (obj.tile[0].data_ptr)
	{
		v = diff(hit, *obj.ctr);
		x = mymod(v.x, obj.tile[0].w);
		y = mymod(v.z, obj.tile[0].h);
		retorig->col = base(rgb(*(obj.tile[0].data_ptr +
			lround(y) * obj.tile[0].w + lround(x))));
		ret->colself = retorig->col;
	}
	else
	{
		if (lround(fabs(hit.x) / 80.0) % 2 ==
				lround(fabs(hit.z) / 80.0) % 2)
			init_vector(&retorig->col, 1, 0, 0.5);
		else
			retorig->col = obj.color;
		ret->colself = retorig->col;
		colself = retorig->col;
	}
	return (ret);
}

t_colbri	bright_plane(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_colbri	ret;
	t_colbri	retorig;
	t_vector	reflrayv;
	t_vector	hitli[g->lights];

	g->recursion++;
	init_hitli(hitli, hit, g);
	if (obj.cam_pos)
	{
		obj.base[1].x = -obj.base[1].x;
		obj.base[1].y = -obj.base[1].y;
		obj.base[1].z = -obj.base[1].z;
	}
	init_bri(&retorig.bri, hitli, obj.base[1], g);
	ret = *tile_plane(&retorig, hit, obj, &ret);
	if (obj.spec || obj.re)
		reflrayv = reflray(st, hit, obj.base[1], g);
	if (obj.re)
		do_re(reflrayv, &ret.col, retorig.col, hit, obj.base[1], obj, g);
	else
		ret.col = retorig.col;
	ret.bri = retorig.bri;
	obstructed(&ret, hit, hitli, reflrayv, obj, g);
	g->recursion = 0;
	return (ret);
}
