/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 21:12:58 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 21:12:59 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int 			hit_quad(t_vector st, t_vector end, t_vector ray, t_vector quad[4], t_global *g)
{
	t_vector	tri[2][3];
	t_object	obj[2];
	t_dstpst	hit[2];

	tri[0][0] = quad[0];
	tri[0][1] = quad[1];
	tri[0][2] = quad[2];
	tri[1][0] = quad[1];
	tri[1][1] = quad[2];
	tri[1][2] = quad[3];
	obj[0].bd1 = tri[0][0];
	obj[0].bd2 = tri[0][1];
	obj[0].bd3 = tri[0][2];
	obj[1].bd1 = tri[1][0];
	obj[1].bd2 = tri[1][1];
	obj[1].bd3 = tri[1][2];
	hit[0] = hit_tri(st, end, ray, obj[0], g);
	hit[1] = hit_tri(st, end, ray, obj[1], g);
	return ((hit[0].dst > 0 || hit[0].dst <= 0) || (hit[1].dst > 0 || hit[1].dst <= 0));
}

int				hit_box(t_vector st, t_vector end, t_vector ray, t_object obj, t_global *g)
{
	t_vector	quad[6][4];

	quad[0][0] = obj.box[0];
	quad[0][1] = obj.box[1];
	quad[0][2] = obj.box[2];
	quad[0][3] = obj.box[3];
	quad[1][0] = obj.box[0];
	quad[1][1] = obj.box[1];
	quad[1][2] = obj.box[4];
	quad[1][3] = obj.box[5];
	quad[2][0] = obj.box[1];
	quad[2][1] = obj.box[2];
	quad[2][2] = obj.box[5];
	quad[2][3] = obj.box[6];
	quad[3][0] = obj.box[3];
	quad[3][1] = obj.box[7];
	quad[3][2] = obj.box[6];
	quad[3][3] = obj.box[2];
	quad[4][0] = obj.box[4];
	quad[4][1] = obj.box[5];
	quad[4][2] = obj.box[6];
	quad[4][3] = obj.box[7];
	quad[5][0] = obj.box[0];
	quad[5][1] = obj.box[4];
	quad[5][2] = obj.box[7];
	quad[5][3] = obj.box[3];
	return (hit_quad(st, end, ray, quad[0], g) ||
		hit_quad(st, end, ray, quad[1], g) ||
		hit_quad(st, end, ray, quad[2], g) ||
		hit_quad(st, end, ray, quad[3], g) ||
		hit_quad(st, end, ray, quad[4], g) ||
		hit_quad(st, end, ray, quad[5], g));
}

t_dstpst		hit_complex(t_vector st, t_vector end, t_vector ray, t_object obj, t_global *g)
{
	t_dstpst	t;
	t_dstpst	framecheck;

	framecheck = hit_sphere(st, end, ray, *(obj.frame), g);
	if (framecheck.obj.name == NULL)
			return (*(nani(&t)));
	objecthit(&t, st, end, obj.tris, obj.rd, g);
	if (t.obj.name == NULL)
		return (*(nani(&t)));
	return (t);
}

t_dstpst		hit_plane(t_vector st, t_vector end, t_vector ray, t_object obj, t_global *g)
{
	t_dstpst	t;
	t_global	p;

	p = *g;
	t.dst = -dot(diff(st, *obj.ctr), obj.base[1]) / dot(ray, obj.base[1]);
	if (t.dst < 0.0000001)
		return (*nani(&t));
	t.obj = obj;
	t.pst = obj.cam_pos;
	return (t);
}

t_dstpst		hit_sphere(t_vector st, t_vector end, t_vector ray, t_object obj, t_global *g)
{
	t_vector	dx[2];
	t_vector	abc;
	double		det;
	t_dstpst	t;
	t_global	p;

	p = *g;
	t.pst = 0;
	dx[0] = ray;
	dx[1] = diff(st, *obj.ctr);
	abc.x = dot(dx[0], dx[0]);
	abc.y = 2 * dot(dx[1], dx[0]);
	abc.z = dot(dx[1], dx[1]) - obj.rd2;
	det = abc.y * abc.y - 4 * abc.x * abc.z;
	if (det < 0)
		return (*(nani(&t)));
	t.dst = (-abc.y - sqrt(det)) / (2 * abc.x);
	if (t.dst <= 0.000001 && (t.pst = 1))
		t.dst = (-abc.y + sqrt(det)) / (2 * abc.x);
	if (t.dst <= 0.000001)
		return (*nani(&t));
	t.obj = obj;
	return (t);
}

