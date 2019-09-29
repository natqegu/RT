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

#include "../includes/rt.h"

t_colbri		refl(t_vector refl, t_vector hit, t_vector nrm, t_object obj, t_global *g)
{
	t_dstpst temp;
	t_objecthit reflobj;
	t_colbri ret;

	objecthit(&temp, hit, sum(refl, hit), g->obj, g->argc + 1, g);
	reflobj.hit = sum(scale(temp.dst, refl), hit);
	reflobj.obj = temp.obj;
	if (reflobj.obj.name == NULL)
	{
		init_vector(&ret.col, 0, 0, 0);
		ret.bri = 0;
	}
	ret = reflobj.obj.bright(hit, reflobj.hit, reflobj.obj, g);
	ret.col = scale(ret.bri / (double)255, ret.col);
	return (ret);
}

void		do_re(t_vector reflrayv, t_vector *reocol, t_vector tileocol, t_vector hit, t_vector nrm, t_object obj, t_global *g)
{
		t_vector reflrayv1;
		t_colbri reflcolbri;

		reflrayv1 = reflrayv;
		if (g->recursion < MAX_REC)
		{
			reflcolbri = refl(reflrayv1, hit, nrm, obj, g);
			*reocol = reflcolbri.col;
			*reocol = sum(scale(1 - obj.re, tileocol), scale(obj.re, base255(scale(reflcolbri.bri, reflcolbri.col))));
		}
		else
			*reocol = tileocol;
}

t_colbri		trans(t_vector st, t_vector hit, t_vector nrm, t_object obj, t_global *g)
{
	t_dstpst temp;
	t_colbri ret;
	t_objecthit	transobj;
	t_vector ray;
	t_vector	end;
	t_vector	start;

	g->recursion++;
	ray = diff(hit, st);
	objecthit(&temp, hit, sum(ray, hit), g->obj, g->argc + 1, g);
	transobj.hit = sum(scale(temp.dst, ray), hit);
	transobj.obj = temp.obj;
	transobj.obj.cam_pos = 0;
	if (transobj.obj.name == NULL)
	{
		init_vector(&ret.col, 0, 0, 0);
		ret.bri = *g->ambient;
		return (ret);
	}
	ret = transobj.obj.bright(hit, transobj.hit, transobj.obj, g);
	return (ret);
}

t_vector		reflray(t_vector st, t_vector end, t_vector nrm, t_global *g)
{
	t_vector ray;
	t_vector refl;
	t_vector rayx;

	ray = diff(end, st);
	rayx = diff(ray, scale(dot(ray, nrm), nrm));
	refl = diff(scale(2, rayx), ray);
	return (refl);
}

void		do_trans(t_vector st, t_vector hit, t_colbri *ret, t_colbri reo, t_vector nrm, t_object obj, t_global *g)
{
		t_colbri transo;

		transo = trans(st, hit, nrm, obj, g);
		transo.col = base255(scale(transo.bri, transo.col));
		transo.col = sum(scale(1 - obj.trans, reo.col), scale(obj.trans, transo.col));
		ret->col = transo.col;
		ret->bri = transo.bri;
}

