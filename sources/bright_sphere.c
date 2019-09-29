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

t_colbri	simple_bright_sphere(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_colbri    ret;
	t_vector    nrm;
	t_vector    ctrli;
	t_colbri ret2;
	int		retobs;
	t_vector	proj;
	t_vector ctrhit;
	int i;
	t_colbri retorig;
	t_vector reflrayv;
	t_vector hitli[g->lights];

	init_hitli(hitli, hit, g);
	nrm = obj.nr;
	if (obj.cam_pos)
	{
		ctrli = diff(*g->li, *obj.ctr);
		if (dot(ctrli, ctrli) > obj.rd2)
		{
			ret.col = obj.color;
			ret.bri = *g->ambient;
			return (ret);
		}
	}
	init_bri(&retorig.bri, hitli, nrm, g);

	ret.col = obj.color;
	if (obj.spec || obj.re)
		reflrayv = reflray(st, hit, nrm, g);
	if (obj.re)
		do_re(reflrayv, &ret.col, ret.col, hit, nrm, obj, g);
	ret.bri = retorig.bri;
	if (obj.trans)
		do_trans(st, hit, &ret, ret, nrm, obj, g);
	obstructed(&ret, hit, hitli, reflrayv, obj, g);
	if (ret.bri < *g->ambient)
		ret.bri = *g->ambient;
	return (ret);
}


t_vector		do_tile_sphere(t_vector *tileocol, t_vector st, t_vector hit, t_vector nrm, t_object obj, t_global *g)
{
	t_vector ctrhit;
	t_vector proj;
	double x;
	double y;

	ctrhit = diff(hit, *obj.ctr);
	proj = diff(ctrhit, scale(dot(obj.base[1], ctrhit),obj.base[1]));
	proj = norm(proj);
	y = obj.tile[0].h * 1 * M_1_PI * acos(dot(nrm, obj.base[1]));
	x = obj.tile[0].w2 * (1 * M_1_PI * myacos(proj, obj.base[2], obj.base[1], g));
	if (round(x) >= obj.tile[0].w2)
		x--;
	if (g->mip_map)
		*tileocol = mip_col(y, x, dot(diff(hit, *g->cam_pos), diff(hit, *g->cam_pos)), obj, g);
	else
		*tileocol = *(obj.tile[0].vectile + lround(y)* obj.tile[0].w + lround(x));
	return (*tileocol);
}

t_colbri	bright_sphere(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_colbri	ret;
	t_vector	nrm;
	t_vector	ctrli;
	int			retobs;
	t_vector	proj;
	t_vector	ctrhit;
	t_colbri	retorig;
	t_colbri	transo;
	t_colbri	reo;
	t_colbri	tileo;
	t_colbri	speco;
	int			i;
	t_vector	reflrayv;
	t_vector	hitli[g->lights];
	static int rec = 0;

	rec++;
	g->recursion++;
	init_hitli(hitli, hit, g);
	nrm = scale(1 / (double)obj.rd, diff(hit, *obj.ctr));
	if (obj.cam_pos)
	{
		if (!obj.trans)
		{
			ctrli = diff(*g->li, *obj.ctr);
			if (dot(ctrli, ctrli) > obj.rd2)
				ret.bri = *g->ambient;
		}
		nrm = scale(-1, nrm);
	}
	ret.nrm = nrm;
	obj.nr = nrm;
	init_bri(&reo.bri, hitli, nrm, g);
	if (obj.tile[0].data_ptr)
		ret.colself = do_tile_sphere(&reo.col, st, hit, nrm, obj, g);
	else
	{
		ret.colself = obj.color;
		reo.col = obj.color;		
	}
	if (obj.spec || obj.re)
		reflrayv = reflray(st, hit, nrm, g);
	if (obj.re)
		do_re(reflrayv, &reo.col, reo.col, hit, nrm, obj, g);
	if (obj.trans)
		do_trans(st, hit, &ret, reo, nrm, obj, g);
	else
	{
		ret.col = reo.col;
		ret.bri = reo.bri;
	}
	g->recursion = 0;
	return (ret);
}
