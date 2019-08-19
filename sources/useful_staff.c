/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_staff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 18:11:58 by vkarpova          #+#    #+#             */
/*   Updated: 2019/08/02 18:11:59 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	miss_open_brackets(t_all *all)
{
	char		*line;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "[", 10) > 0))
	{
		if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "{", 10) > 0))
		{
			free(line);
		}
	}
}

void	miss_closed_brackets(t_all *all)
{
	char		*line;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "}", 10) > 0))
	{
		if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "]", 10) > 0))
		{
			free(line);
		}
	}
}

int				rgb_to_int(t_vector c)
{
	int		rgb;

	rgb = c.x;
	rgb = (rgb << 8) + c.y;
	rgb = (rgb << 8) + c.z;
	return (rgb);
}

t_vector		int_to_rgb(int rgb)
{
	t_vector	c;

	c.x = (rgb >> 16) & 0xFF;
	c.y = (rgb >> 8) & 0xFF;
	c.z = rgb & 0xFF;
	return (c);
}

t_vector		init_vector(double x, double y, double z, double t)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.t1 = t;
	vec.t2 = t;
	return (vec);
}
