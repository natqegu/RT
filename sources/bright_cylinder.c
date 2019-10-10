/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bright_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:21:50 by nnovikov          #+#    #+#             */
/*   Updated: 2019/10/10 19:21:52 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_colbri	simple_bright_cylinder(t_vector st, t_vector hit,
	t_object *obj, t_global *g)
{
	t_colbri	ret;
	t_vector	hitli[g->lights];
	t_vector	reflrayv;
	t_vector	saveobjcol;

	init_hitli(hitli, hit, g);
	saveobjcol = obj->color;
	if (obj->cam_pos)
	{
		if (obj->hit(*g->cam_pos, *g->li,
			diff(*g->li, *g->cam_pos), obj).dst < 1)
			ret.bri = *g->ambient;
	}
	else
		init_bri(&ret.bri, hitli, obj->nr, g);
	reflrayv = reflray(st, hit, obj->nr);
	if (obj->re)
		do_re(reflrayv, hit, obj, g);
	ret.col = obj->color;
	if (obj->trans)
		do_trans(create_3_vecs(st, NULL, hit), &ret, *obj, g);
	obj->color = saveobjcol;
	obstructed(&ret, create_3_vecs(hit, hitli, reflrayv), obj, g);
	return (ret);
}

void		do_tile_cyl(t_vector hit, t_vector ctrhit,
						t_object *obj)
{
	double		x;
	double		y;
	t_vector	proj;
	double		xdst;

	proj = diff(ctrhit, scale(dot(obj->base[1], ctrhit), obj->base[1]));
	proj = norm(proj);
	x = obj->tile[0].w2
	* (1 - (1 - 2 * (det(proj, obj->base[0]) < 0))
	* M_1_PI * acos(dot(proj, obj->base[0])));
	xdst = dot(obj->base[1], diff(hit, *obj->ctr));
	x = obj->tile[0].w2 * M_1_PI
		* myacos(proj, obj->base[0], obj->base[1]);
	y = myintmod(xdst, obj->tile[0].h);
	obj->color = base255(rgb(*(obj->tile[0].data_ptr
					+ obj->tile[0].w * (int)y + (int)x)));
}

void		bri_cyl_obj(t_do_spec sp, t_global *g, t_object *obj)
{
	t_vector	ctrhit;

	ctrhit = diff(sp.reflrayv, *obj->ctr);
	obj->nr = scale(dot(ctrhit, obj->base[1]), obj->base[1]);
	obj->nr = norm(diff(ctrhit, obj->nr));
	init_hitli(sp.hitli, sp.reflrayv, g);
	if (obj->cam_pos)
	{
		obj->nr = scale(-1, obj->nr);
		if (obj->hit(*g->cam_pos, *g->li,
			diff(*g->li, *g->cam_pos), obj).dst < 1)
			sp.ret->bri = *g->ambient;
		else
			init_bri(&sp.ret->bri, sp.hitli, obj->nr, g);
	}
	else
		init_bri(&sp.ret->bri, sp.hitli, obj->nr, g);
}

t_colbri	bright_cylinder(t_vector st, t_vector hit,
			t_object *obj, t_global *g)
{
	t_vector	ctrhit;
	t_colbri	ret;
	t_vector	hitli[g->lights];
	t_vector	reflrayv;
	t_vector	saveobjcol;

	g->recursion[obj->id]++;
	ctrhit = diff(hit, *obj->ctr);
	bri_cyl_obj(cr_spec(&ret, hitli, hit, *obj), g, obj);
	if (obj->tile[0].data_ptr)
		do_tile_cyl(hit, ctrhit, obj);
	saveobjcol = obj->color;
	reflrayv = reflray(st, hit, obj->nr);
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
