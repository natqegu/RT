/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:02:13 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 18:02:14 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			brg(t_vector a)
{
	return (a.z + a.y * 256 + a.x * 65536);
}

t_vector	rgb(int c)
{
	t_vector	ret;

	ret.x = c / (65536);
	c = c - ret.x * 65536;
	ret.y = c / (256);
	c = c - ret.y * 256;
	ret.z = c;
	return (ret);
}

t_vector	base255(t_vector dir)
{
	dir.x = dir.x / (double)255;
	dir.y = dir.y / (double)255;
	dir.z = dir.z / (double)255;
	return (dir);
}

t_vector	base(t_vector dir)
{
	double		max;

	max = fmax(dir.x, fmax(dir.y, dir.z));
	dir.x = dir.x / (double)max;
	dir.y = dir.y / (double)max;
	dir.z = dir.z / (double)max;
	return (dir);
}

int			color(int b, t_vector v)
{
	v.x = round(b * v.x);
	v.y = round(b * v.y);
	v.z = round(b * v.z);
	return (v.z + v.y * 256 + v.x * 65536);
}
