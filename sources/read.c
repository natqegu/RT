/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:52:55 by vkarpova          #+#    #+#             */
/*   Updated: 2019/02/01 17:52:55 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				open_file(char **argv, t_all *all)
{
	t_list	*list;

	all->fd = open(argv[1], O_RDONLY);
	if (all->fd == -1)
		return (0);
	read_file(all);
	list = all->obj;
	if (list == NULL || all->is_cam == 0)
	{
		if (list == NULL)
			ft_putendl("There's no object to show");
		if (all->is_cam == 0)
			ft_putendl("You don't set camera position");
		return (0);
	}
	return (1);
}

void			read_file(t_all *all)
{
	char		*line;

	while (get_next_line(all->fd, &line) > 0)
	{
		if (ft_strncmp(line, "camera:", 7) == 0)
			save_cam(line, all);
		if (ft_strncmp(line, "rotation:", 9) == 0)
			save_rotation(all, line);
		if (ft_strncmp(line, "#light", 6) == 0)
			save_light(all);
		if (ft_strncmp(line, "#plane", 6) == 0)
			save_plane(all);
		if (ft_strncmp(line, "#cylinder", 9) == 0)
			save_cylinder(all);
		if (ft_strncmp(line, "#cone", 5) == 0)
			save_cone(all);
		if (ft_strncmp(line, "#sphere", 7) == 0)
			save_sphere(all);
		free(line);
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
