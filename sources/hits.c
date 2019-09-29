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

#include "rt.h"

t_2_vec		cr_2_ve(t_vector one, t_vector two)
{
	t_2_vec hey;

	hey.one = one;
	hey.two = two;
	return (hey);
}

t_dstpst	hit_complex(t_2_vec st_end, t_vector ray, t_object obj, t_global *g)
{
	t_dstpst	t;
	t_dstpst	framecheck;

	framecheck = hit_sphere(st_end, ray, *(obj.frame), g);
	if (framecheck.obj.name == NULL)
			return (*(nani(&t)));
	objecthit(&t, st_end, obj.tris, obj.rd, g);
	if (t.obj.name == NULL)
		return (*(nani(&t)));
	return (t);
}

t_dstpst	hit_plane(t_2_vec st_end, t_vector ray, t_object obj, t_global *g)
{
	t_dstpst	t;
	t_global	p;

	p = *g;
	t.dst = -dot(diff(st_end.one, *obj.ctr), obj.base[1]) / dot(ray, obj.base[1]);
	if (t.dst < 0.0000001)
		return (*nani(&t));
	t.obj = obj;
	t.pst = obj.cam_pos;
	return (t);
}

t_dstpst	hit_sphere(t_2_vec st_end, t_vector ray, t_object obj, t_global *g)
{
	t_vector	dx[2];
	t_vector	abc;
	double		det;
	t_dstpst	t;
	t_global	p;

	p = *g;
	t.pst = 0;
	dx[0] = ray;
	dx[1] = diff(st_end.one, *obj.ctr);
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

t_dstpst	hit_cylinder(t_2_vec st_end, t_vector ray, t_object obj, t_global *g)
{
	t_vector	d;
	t_vector	po[4];
	t_dstpst	t;
	t_global	p;

	p = *g;
	t.pst = 0;
	po[0] = ray;
	po[3] = diff(st_end.one, *obj.ctr);
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

t_dstpst	hit_tri(t_2_vec st_end, t_vector ray, t_object obj, t_global *g)
{
	t_dstpst	t;
	t_global	p;
	t_dstpst	framecheck;
	t_vector	hit;

	p = *g;
	t.dst = -dot(diff(st_end.one, obj.bd1), obj.base[1]) / dot(ray, obj.base[1]);
	if (t.dst < 0.000001)
		return (*nani(&t));
	hit = sum(scale(t.dst, ray), st_end.one);
	if (!pinside(sum(scale(t.dst, ray), st_end.one), obj, obj.base[1], g))
		return (*nani(&t));
	t.obj = obj;
	return (t);
}

t_dstpst		hit_cone(t_2_vec st_end, t_vector ray, t_object obj, t_global *g)
{
	t_vector	dx[2];
	t_vector	dvxvdet;
	t_vector	abc;
	t_global	p;
	double		ret;
	double		min;

	p = *g;
	dx[0] = diff(st_end.one, *obj.ctr);
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
