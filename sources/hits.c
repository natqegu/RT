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

t_dstpst	hit_complex(t_vector st, t_vector end, t_vector ray, t_object *obj)
{
	t_dstpst t;
	t_dstpst framecheck;

	framecheck = hit_sphere(st, end, ray, obj->frame);
	if (framecheck.obj.name == NULL)
		return (*(nani(&t)));
	objecthit(&t, create_3_vecs(st, NULL, end), obj->tris, obj->rd);
	if (t.obj.name == NULL)
		return (*(nani(&t)));
	return (t);
}

t_dstpst	hit_sphere(t_vector st, t_vector end, t_vector ray, t_object *obj)
{
	t_vector	dx[2];
	t_vector	abc;
	double		det;
	t_dstpst	t;

	t.pst = 0;
	dx[0] = ray;
	dx[1] = diff(st, *obj->ctr);
	abc.x = dot(dx[0], dx[0]);
	abc.y = 2 * dot(dx[1], dx[0]);
	abc.z = dot(dx[1], dx[1]) - obj->rd2;
	det = abc.y * abc.y - 4 * abc.x * abc.z;
	if (det < 0)
		return (*(nani(&t)));
	t.dst = (-abc.y - sqrt(det)) / (2 * abc.x);
	if (t.dst <= 0.000001 && (t.pst = 1))
		t.dst = (-abc.y + sqrt(det)) / (2 * abc.x);
	if (t.dst <= 0.000001)
		return (*nani(&t));
	t.obj = *obj;
	hello(end);
	return (t);
}

t_dstpst	hit_cylinder(t_vector st, t_vector end, t_vector ray, t_object *obj)
{
	t_vector d;
	t_vector po[4];
	t_dstpst t;

	t.pst = 0;
	po[0] = ray;
	po[3] = diff(st, *obj->ctr);
	d.y = dot(po[0], obj->base[1]);
	d.x = dot(po[3], obj->base[1]);
	po[2].x = dot(po[0], po[0]) - d.y * d.y;
	po[2].y = 2 * (dot(po[0], po[3]) - d.y * d.x);
	po[2].z = dot(po[3], po[3]) - d.x * d.x - obj->rd2;
	d.z = po[2].y * po[2].y - 4 * po[2].x * po[2].z;
	if (d.z < 0)
		return (*nani(&t));
	t.dst = (-po[2].y - sqrt(d.z)) / (2 * po[2].x);
	if (t.dst < 0.000001 && (t.pst = 1))
		t.dst = (-po[2].y + sqrt(d.z)) / (2 * po[2].x);
	if (t.dst < 0.0000001)
		return (*(nani(&t)));
	t.obj = *obj;
	hello(end);
	return (t);
}

t_dstpst	hit_tri(t_vector st, t_vector end, t_vector ray, t_object *obj)
{
	t_dstpst t;
	t_vector hit;

	t.dst = -dot(diff(st, obj->bd1), obj->base[1]) / dot(ray, obj->base[1]);
	if (t.dst < 0.000001)
		return (*nani(&t));
	hit = sum(scale(t.dst, ray), st);
	if (!pinside(sum(scale(t.dst, ray), st), *obj, obj->base[1]))
		return (*nani(&t));
	t.obj = *obj;
	hello(end);
	return (t);
}

t_dstpst	hit_plane(t_vector st, t_vector end, t_vector ray, t_object *obj)
{
	t_dstpst t;

	t.dst = -dot(diff(st, *obj->ctr), obj->base[1]) / dot(ray, obj->base[1]);
	if (t.dst < 0.0000001)
		return (*nani(&t));
	hello(end);
	t.obj = *obj;
	t.pst = obj->cam_pos;
	return (t);
}