t_vector		mip_col(double x, double y, double dst2, t_object obj, t_global *g)
{
	int		tilelow;
	int		tilehi;
	t_tile		*ti;
	double		newres;
	double		tilen;
	t_vector		ret;
	double weight[2];

	newres = g->ray->z / (double)sqrt(dst2) * obj.tile[0].w;
	ti = obj.tile;

	tilen = log2(obj.tile[0].w / newres) + 13;
	tilelow = floor(tilen);
	tilehi = ceil(tilen);
	weight[0] = 1 - (tilen - tilelow);
	weight[1] = 1 - (tilehi - tilen);
	if (tilehi > ti[0].mipq || tilelow > ti[0].mipq)
	{
		tilen = ti[0].mipq;
		tilehi = ti[0].mipq;
		tilelow = ti[0].mipq;
	}
	if (tilehi < 0 || tilelow < 0)
	{
		tilen = 0;
		tilehi = 0;
		tilelow = 0;
	}
	if (tilehi > 6 || tilelow > 6)
	{
		tilehi = 6;
		tilen = 6;
		weight[0] = 1;
		weight[1] = 0;
	}
	if (tilehi < 0 || tilelow < 0)
	{
		tilehi = 0;
		tilen = 0;
		weight[1] = 1;
		weight[0] = 0;
	}
	tilen = floor(tilen);
	if (tilen < 0)
		tilen = 0;
	else if (tilen > ti[0].mipq)
		tilen = ti[0].mipq;

	t_vector col[4];
	t_vector colhi[4];
	double	colweight[4];
	double colhiweight[4];
	
	col[0] = base255(rgb(*(ti[tilelow].data_ptr + ti[tilelow].w * (int)floor(x) + (int)floor(y))));
	col[1] = base255(rgb(*(ti[tilehi].data_ptr + ti[tilehi].w * (int)floor(x) + (int)floor(y))));

	ret = sum(scale(weight[0], col[0]), scale(weight[1], col[1]));
	return (ret);	
}

void		init_hitli(t_vector *hitli, t_vector hit, t_global *g)
{
	int i;

	i = 0;
	while (i < g->lights)
	{
		hitli[i] = diff(g->li[i], hit);
		i++;
	}
}

void		init_bri(int *bri, t_vector *hitli, t_vector nrm, t_global *g)
{
	int i;

	i = 0;
	*bri = 0;
	while(i < g->lights)
	{
		*bri += fmax(round(255 * dot(norm(hitli[i]), nrm)), *g->ambient);
		i++;
	}
	*bri = round(*bri / (double)g->lights);
}

