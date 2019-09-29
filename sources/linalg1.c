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

double			myacos(t_vector ax, t_vector v, t_vector nrm, t_global *g)
{
	double		ret;

	ret = acos(dot(ax, v));
	if (con(g))
		printf("left %d\n", left(v, ax, nrm, g));
	if (left(v, ax, nrm, g))
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

int				left(t_vector a, t_vector b, t_vector nr, t_global *g)
{
	return (dot(cross(b, a), nr) >= -0.000004);
}

int				pinside(t_vector p, t_object obj, t_vector nr, t_global *g)
{
	t_vector	bd[3];
	t_vector	pt[3];

	bd[0] = diff(obj.bd2, obj.bd1);
	bd[1] = diff(obj.bd3, obj.bd2);
	bd[2] = diff(obj.bd1, obj.bd3);
	pt[0] = diff(p, obj.bd1);
	pt[1] = diff(p, obj.bd2);
	pt[2] = diff(p, obj.bd3);
	return (left(pt[0], bd[0], nr, g)
		&& left(pt[2], bd[2], nr, g)
		&& left(pt[1], bd[1], nr, g));
}

double			det(t_vector a, t_vector b)
{
	return (a.x * b.z - a.z * b.x);
}

t_vector		rotate(t_vector ray, t_vector angle)
{
	t_vector	ret;
	t_vector	cxcycz;
	t_vector	sxsysz;
	t_vector	opt;
	t_vector	row[3];

	if (angle.x == 0 && angle.y == 0 && angle.z == 0)
		return (ray);
	init_vector(&cxcycz, cos(angle.x), cos(angle.y), cos(angle.z));
	init_vector(&sxsysz, sin(angle.x), sin(angle.y), sin(angle.z));
	init_vector(&opt, cxcycz.z * sxsysz.x,
	cxcycz.z * cxcycz.x, sxsysz.z * sxsysz.y);
	init_vector(&row[0], cxcycz.z * cxcycz.y, -sxsysz.z * cxcycz.x +
				opt.x * sxsysz.y, sxsysz.z * sxsysz.x + opt.y * sxsysz.y);
	init_vector(&row[1], sxsysz.z * cxcycz.y, opt.y
				+ opt.z * sxsysz.x, -opt.x + opt.z * cxcycz.x);
	init_vector(&row[2], -sxsysz.y, cxcycz.y * sxsysz.x, cxcycz.y * cxcycz.x);
	init_vector(&ret, dot(row[0], ray), dot(row[1], ray), dot(row[2], ray));
	return (ret);
}

double			tothe2(double x, int e)
{
	int			i;

	i = -1;
	while (++i < e)
		x = x * x;
	return (x);
}

t_dstpst		*nani(t_dstpst *t)
{
	t->dst = NAN;
	t->obj.name = NULL;
	return (t);
}
