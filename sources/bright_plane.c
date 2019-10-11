/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bright_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 20:38:38 by vkarpova          #+#    #+#             */
/*   Updated: 2019/10/11 20:38:39 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_colbri		simple_bright_plane(t_vector st, t_vector hit,
	t_object *obj, t_global *g)
{
	t_colbri	ret;
	t_vector	reflrayv;
	t_vector	hitli[g->lights];
	t_vector	saveobjcol;

	saveobjcol = obj->color;
	init_hitli(hitli, hit, g);
	init_bri(&ret.bri, hitli, obj->base[1], g);
	reflrayv = reflray(st, hit, obj->base[1]);
	if (obj->re)
		do_re(reflrayv, hit, obj, g);
	ret.col = obj->color;
	if (obj->trans)
		do_trans(create_3_vecs(st, NULL, hit), &ret, *obj, g);
	obj->nr = obj->base[1];
	obstructed(&ret, create_3_vecs(hit, hitli, reflrayv), obj, g);
	obj->color = saveobjcol;
	return (ret);
}

void			do_tile_plane(t_colbri *retorig, t_vector hit,
	t_object *obj)
{
	t_vector	ctrhit;
	int			x;
	int			y;

	ctrhit = diff(hit, *obj->ctr);
	x = mymod(ctrhit.x, obj->tile[0].w);
	y = mymod(ctrhit.z, obj->tile[0].h);
	retorig->col = base255(rgb(*(obj->tile[0].data_ptr +
	(int)y * obj->tile[0].w + (int)x)));
	obj->color = retorig->col;
}

void			bri_pl_obj(t_do_spec sp, t_global *g, t_object *obj)
{
	init_hitli(sp.hitli, sp.reflrayv, g);
	if (obj->cam_pos)
		obj->base[1] = scale(-1, obj->base[1]);
	init_bri(&sp.ret->bri, sp.hitli, obj->base[1], g);
}

t_colbri		bright_plane(t_vector st, t_vector hit,
	t_object *obj, t_global *g)
{
	t_colbri	ret;
	t_vector	reflrayv;
	t_vector	hitli[g->lights];
	t_vector	saveobjcol;

	g->recursion[obj->id]++;
	bri_pl_obj(cr_spec(&ret, hitli, hit, *obj), g, obj);
	reflrayv = reflray(st, hit, obj->base[1]);
	if (obj->tile[0].data_ptr)
		do_tile_plane(&ret, hit, obj);
	else if (lround(fabs(hit.x) / (double)80) % 2
		== lround(fabs(hit.z) / (double)80) % 2)
		init_vector(&obj->color, 1, 0, 0.5);
	saveobjcol = obj->color;
	if (obj->re)
		do_re(reflrayv, hit, obj, g);
	ret.col = obj->color;
	if (obj->trans)
		do_trans(create_3_vecs(st, NULL, hit), &ret, *obj, g);
	obj->color = saveobjcol;
	obstructed(&ret, create_3_vecs(hit, hitli, reflrayv), obj, g);
	g->recursion[obj->id] = 0;
	return (ret);
}
