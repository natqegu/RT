/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:51:48 by vkarpova          #+#    #+#             */
/*   Updated: 2019/02/01 17:51:49 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector		minus(t_vector a, t_vector b)
{
	t_vector	new;

	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;
	return (new);
}

t_vector		plus(t_vector a, t_vector b)
{
	t_vector	new;

	new.x = a.x + b.x;
	new.y = a.y + b.y;
	new.z = a.z + b.z;
	return (new);
}

t_vector		times(double n, t_vector a)
{
	t_vector	new;

	new.x = a.x * n;
	new.y = a.y * n;
	new.z = a.z * n;
	return (new);
}

double			dot(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
	res.z = a.z * b.z;
	res.res = res.x + res.y + res.z;
	return (res.res);
}

double			dlinna(t_vector a)
{
	t_vector	res;

	res.res = sqrt(dot(a, a));
	return (res.res);
}
