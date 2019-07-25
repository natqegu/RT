/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:06:28 by vkarpova          #+#    #+#             */
/*   Updated: 2019/02/01 17:06:29 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector		norm(t_vector a)
{
	t_vector	norm;
	double		dlinna;

	dlinna = sqrt(dot(a, a));
	if (dlinna == 0)
		dlinna = 1;
	norm.x = a.x / dlinna;
	norm.y = a.y / dlinna;
	norm.z = a.z / dlinna;
	return (norm);
}

void			plane_normal(t_vec *vec, t_plane *plan)
{
	if (dot(vec->d, plan->v) < 0)
		vec->n = plan->v;
	else
		vec->n = minus(init_vector(0, 0, 0, 0), plan->v);
}

void			sphere_normal(t_vec *vec, t_sphere *sphr)
{
	t_vector	v;

	v = minus(vec->p, sphr->c);
	vec->n = norm(v);
}

void			cyl_normal(t_vec *vec, double t, t_cylinder *cyl)
{
	double		m;
	t_vector	oc;

	cyl->v = norm(cyl->v);
	oc = minus(vec->o, cyl->c);
	m = dot(vec->d, times(t, cyl->v)) + dot(oc, cyl->v);
	vec->n = minus(minus(vec->p, cyl->c), times(m, cyl->v));
	vec->n = norm(vec->n);
}

void			cone_normal(t_vec *vec, double t, t_cone *cone)
{
	double		m;
	t_vector	oc;
	t_vector	pc;

	cone->v = norm(cone->v);
	oc = minus(vec->o, cone->c);
	pc = minus(vec->p, cone->c);
	m = dot(vec->d, cone->v) * t + dot(oc, cone->v);
	vec->n = minus(pc, times(m, times((1 + (cone->a) * (cone->a)), cone->v)));
	vec->n = norm(vec->n);
}
