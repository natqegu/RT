/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linalg1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:07:35 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 18:07:36 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

double			myacos(t_vector ax, t_vector v, t_vector nrm)
{
	double		ret;

	ret = acos(dot(ax, v));
	if (left(v, ax, nrm))
		return (M_T - ret);
	if (ret > M_PI)
		return (M_T - ret);
	return (ret);
	return (M_T - acos(dot(ax, v)));
}

void			init_vector(t_vector *i, double x, double y, double z)
{
	i->x = x;
	i->y = y;
	i->z = z;
}

t_vector		cross(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = -a.y * b.z + a.z * b.y;
	ret.y = -a.z * b.x + a.x * b.z;
	ret.z = -a.x * b.y + a.y * b.x;
	return (ret);
}

int				left(t_vector a, t_vector b, t_vector nr)
{
	return (dot(cross(b, a), nr) >= -0.000004);
}

int				pinside(t_vector p, t_object obj, t_vector nr)
{
	t_vector	bd[3];
	t_vector	pt[3];

	bd[0] = diff(obj.bd2, obj.bd1);
	bd[1] = diff(obj.bd3, obj.bd2);
	bd[2] = diff(obj.bd1, obj.bd3);
	pt[0] = diff(p, obj.bd1);
	pt[1] = diff(p, obj.bd2);
	pt[2] = diff(p, obj.bd3);
	return (left(pt[0], bd[0], nr)
		&& left(pt[2], bd[2], nr)
		&& left(pt[1], bd[1], nr));
}
