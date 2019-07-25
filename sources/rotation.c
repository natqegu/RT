/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 16:08:09 by vkarpova          #+#    #+#             */
/*   Updated: 2019/02/07 16:08:10 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			rotate_x(double angle, double *y, double *z)
{
	double		tmp_y;
	double		tmp_z;
	double		pi;

	pi = 3.14 / 180;
	tmp_y = *y;
	tmp_z = *z;
	*y = tmp_y * cos(angle * pi) - tmp_z * sin(angle * pi);
	*z = tmp_y * sin(angle * pi) + tmp_z * cos(angle * pi);
}

void			rotate_y(double angle, double *x, double *z)
{
	double		tmp_x;
	double		tmp_z;
	double		pi;

	pi = 3.14 / 180;
	tmp_x = *x;
	tmp_z = *z;
	*z = tmp_z * cos(angle * pi) - tmp_x * sin(angle * pi);
	*x = tmp_z * sin(angle * pi) + tmp_x * cos(angle * pi);
}

void			rotate_z(double angle, double *x, double *y)
{
	double		tmp_x;
	double		tmp_y;
	double		pi;

	pi = 3.14 / 180;
	tmp_x = *x;
	tmp_y = *y;
	*x = tmp_x * cos(angle * pi) - tmp_y * sin(angle * pi);
	*y = tmp_x * sin(angle * pi) + tmp_y * cos(angle * pi);
}

t_vector		rotation(t_all *all, t_vector canvas)
{
	t_vector	d;
	t_vector	vec;

	vec = canvas;
	rotate_x(all->rot.x, &vec.y, &vec.z);
	rotate_y(all->rot.y, &vec.x, &vec.z);
	rotate_z(all->rot.z, &vec.x, &vec.y);
	d = vec;
	norm(d);
	return (d);
}

int				num(char *str)
{
	int			i;

	i = 0;
	if (str)
	{
		if (str[i] == '-')
			i++;
		if (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			return (0);
		while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}
