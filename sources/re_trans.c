/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_trans.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:54:20 by nnovikov          #+#    #+#             */
/*   Updated: 2019/10/10 20:54:22 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_colbri		refl(t_vector refl, t_vector hit, t_global *g)
{
	t_dstpst	temp;
	t_objecthit	reflobj;
	t_colbri	ret;

	objecthit(&temp, create_3_vecs(hit, NULL, sum(refl, hit)),
										g->obj, g->argc + 1);
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

void			do_re(t_vector reflrayv, t_vector hit, t_object *obj,
														t_global *g)
{
	t_colbri reflcolbri;
	t_vector prevcol;

	prevcol = obj->color;
	if (g->recursion[obj->id] < MAX_REC)
	{
		reflcolbri = refl(reflrayv, hit, g);
		obj->color = sum(scale(1 - obj->re, prevcol),
						scale(obj->re, reflcolbri.col));
	}
}

t_vector		reflray(t_vector st, t_vector end, t_vector nrm)
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
	objecthit(&temp, create_3_vecs(hit, NULL, sum(ray, hit)),
											g->obj, g->argc + 1);
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
	t_colbri	transo;
	int			origbri;

	origbri = ret->bri;
	if (g->recursion[obj.id] > MAX_REC)
		return ;
	transo = trans(co.one, co.three, g);
	transo.col = sum(scale(1 - obj.trans, ret->col),
		scale(obj.trans, transo.col));
	ret->col = transo.col;
	ret->bri = transo.bri * obj.trans + origbri * (1 - obj.trans);
}
