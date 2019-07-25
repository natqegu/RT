/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:52:14 by vkarpova          #+#    #+#             */
/*   Updated: 2019/02/01 17:52:15 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector		intersect_ray(t_list *list, t_vector o, t_vector d)
{
	t_vector	a;

	a = init_vector(0, 0, 0, 0);
	if (list->content_size == CONE)
		a = intersect_cone((t_cone *)(list->content), o, d);
	else if (list->content_size == CYL)
		a = intersect_cyl((t_cylinder *)(list->content), o, d);
	else if (list->content_size == SPHERE)
		a = intersect_sphere((t_sphere *)(list->content), o, d);
	else if (list->content_size == PLANE)
		a = intersect_plane((t_plane *)(list->content), o, d);
	else
		a = init_vector(600000, 600000, 600000, 600000);
	return (a);
}

t_vector		intersect_sphere(t_sphere *sphere, t_vector o, t_vector d)
{
	t_vector	oc;
	t_vector	a;
	t_vector	k;
	double		disc;

	a = init_vector(0, 0, 0, 0);
	oc = minus(o, sphere->c);
	k.x = dot(d, d);
	k.y = 2 * dot(oc, d);
	k.z = dot(oc, oc) - sphere->r * sphere->r;
	disc = k.y * k.y - 4 * k.x * k.z;
	if (disc < 0)
	{
		a.t1 = 600000;
		a.t2 = 600000;
		return (a);
	}
	a.t1 = (-k.y + sqrt(disc)) / (2 * k.x);
	a.t2 = (-k.y - sqrt(disc)) / (2 * k.x);
	return (a);
}

t_vector		intersect_cyl(t_cylinder *cyl, t_vector o, t_vector d)
{
	t_vector	oc;
	t_vector	a;
	t_vector	k;
	double		disc;

	a = init_vector(0, 0, 0, 0);
	oc = minus(o, cyl->c);
	k.x = dot(d, d) - dot(d, cyl->v) * dot(d, cyl->v);
	k.y = 2 * (dot(oc, d) - dot(cyl->v, d) * dot(oc, cyl->v));
	k.z = dot(oc, oc) - dot(oc, cyl->v) * dot(oc, cyl->v) - cyl->r * cyl->r;
	disc = k.y * k.y - 4 * k.x * k.z;
	if (disc < 0)
	{
		a.t1 = 600000;
		a.t2 = 600000;
		return (a);
	}
	a.t1 = (-k.y + sqrt(disc)) / (2 * k.x);
	a.t2 = (-k.y - sqrt(disc)) / (2 * k.x);
	return (a);
}

t_vector		intersect_cone(t_cone *c, t_vector o, t_vector d)
{
	t_vector	oc;
	t_vector	a;
	t_vector	k;
	double		disc;

	a = init_vector(0, 0, 0, 0);
	oc = minus(o, c->c);
	k.x = dot(d, d) - (1 + (c->a) * (c->a)) * dot(d, c->v) * dot(d, c->v);
	k.y = 2 * (dot(d, oc) - (1 + (c->a) * (c->a)) * dot(d, c->v)
			* dot(oc, c->v));
	k.z = dot(oc, oc) - (1 + (c->a) * (c->a)) * dot(oc, c->v) * dot(oc, c->v);
	disc = k.y * k.y - 4 * k.x * k.z;
	if (disc < 0)
	{
		a.t1 = 600000;
		a.t2 = 600000;
		return (a);
	}
	a.t1 = (-k.y + sqrt(disc)) / (2 * k.x);
	a.t2 = (-k.y - sqrt(disc)) / (2 * k.x);
	return (a);
}

t_vector		intersect_plane(t_plane *plane, t_vector o, t_vector d)
{
	t_vector	oc;
	t_vector	a;
	double		i;
	double		j;

	a = init_vector(0, 0, 0, 0);
	oc = minus(plane->c, o);
	i = dot(oc, plane->v);
	j = dot(d, plane->v);
	if (j == 0 || ((i / j) < 0))
	{
		a.t1 = 600000;
		a.t2 = 600000;
		return (a);
	}
	a.t1 = i / j;
	a.t2 = i / j;
	return (a);
}
