/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linalg2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:07:35 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 18:07:36 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

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
