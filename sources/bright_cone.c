/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bright_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:21:36 by nnovikov          #+#    #+#             */
/*   Updated: 2019/10/10 19:21:38 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			inside_cone(t_vector p, t_object obj)
{
	double		axdst;
	double		cirad;
	t_vector	ptoaxproj;
	t_vector	ptoaxperp;
	t_vector	op;

	op = diff(p, *obj.ctr);
	if (dot(op, op) < 0.001)
		return (0);
	axdst = dot(op, obj.base[1]);
	cirad = axdst * obj.rd2;
	ptoaxproj = scale(axdst, obj.base[1]);
	ptoaxperp = diff(op, ptoaxproj);
	return (dot(ptoaxperp, ptoaxperp) - cirad * cirad <= 0);
}

t_colbri	simple_bright_cone(t_vector st, t_vector hit, t_object *obj,
	t_global *g)
{
	t_colbri	ret;
	t_vector	reflrayv;
	t_vector	hitli[g->lights];
	t_vector	saveobjcol;

	init_hitli(hitli, hit, g);
	saveobjcol = obj->color;
	init_bri(&ret.bri, hitli, obj->nr, g);
	if (inside_cone(*g->cam_pos, *obj))
	{
		if (!inside_cone(*g->li, *obj))
			ret.bri = *g->ambient;
	}
	else if (inside_cone(*g->li, *obj))
		ret.bri = *g->ambient;
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

void		do_tile_cone(t_vector ctrhit,
	t_vector hit, t_object *obj)
{
	double		x;
	double		y;
	t_vector	proj;
	t_tile		*objtile;

	objtile = obj->tile;
	proj = diff(ctrhit, scale(dot(obj->base[1], ctrhit), obj->base[1]));
	proj = norm(proj);
	x = objtile[0].w2 * (1 * M_1_PI *
		myacos(proj, obj->base[2], obj->base[1]));
	y = mymod(1 - dot(obj->base[1], diff(hit, *obj->ctr)), objtile[0].h);
	obj->color = base255(rgb(*(obj->tile[0].data_ptr
							+ obj->tile[0].w * (int)y + (int)x)));
}

void		bri_cone_obj(t_do_spec sp, t_global *g, t_object *obj)
{
	t_vector	hit0;

	hit0 = diff(sp.reflrayv, *obj->ctr);
	obj->nr = norm(diff(hit0, scale(dot(hit0, obj->base[1]) *
		(1 + obj->rd2), obj->base[1])));
	init_hitli(sp.hitli, sp.reflrayv, g);
	if (inside_cone(*g->cam_pos, *obj))
	{
		obj->nr = scale(-1, obj->nr);
		if (!inside_cone(*g->li, *obj))
			sp.ret->bri = *g->ambient;
		else
			init_bri(&sp.ret->bri, sp.hitli, obj->nr, g);
	}
	else if (inside_cone(*g->li, *obj))
		sp.ret->bri = *g->ambient;
	else
		init_bri(&sp.ret->bri, sp.hitli, obj->nr, g);
}

t_colbri	bright_cone(t_vector st, t_vector hit, t_object *obj, t_global *g)
{
	t_vector	hit0;
	t_colbri	ret;
	t_vector	hitli[g->lights];
	t_vector	reflrayv;
	t_vector	saveobjcol;

	g->recursion[obj->id]++;
	hit0 = diff(hit, *obj->ctr);
	bri_cone_obj(cr_spec(&ret, hitli, hit, *obj), g, obj);
	if (obj->tile[0].data_ptr)
		do_tile_cone(hit0, hit, obj);
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
