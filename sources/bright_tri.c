/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bright_tri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:22:34 by nnovikov          #+#    #+#             */
/*   Updated: 2019/10/10 19:22:37 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_colbri		simple_bright_tri(t_vector st, t_vector hit,
	t_object *obj, t_global *g)
{
	t_colbri	ret;
	t_vector	hitli[g->lights];
	t_vector	reflrayv;
	t_colbri	retorig;

	init_hitli(hitli, hit, g);
	if (0 && dot(diff(hit, st), obj->base[1]) > 0)
	{
		obj->base[1].x = -obj->base[1].x;
		obj->base[1].y = -obj->base[1].y;
		obj->base[1].z = -obj->base[1].z;
	}
	init_bri(&retorig.bri, hitli, obj->base[1], g);
	ret.col = obj->color;
	ret.bri = retorig.bri;
	if (obj->spec || obj->re)
		reflrayv = reflray(st, hit, obj->base[1]);
	if (obj->re)
		do_re(reflrayv, hit, obj, g);
	ret.bri = retorig.bri;
	if (obj->trans)
		do_trans(create_3_vecs(st, NULL, hit), &ret, *obj, g);
	if (obj->spec)
		do_spec(&ret, create_3_vecs(hit, NULL, reflrayv), *obj, g);
	return (ret);
}

void			do_tile_tri(t_object *obj, t_vector hit)
{
	t_vector	v;
	double		x;
	double		y;

	v = diff(hit, *obj->ctr);
	x = mymod(v.x, obj->tile[0].w);
	y = mymod(v.z, obj->tile[0].h);
	obj->color = base255(rgb(*(obj->tile[0].data_ptr +
					obj->tile[0].w * (int)y + (int)x)));
}

t_colbri		bright_tri(t_vector st, t_vector hit,
							t_object *obj, t_global *g)
{
	t_colbri	ret;
	t_vector	hitli[g->lights];
	t_vector	reflrayv;
	t_colbri	retorig;
	t_vector	saveobjcol;

	init_hitli(hitli, hit, g);
	if (dot(diff(hit, *g->cam_pos), obj->base[1]) > 0)
		obj->base[1] = scale(-1, obj->base[1]);
	init_bri(&retorig.bri, hitli, obj->base[1], g);
	if (obj->re || obj->spec)
		reflrayv = reflray(st, hit, obj->base[1]);
	if (obj->tile[0].data_ptr)
		do_tile_tri(obj, hit);
	saveobjcol = obj->color;
	if (obj->re)
		do_re(reflrayv, hit, obj, g);
	ret.col = obj->color;
	if (obj->trans)
		do_trans(create_3_vecs(st, NULL, hit), &ret, *obj, g);
	ret.bri = retorig.bri;
	if (obj->spec)
		do_spec(&ret, create_3_vecs(hit, NULL, reflrayv), *obj, g);
	obj->color = saveobjcol;
	return (ret);
}
