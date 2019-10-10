/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bright_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 20:37:08 by tpokalch          #+#    #+#             */
/*   Updated: 2019/07/03 20:49:07 by tpokalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_colbri	simple_bright_sphere(t_vector st, t_vector hit,
	t_object *obj, t_global *g)
{
	t_colbri		ret;
	t_vector		reflrayv;
	t_vector		hitli[g->lights];
	t_vector		saveobjcol;

	init_hitli(hitli, hit, g);
	saveobjcol = obj->color;
	if (obj->cam_pos)
	{
		if ((dot(diff(*g->li, *obj->ctr), diff(*g->li, *obj->ctr))
							> obj->rd2) && (ret.bri = *g->ambient))
			ret.col = obj->color;
	}
	else
		init_bri(&ret.bri, hitli, obj->nr, g);
	reflrayv = reflray(st, hit, obj->nr);
	if (obj->re)
		do_re(reflrayv, hit, obj, g);
	ret.col = obj->color;
	if (obj->trans)
		do_trans(create_3_vecs(st, NULL, hit), &ret, *obj, g);
	obstructed(&ret, create_3_vecs(hit, hitli, reflrayv), obj, g);
	obj->color = saveobjcol;
	return (ret);
}

void		do_tile_sphere(t_vector hit, t_object *obj)
{
	t_vector	ctrhit;
	t_vector	proj;
	double		x;
	double		y;
	t_tile		*tile;

	tile = obj->tile;
	ctrhit = diff(hit, *obj->ctr);
	proj = diff(ctrhit, scale(dot(obj->base[1], ctrhit), obj->base[1]));
	proj = norm(proj);
	y = tile[0].h * M_1_PI * acos(dot(obj->nr, obj->base[1]));
	x = tile[0].w2 * M_1_PI * myacos(proj, obj->base[2], obj->base[1]);
	if (round(x) >= tile[0].w2)
		x--;
	obj->color = base255(rgb(*(obj->tile[0].data_ptr +
	obj->tile[0].w * (int)y + (int)x)));
}

void		bri_sph_obj(t_do_spec sp, t_global *g, t_object *obj)
{
	init_hitli(sp.hitli, sp.reflrayv, g);
	obj->nr = scale(1 / (double)obj->rd, diff(sp.reflrayv, *obj->ctr));
	if (obj->cam_pos)
	{
		obj->nr = scale(-1, obj->nr);
		if (len2(diff(*g->li, *obj->ctr)) > obj->rd2)
			sp.ret->bri = *g->ambient;
		else
			init_bri(&sp.ret->bri, sp.hitli, obj->nr, g);
	}
	else
		init_bri(&sp.ret->bri, sp.hitli, obj->nr, g);
}

t_colbri	bright_sphere(t_vector st, t_vector hit, t_object *obj, t_global *g)
{
	t_colbri	ret;
	t_vector	reflrayv;
	t_vector	hitli[g->lights];
	t_vector	saveobjcol;

	g->recursion[obj->id]++;
	bri_sph_obj(cr_spec(&ret, hitli, hit, *obj), g, obj);
	reflrayv = reflray(st, hit, obj->nr);
	if (obj->tile[0].data_ptr)
		do_tile_sphere(hit, obj);
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
