/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brights.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 20:37:08 by tpokalch          #+#    #+#             */
/*   Updated: 2019/07/03 20:49:07 by tpokalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_do_spec		cr_spec(t_colbri *ret, t_vector *hitli,	t_vector reflrayv, t_object obj, int i)
{
	t_do_spec spec;

	spec.ret = ret;
	spec.hitli = hitli;
	spec.reflrayv = reflrayv;
	spec.obj = obj;
	spec.i = i;
	return (spec);
}

t_3_vecs		create_3_vecs(t_vector one, t_vector *two, t_vector three)
{
	t_3_vecs vec;

	vec.one = one;
	vec.two = two;
	vec.three = three;
	return (vec);
}

t_colbri		refl(t_vector refl, t_vector hit, t_object obj, t_global *g)
{
	t_dstpst	temp;
	t_objecthit	reflobj;
	t_colbri	ret;

	objecthit(&temp, create_3_vecs(hit, NULL, sum(refl, hit)), g->obj, g->argc + 1);
	reflobj.hit = sum(scale(temp.dst, refl), hit);
	reflobj.obj = temp.obj;
	if (reflobj.obj.name == NULL)
	{
		init_vector(&ret.col, 0, 0, 0);
		ret.bri = 0;
		return (ret);
	}
	ret = reflobj.obj.bright(hit, reflobj.hit, &reflobj.obj, g);
	ret.col = scale(ret.bri / (double)255, ret.col);
	return (ret);
}

void			do_re(t_vector reflrayv, t_vector hit, t_object *obj, t_global *g)
{
	t_colbri reflcolbri;
	t_vector prevcol;

	prevcol = obj->color;
	if (g->recursion[obj->id] < MAX_REC)
	{
		reflcolbri = refl(reflrayv, hit, *obj, g);
		obj->color = sum(scale(1 - obj->re, prevcol), scale(obj->re, reflcolbri.col));
	}
}

t_vector		reflray(t_vector st, t_vector end, t_vector nrm, t_global *g)
{
	t_vector	ray;
	t_vector	refl;
	t_vector	rayx;

	ray = diff(end, st);
	rayx = diff(ray, scale(dot(ray, nrm), nrm));
	refl = diff(scale(2, rayx), ray);
	return (refl);
}

t_colbri		trans(t_vector st, t_vector hit, t_global *g)
{
	t_dstpst	temp;
	t_colbri	ret;
	t_objecthit	transobj;
	t_vector	ray;

	ray = diff(hit, st);
	objecthit(&temp, create_3_vecs(hit, NULL, sum(ray, hit)), g->obj, g->argc + 1);
	transobj.hit = sum(scale(temp.dst, ray), hit);
	transobj.obj = temp.obj;
	if (transobj.obj.name == NULL)
	{
		init_vector(&ret.col, 0, 0, 0);
		ret.bri = *g->ambient;
		return (ret);
	}
	ret = transobj.obj.bright(hit, transobj.hit, &transobj.obj, g);
	return (ret);
}

void			do_trans(t_3_vecs co, t_colbri *ret, t_object obj, t_global *g)
{
	t_colbri transo;
	int		origbri;

	origbri = ret->bri;
	if (g->recursion[obj.id] > MAX_REC)
		return ;
	transo = trans(co.one, co.three, g);
	transo.col = sum(scale(1 - obj.trans, ret->col),
		scale(obj.trans, transo.col));
	ret->col = transo.col;
	ret->bri = transo.bri * obj.trans + origbri * (1 - obj.trans);
}

void			init_hitli(t_vector *hitli, t_vector hit, t_global *g)
{
	int i;

	i = 0;
	while (i < g->lights)
	{
		hitli[i] = diff(g->li[i], hit);
		i++;
	}
}

void			init_bri(int *bri, t_vector *hitli, t_vector nrm, t_global *g)
{
	int i;

	i = 0;
	*bri = 0;
	while (i < g->lights)
	{
		*bri += fmax(round(255 * dot(norm(hitli[i]), nrm)), *g->ambient);
		i++;
	}
	*bri = round(*bri / (double)g->lights);
}

int				inside_cone(t_vector p, t_object obj, t_global *g)
{
	double		axdst;
	double		cirad;
	t_vector	ptoaxproj;
	t_vector	ptoaxperp;
	t_vector	op;
	t_global	*a;

	a = g;
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
	if (inside_cone(*g->cam_pos, *obj, g))
	{
		if (!inside_cone(*g->li, *obj, g))
			ret.bri = *g->ambient;
		else
			init_bri(&ret.bri, hitli, obj->nr, g);
	}
	else if (inside_cone(*g->li, *obj, g))
		ret.bri = *g->ambient;
	else
		init_bri(&ret.bri, hitli, obj->nr, g);
	if (obj->spec || obj->re)
		reflrayv = reflray(st, hit, obj->nr, g);
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
	t_vector hit, t_object *obj, t_global *g)
{
	double		x;
	double		y;
	t_vector	proj;
	t_tile		*objtile;

	objtile = obj->tile;
	proj = diff(ctrhit, scale(dot(obj->base[1], ctrhit), obj->base[1]));
	proj = norm(proj);
	x = objtile[0].w2 * (1 * M_1_PI *
		myacos(proj, obj->base[2], obj->base[1], g));
	y = mymod(1 - dot(obj->base[1], diff(hit, *obj->ctr)), objtile[0].h);
	obj->color = base255(rgb(*(obj->tile[0].data_ptr + obj->tile[0].w * (int)y + (int)x)));
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
	obj->nr = norm(diff(hit0, scale(dot(hit0, obj->base[1]) *
		(1 + obj->rd2), obj->base[1])));
	init_hitli(hitli, hit, g);
	if (inside_cone(*g->cam_pos, *obj, g))
	{
		obj->nr = scale(-1, obj->nr);
		if (!inside_cone(*g->li, *obj, g))
			ret.bri = *g->ambient;
		else
			init_bri(&ret.bri, hitli, obj->nr, g);
	}
	else if (inside_cone(*g->li, *obj, g))
		ret.bri = *g->ambient;
	else
		init_bri(&ret.bri, hitli, obj->nr, g);
	if (obj->tile[0].data_ptr)
		do_tile_cone(hit0, hit, obj, g);
	saveobjcol = obj->color;
	if (obj->re || obj->spec)
		reflrayv = reflray(st, hit, obj->nr, g);
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
	if (obj->spec || obj->re)
		reflrayv = reflray(st, hit, obj->nr, g);
	if (obj->re)
		do_re(reflrayv, hit, obj, g);
	ret.col = obj->color;	
	if (obj->trans)
		do_trans(create_3_vecs(st, NULL, hit), &ret, *obj, g);
	obj->color = saveobjcol;
	obstructed(&ret, create_3_vecs(hit, hitli, reflrayv), obj, g);
	return (ret);
}

void	do_tile_cyl(t_vector hit, t_vector ctrhit,
	 t_object *obj, t_global *g)
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
		* myacos(proj, obj->base[0], obj->base[1], g);
	y = myintmod(xdst, obj->tile[0].h);
	obj->color = base255(rgb(*(obj->tile[0].data_ptr + obj->tile[0].w * (int)y + (int)x)));
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
	obj->nr = scale(dot(ctrhit, obj->base[1]), obj->base[1]);
	obj->nr = norm(diff(ctrhit, obj->nr));
	init_hitli(hitli, hit, g);
	if (obj->cam_pos)
	{
		obj->nr = scale(-1, obj->nr);
		if (obj->hit(*g->cam_pos, *g->li,
			diff(*g->li, *g->cam_pos), obj).dst < 1)
			ret.bri = *g->ambient;
		else
			init_bri(&ret.bri, hitli, obj->nr, g);
	}
	else
		init_bri(&ret.bri, hitli, obj->nr, g);
	if (obj->tile[0].data_ptr)
		do_tile_cyl(hit, ctrhit, obj, g);
	saveobjcol = obj->color;
	if (obj->spec || obj->re)
		reflrayv = reflray(st, hit, obj->nr, g);
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

void		do_1_spec(t_colbri *tmp, t_do_spec sp, t_global *g)
{
	g->cosa[sp.i] = dot(norm(sp.hitli[sp.i]), norm(sp.reflrayv));
	if (g->cosa[sp.i] > 0)
	{
		g->cosa[sp.i] = tothe2(g->cosa[sp.i], sp.obj.spec);
		tmp->col = sum(tmp->col, sum(scale(g->cosa[sp.i], g->white),
					scale((1 - g->cosa[sp.i]), sp.ret->col)));
	}
	else
		tmp->col = sum(tmp->col, sp.ret->col);
}

void		do_spec(t_colbri *ret, t_3_vecs co, t_object obj, t_global *g)
{
	int			i;
	t_colbri	tmp;
	t_vector	hitli[g->lights];

	i = -1;
	while (++i < g->lights)
		hitli[i] = diff(g->li[i], co.one);
	init_vector(&tmp.col, 0, 0, 0);
	i = -1;
	while (++i < g->lights)
		do_1_spec(&tmp, cr_spec(ret, hitli, co.three, obj, i), g);
	tmp.col = scale(1 / (double)g->lights, tmp.col);
	ret->col = tmp.col;
}



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
		reflrayv = reflray(st, hit, obj->base[1], g);
	if (obj->re)
		do_re(reflrayv, hit, obj, g);
	ret.bri = retorig.bri;
	if (obj->trans)
		do_trans(create_3_vecs(st, NULL, hit), &ret, *obj, g);
	if (obj->spec)
		do_spec(&ret, create_3_vecs(hit, NULL, reflrayv), *obj, g);
	return (ret);
}

void			do_tile_tri(t_vector *retcol, t_object *obj, t_vector hit)
{
	t_vector	v;
	double		x;
	double		y;

	v = diff(hit, *obj->ctr);
	x = mymod(v.x, obj->tile[0].w);
	y = mymod(v.z, obj->tile[0].h);
	obj->color = base255(rgb(*(obj->tile[0].data_ptr + obj->tile[0].w * (int)y + (int)x)));
}

t_colbri		bright_tri(t_vector st, t_vector hit, t_object *obj, t_global *g)
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
		reflrayv = reflray(st, hit, obj->base[1], g);
	if (obj->tile[0].data_ptr)
		do_tile_tri(&ret.col, obj, hit);
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
