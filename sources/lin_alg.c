/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lin_alg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:03:33 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 18:03:34 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_vector	scale(double a, t_vector b)
{
	b.x *= a;
	b.y *= a;
	b.z *= a;
	return (b);
}

double		dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	norm(t_vector a)
{
	double leng;

	leng = sqrt(dot(a, a));
	a.x = a.x / (double)leng;
	a.y = a.y / (double)leng;
	a.z = a.z / (double)leng;
	return (a);
}

t_vector	sum(t_vector a, t_vector b)
{
	a.x = b.x + a.x;
	a.y = b.y + a.y;
	a.z = b.z + a.z;
	return (a);
}

t_vector	diff(t_vector a, t_vector b)
{
	a.x = a.x - b.x;
	a.y = a.y - b.y;
	a.z = a.z - b.z;
	return (a);
}