int		inside_cone(t_vector p, t_object obj, t_global *g)
{
	double axdst;
	double cirad;
	t_vector ptoaxproj;
	t_vector ptoaxperp;
	t_vector op;
	t_global *a;

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


t_colbri	simple_bright_cone(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_vector	nrm;
	t_colbri			ret;
	t_vector	reflrayv;
	int		retobs;
	t_vector	hitli[g->lights];
	int		i;
	t_colbri	retorig;

	nrm = obj.nr;

	init_hitli(hitli, hit, g);
	if (inside_cone(*g->cam_pos, obj, g))
	{
		if (!inside_cone(*g->li, obj, g))
			ret.bri = *g->ambient;
	}
	else if (inside_cone(*g->li, obj, g))
		ret.bri = *g->ambient;
	else
		init_bri(&ret.bri, hitli, nrm, g);
	ret.col = obj.color;	
	if (obj.spec || obj.re)
		reflrayv = reflray(st, hit, nrm, g);
	if (obj.re)
		do_re(reflrayv, &ret.col, ret.col, hit, nrm, obj, g);
	if (obj.trans)
		do_trans(st, hit, &ret, ret, nrm, obj, g);
	obstructed(&ret, hit, hitli, reflrayv, obj, g);
	return (ret);
}

t_colbri	bright_cone(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_vector	nrm;
	t_vector	camforw;
	t_vector	hit0;
	t_colbri			ret;
	t_vector	ax;
	int		retobs;
	t_vector	 hitli[g->lights];
	t_vector	reflrayv;

	hit0 = diff(hit, *obj.ctr);
	ax = scale(dot(hit0, obj.base[1]) * (1 + obj.rd2), obj.base[1]);
	nrm = norm(diff(hit0, ax));

	init_hitli(hitli, hit, g);
	if (inside_cone(*g->cam_pos, obj, g))
	{
		nrm = scale(-1, nrm);
		if (!inside_cone(*g->li, obj, g))
			ret.bri = *g->ambient;
		else
			init_bri(&ret.bri, hitli, nrm, g);
	}
	else
		init_bri(&ret.bri, hitli, nrm, g);
	obj.nr = nrm;
	ret.nrm = nrm;
	if (obj.tile[0].data_ptr)
	{
		double x;
		double y;
		t_vector proj;
		t_vector ctrhit;
		ctrhit = diff(hit, *obj.ctr);

		proj = diff(ctrhit, scale(dot(obj.base[1], ctrhit),obj.base[1]));
		proj = norm(proj);
		x = obj.tile[0].w2 * (1 * M_1_PI * myacos(proj, obj.base[2], obj.base[1], g));
		y = mymod(1 - dot(obj.base[1], diff(hit, *obj.ctr)), obj.tile[0].h);
		if (g->mip_map)
			ret.col = mip_col(y, x, dot(diff(hit, *g->cam_pos), diff(hit, *g->cam_pos)), obj, g);
		else
			ret.col = *(obj.tile[0].vectile + lround(y) * obj.tile[0].w + lround(x));
	}
	else
		ret.col = obj.color;
	ret.colself = ret.col;
	if (obj.re || obj.spec)
		reflrayv = reflray(st, hit, nrm, g);
	if (obj.re)
		do_re(reflrayv, &ret.col, ret.col, hit, nrm, obj, g);
	if (obj.trans)
		do_trans(st, hit, &ret, ret, nrm, obj, g);
	obstructed(&ret, hit, hitli, reflrayv, obj, g);
	return (ret);
}

t_colbri	simple_bright_cylinder(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_vector	nrm;
	t_colbri		ret;
	t_dstpst	t;
	int		retobs;
	t_vector	hitli[g->lights];
	int		i;
	t_vector	reflrayv;

	nrm = obj.nr;
	init_hitli(hitli, hit, g);
	if (obj.cam_pos && (t = obj.hit(*g->cam_pos, *g->li, diff(*g->li, *g->cam_pos),obj, g)).dst < 1)
		ret.bri = *g->ambient;
	else
		init_bri(&ret.bri, hitli, nrm, g);
	ret.col = obj.color;
	if (obj.spec || obj.re)
		reflrayv = reflray(st, hit, nrm, g);
	if (obj.re)
		do_re(reflrayv, &ret.col, ret.col, hit, nrm, obj, g);
	if (obj.trans)
		do_trans(st, hit, &ret, ret, nrm, obj, g);
	obstructed(&ret, hit, hitli, reflrayv, obj, g);
	return (ret);
}

t_colbri	bright_cylinder(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_vector	nrm;
	t_vector	vrt;
	t_vector	hit0;
	t_colbri		ret;
	t_dstpst	t;
	int		retobs;
	t_vector	hitli[g->lights];
	int		i;
	t_vector	reflrayv;

	hit0 = diff(hit, *obj.ctr);
	vrt = obj.base[1];
	vrt = scale(dot(hit0, vrt), vrt);
	nrm = norm(diff(hit0, vrt));

	init_hitli(hitli, hit, g);
	if (obj.cam_pos)
	{
		t = obj.hit(*g->cam_pos, *g->li, diff(*g->li, *g->cam_pos),obj, g);
		nrm = scale(-1, nrm);	
		if (t.dst < 1)
			ret.bri = *g->ambient;
		else
			init_bri(&ret.bri, hitli, nrm, g);
	}
	else
		init_bri(&ret.bri, hitli, nrm, g);
	obj.nr = nrm;	
	ret.nrm = nrm;	
	if (obj.tile[0].data_ptr)
	{
		double x;
		double y;

		t_vector proj;
		t_vector ctrhit;
		ctrhit = diff(hit, *obj.ctr);
		proj = diff(ctrhit, scale(dot(obj.base[1], ctrhit),obj.base[1]));
		proj = norm(proj);
		x = obj.tile[0].w2 * (1 - (1 - 2 * (det(proj, obj.base[0]) < 0)) * M_1_PI * acos(dot(proj, obj.base[0])));

		double xdst;
		xdst = dot(obj.base[1], diff(hit, *obj.ctr));
		if (g->mip_map)
		{
			x = obj.tile[0].w2 * (1 - (1 - 2 * (det(proj, obj.base[0]) < 0)) * M_1_PI * acos(dot(proj, obj.base[0])));
			y = mymod(xdst, obj.tile[0].h);
			ret.col = mip_col(y, x, dot(diff(hit, *g->cam_pos), diff(hit, *g->cam_pos)), obj, g);
		}
		else
		{
			x = obj.tile[0].w2 * M_1_PI * myacos(proj, obj.base[0], obj.base[1], g);
			y = myintmod(xdst, obj.tile[0].h);
			ret.col = *(obj.tile[0].vectile + lround(y) * obj.tile[0].w + lround(x));
			ret.colself = ret.col;
		}
	}
	else
		ret.colself = obj.color;
	if (obj.spec || obj.re)
		reflrayv = reflray(st, hit, nrm, g);
	if (obj.re)
		do_re(reflrayv, &ret.col, ret.col, hit, nrm, obj, g);
	if (obj.trans)
		do_trans(st, hit, &ret, ret, nrm, obj, g);
	obstructed(&ret, hit, hitli, reflrayv, obj, g);

	if (ret.bri < *g->ambient)
		ret.bri = *g->ambient;
	return (ret);
}

void		do_1_spec(t_colbri *tmp, t_colbri *ret, t_vector hit, t_vector *hitli, t_vector nrm, t_vector reflrayv, t_object obj, int i, t_global *g)
{
	g->cosa[i] = dot(norm(hitli[i]),norm(reflrayv));
	if (g->cosa[i] > 0)
	{
		g->cosa[i] = tothe2(g->cosa[i], obj.spec);
		tmp->col = sum(tmp->col, sum(scale(g->cosa[i], g->white), scale((1 - g->cosa[i]), ret->col)));
	}
	else
		tmp->col = sum(tmp->col, ret->col);
}

void		do_spec(t_colbri *ret, t_vector hit, t_vector nrm, t_vector reflrayv, t_object obj, t_global *g)
{
		double	cosa;
		double cosa3;
		int	i;
		t_colbri tmp;
		t_vector hitli[g->lights];

		i = -1;
		while (++i < g->lights)
			hitli[i] = diff(g->li[i], hit);
		init_vector(&tmp.col, 0, 0, 0);
		i = -1;
		while (++i < g->lights)
			do_1_spec(&tmp, ret, hit, hitli, nrm, reflrayv, obj, i, g);
		tmp.col = scale(1 / (double)g->lights, tmp.col);
		ret->col = tmp.col;	
}
	
t_colbri	simple_bright_sphere(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_colbri		ret;
	t_vector	nrm;
	t_vector	ctrli;
	t_colbri	ret2;
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
		// *tileocol = base255(rgb(*(obj.tile[0].data_ptr + obj.tile[0].w * lround(y) + lround(x))));
	return (*tileocol);
}

t_colbri	bright_sphere(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_colbri		ret;
	t_vector	nrm;
	t_vector	ctrli;
	int		retobs;
	t_vector	proj;
	t_vector	ctrhit;
	t_colbri	retorig;
	t_colbri	transo;
	t_colbri	reo;
	t_colbri	tileo;
	t_colbri	speco;
	int		i;
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

t_colbri		simple_bright_spheror(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_colbri	ret;
	t_vector	nrm;
	t_vector	ctrli;
	t_vector	refl;
	t_objecthit	reflobj;
	t_vector	camhit;
	t_vector	combcolor;
	t_vector	reflcolor;
	int		retorig;
	double		re;
	t_vector hitli = diff(*g->li, hit);

	re = 0.5;
	nrm = norm(diff(hit, *obj.ctr));
	retorig = (round(255 * dot(norm(hitli), nrm)));
	if (retorig < *g->ambient)
		retorig = *g->ambient;
	camhit = diff(hit, st);
	t_vector camhitx = diff(camhit, scale(dot(camhit, nrm), nrm));
	refl = (diff(scale(2, camhitx), camhit));
	t_dstpst temp;
	objecthit(&temp, hit, sum(refl, hit), g->obj, g->argc + 1, g);
	reflobj.hit = sum(scale(temp.dst, refl), hit);
	reflobj.obj = temp.obj;

	if (reflobj.obj.name == NULL)
	{
		combcolor = scale(1 - re, obj.color);
		ret.col = combcolor;
		ret.bri = ((1 - re) * retorig);
		return (ret);
	}
	ret = reflobj.obj.bright(hit, reflobj.hit, reflobj.obj, g);
	combcolor = sum(scale(re, ret.col), scale(1 - re, obj.color));
	ret.bri = ((1 - re) * retorig + re * ret.bri);

	ret.col = combcolor;
	return (ret);
}

t_colbri		bright_spheror(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_colbri	ret;
	t_vector	nrm;
	t_vector	ctrli;
	t_objecthit	reflobj;
	t_vector	camhit;
	t_vector	combcolor;
	t_vector	reflcolor;
	int		retorig;
	t_vector	proj;
	double		x;
	double		y;
	t_vector	ctrhit;
	t_vector	hitli = diff(*g->li, hit);

	nrm = norm(diff(hit, *obj.ctr));
	retorig = (round(255 * dot(norm(diff(*g->li, hit)), nrm)));
	if (retorig < *g->ambient)
		retorig = *g->ambient;

	if (obj.tile[0].data_ptr)
	{
		ctrhit = diff(hit, *obj.ctr);
		proj = diff(ctrhit, scale(dot(obj.base[1], ctrhit),obj.base[1]));
		proj = norm(proj);
		x = obj.tile[0].w2 * (1 - (1 - 2 * (det(proj, obj.base[2]) < 0)) * M_1_PI * acos(dot(proj, obj.base[2])));
		y = obj.tile[0].h * ( (1 - 2 * (det(nrm, obj.base[1]) < 0)) * M_1_PI * acos(dot(nrm, obj.base[1])));	
		obj.color = mip_col(y, x, dot(diff(hit, *g->cam_pos), diff(hit, *g->cam_pos)), obj, g);
	}
	ret = refl(st, hit, nrm, obj, g);
	ret.bri = ((1 - obj.re) * retorig + obj.re * ret.bri);
	ret.col = sum(scale(1 - obj.re, obj.color), scale(obj.re, ret.col));
	return (ret);
}

double			bell(double tile_dst, double crt_dst)
{
	double v;

	v = 5;	
	return (1 / sqrt(M_PI * 2 * v * v) * exp(-(crt_dst - tile_dst) * (crt_dst - tile_dst) / (2 * v * v)));
}


t_colbri		simple_bright_plane(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_colbri			ret;
	int			i;
	int			retobs;
	int			chess;
	int			tempbri;
	t_vector	v;
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

t_colbri		bright_plane(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_colbri			ret;
	int			i;
	int			retobs;
	int			chess;
	int			tempbri;
	t_vector	v;
	double		x;
	double		y;
	t_colbri	retorig;
	t_vector	reflrayv;
	t_vector	hitli[g->lights];
	t_vector	colself;
	
	init_hitli(hitli, hit, g);
	if (obj.cam_pos)
	{
		obj.base[1].x = -obj.base[1].x;
		obj.base[1].y = -obj.base[1].y;
		obj.base[1].z = -obj.base[1].z;
	}
	init_bri(&retorig.bri, hitli, obj.base[1], g);
	if (obj.tile[0].data_ptr)
	{
		v = diff(hit, *obj.ctr);
		x = mymod(v.x, obj.tile[0].w);
		y = mymod(v.z, obj.tile[0].h);
		retorig.col = base(rgb(*(obj.tile[0].data_ptr + lround(y) * obj.tile[0].w + lround(x))));
		ret.colself = retorig.col;
	}
	else
	{
		chess = lround(fabs(hit.x) / (double)80) % 2 == lround(fabs(hit.z) / (double)80) % 2;
		if (chess)
			init_vector(&retorig.col, 1, 0, 0.5);
		else
			retorig.col = obj.color;
		ret.colself = retorig.col;
		colself = retorig.col;
	}	
	if (obj.spec || obj.re)
		reflrayv = reflray(st, hit, obj.base[1], g);
	if (obj.re)
		do_re(reflrayv, &ret.col, retorig.col, hit, obj.base[1], obj, g);
	else
		ret.col = retorig.col;
	ret.bri = retorig.bri;
	obstructed(&ret, hit, hitli, reflrayv, obj, g);
	return (ret);
}

t_colbri		simple_bright_tri(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_colbri			ret;
	t_object	a;
	int			i;
	int			retobs;
	int			tempbri;
	t_colbri		retorig;
	t_vector		hitli[g->lights];
	t_vector		reflrayv;

	init_hitli(hitli, hit, g);
	if (0 && dot(diff(hit, st), obj.base[1]) > 0)
	{
		obj.base[1].x = -obj.base[1].x;
		obj.base[1].y = -obj.base[1].y;
		obj.base[1].z = -obj.base[1].z;
	}
	init_bri(&retorig.bri, hitli, obj.base[1], g);

	ret.col = obj.color;
	ret.bri = retorig.bri;

	if (obj.spec || obj.re)
		reflrayv = reflray(st, hit, obj.base[1], g);
	if (obj.re)
		do_re(reflrayv, &ret.col, ret.col, hit, obj.base[1], obj, g);
	ret.bri = retorig.bri;
	if (obj.trans)
		do_trans(st, hit, &ret, ret, obj.base[1], obj, g);
	
	if (obj.spec)
		do_spec(&ret, hit, obj.base[1], reflrayv, obj, g);
	return (ret);
}

t_colbri		bright_tri(t_vector st, t_vector hit, t_object obj, t_global *g)
{
	t_colbri			ret;
	int			i;
	int			retobs;
	int			chess;
	int			tempbri;
	t_vector	v;
	double		x;
	double		y;
	t_tile		*ti;
	double		newres;
	double		tilen;
	double	dst2;
	int tilelow;
	int tilehi;
	t_colbri retorig;
	t_vector	hitli[g->lights];
		t_vector reflrayv;


	init_hitli(hitli, hit, g);	
	if (dot(diff(hit, *g->cam_pos), obj.base[1]) > 0)
	{
		obj.base[1].x = -obj.base[1].x;
		obj.base[1].y = -obj.base[1].y;
		obj.base[1].z = -obj.base[1].z;
	}
	init_bri(&retorig.bri, hitli, obj.base[1], g);
	if (obj.tile[0].data_ptr)
	{
		v = diff(hit, *obj.ctr);
		x = mymod(v.x, obj.tile[0].w);
		y = mymod(v.z, obj.tile[0].h);
		if (g->mip_map)
			ret.col = mip_col(y, x, dot(diff(hit, *g->cam_pos), diff(hit, *g->cam_pos)), obj, g);
		else
			ret.col = *(obj.tile[0].vectile + lround(y)* obj.tile[0].w + lround(x));
	}
	else
		ret.col = obj.color;
	ret.colself = ret.col;
	if (obj.re || obj.spec)
		reflrayv = reflray(st, hit, obj.base[1], g);
	if (obj.re)
		do_re(reflrayv, &ret.col, ret.col, hit, obj.base[1], obj, g);
	if (obj.trans)
		do_trans(st, hit, &ret, ret, obj.base[1], obj, g);
	ret.bri = retorig.bri;
	if (obj.spec)
		do_spec(&ret, hit, obj.base[1], reflrayv, obj, g);
	return (ret);
}