t_dstpst		hit_cylinder(t_vector st, t_vector end, t_vector ray, t_object obj, t_global *g)
{
	t_vector	d;
	t_vector	po[4];
	t_dstpst	t;
	t_global	p;

	p = *g;
	t.pst = 0;
	po[0] = ray;
	po[3] = diff(st, *obj.ctr);
	d.y = dot(po[0], obj.base[1]);
	d.x = dot(po[3], obj.base[1]);
	po[2].x = dot(po[0], po[0]) - d.y * d.y;
	po[2].y = 2 * (dot(po[0], po[3]) - d.y * d.x);
	po[2].z = dot(po[3], po[3]) - d.x * d.x - obj.rd2;
	d.z = po[2].y * po[2].y - 4 * po[2].x * po[2].z;
	if (d.z < 0)
		return (*nani(&t));
	t.dst = (-po[2].y - sqrt(d.z)) / (2 * po[2].x);
	if (t.dst < 0.000001 && (t.pst = 1))
		t.dst = (-po[2].y + sqrt(d.z)) / (2 * po[2].x);
	if (t.dst < 0.0000001)
		return (*(nani(&t)));
	t.obj = obj;
	return (t);
}

t_dstpst		hit_tri(t_vector st, t_vector end, t_vector ray, t_object obj, t_global *g)
{
	t_dstpst	t;
	t_global	p;
	t_dstpst	framecheck;
	t_vector	hit;

	p = *g;
	t.dst = -dot(diff(st, obj.bd1), obj.base[1]) / dot(ray, obj.base[1]);
	if (t.dst < 0.000001)
		return (*nani(&t));
	hit = sum(scale(t.dst, ray), st);
	if (!pinside(sum(scale(t.dst, ray), st), obj, obj.base[1], g))
		return (*nani(&t));
	t.obj = obj;
	return (t);
}

t_dstpst		hit_cone(t_vector st, t_vector end, t_vector ray, t_object obj, t_global *g)
{
	t_vector	dx[2];
	t_vector	dvxvdet;
	t_vector	abc;
	t_global	p;
	double		ret;
	double		min;

	p = *g;
	dx[0] = diff(st, *obj.ctr);
	dx[1] = ray;
	dvxvdet.x = dot(dx[1], obj.base[1]);
	dvxvdet.y = dot(dx[0], obj.base[1]);
	abc.x = dot(dx[1], dx[1]) - (1 + obj.rd2) * dvxvdet.x * dvxvdet.x;
	abc.y = 2 * (dot(dx[1], dx[0]) - (1 + obj.rd2) * dvxvdet.x * dvxvdet.y);
	abc.z = dot(dx[0], dx[0]) - (1 + obj.rd2) * dvxvdet.y * dvxvdet.y;
	dvxvdet.z = abc.y * abc.y - 4 * abc.x * abc.z;
	if (dvxvdet.z < 0)
		return (*nani(&g->cone[0]));
	g->cone[0].dst = (-abc.y - sqrt(dvxvdet.z)) / (2 * abc.x);
	g->cone[1].dst = (-abc.y + sqrt(dvxvdet.z)) / (2 * abc.x);
	ret = fmin(g->cone[0].dst, g->cone[1].dst);
	if (ret < 0.000001)
	{
		g->cone[0].dst = fmax(g->cone[1].dst, g->cone[0].dst);
		if (g->cone[0].dst < 0.0000001)
			return (*nani(&g->cone[0]));
		g->cone[0].pst = 1;
		g->cone[0].obj = obj;
		return (g->cone[0]);
	}
	else
	{
		g->cone[0].obj = obj;
		g->cone[0].dst = ret;
		return (g->cone[0]);
	}
	return (g->cone[0]);
}
