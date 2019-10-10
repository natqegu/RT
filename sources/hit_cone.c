/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:31:54 by nnovikov          #+#    #+#             */
/*   Updated: 2019/10/10 20:31:59 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_dstpst	hit_cone(t_vector st, t_vector end, t_vector ray, t_object *obj)
{
	t_vector	d;
	t_vector	abc;
	t_dstpst	cone[2];

	d.x = dot(ray, obj->base[1]);
	d.y = dot(diff(st, *obj->ctr), obj->base[1]);
	abc.x = dot(ray, ray) - (1 + obj->rd2) * d.x * d.x;
	abc.y = 2 * (dot(ray, diff(st, *obj->ctr)) - (1 + obj->rd2) * d.x * d.y);
	abc.z = dot(diff(st, *obj->ctr), diff(st, *obj->ctr)) - (1 + obj->rd2)
										* d.y * d.y;
	d.z = abc.y * abc.y - 4 * abc.x * abc.z;
	if (d.z < 0)
		return (*nani(&cone[0]));
	cone[0].dst = (-abc.y - sqrt(d.z)) / (2 * abc.x);
	cone[1].dst = (-abc.y + sqrt(d.z)) / (2 * abc.x);
	cone[0].dst = fmin(cone[0].dst, cone[1].dst);
	if (cone[0].dst < 0.000001)
		return (*nani(&cone[0]));
	else
	{
		cone[0].obj = *obj;
		return (cone[0]);
	}
	hello(end);
	return (cone[0]);
}
