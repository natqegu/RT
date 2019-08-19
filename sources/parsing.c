/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:57:45 by vkarpova          #+#    #+#             */
/*   Updated: 2019/08/02 15:57:46 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

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
	char		*tmp;

	while (get_next_line(all->fd, &line) > 0)
	{
		if (ft_strnstr(line, "SHADOW", 20) > 0)
		{
			tmp = ft_strchr(line, 58);
			all->shadow = ft_atoi(tmp + 1);
		}
		else if (ft_strnstr(line, "CAMERA", 20) > 0)
		{
			tmp = ft_strchr(line, 58);
			save_cam(tmp + 2, all);
		}
		else if (ft_strnstr(line, "ROTATION", 20) > 0)
		{
			tmp = ft_strchr(line, 58);
			save_rotation(all, tmp + 2);
		}
		else if (ft_strnstr(line, "LIGHT", 20) > 0)
			save_light(all);
		else if (ft_strnstr(line, "OBJECTS", 20) > 0)
			save_objects(all);
		free(line);
	}
}

void		save_objects(t_all *all)
{
	char		*line;
	char		*tmp;

	miss_open_brackets(all);
	while (get_next_line(all->fd, &line) > 0)
	{
		if (ft_strnstr(line, "type", 20) > 0)
		{
			tmp = ft_strchr(line, 58);
			if (ft_strncmp(tmp + 3, "PLANE", 5) == 0)
				save_plane(all);
			else if (ft_strncmp(tmp + 3, "SPHERE", 6) == 0)
				save_sphere(all);
			else if (ft_strncmp(tmp + 3, "CONE", 4) == 0)
				save_cone(all);
			else if (ft_strncmp(tmp + 3, "CYLINDER", 8) == 0)
				save_cylinder(all);
			// else
			// {
			// 	miss_open_brackets(all);
			// 	miss_closed_brackets(all);
			// }
		}
		free(line);
	}
}

int		save_plane(t_all *all)
{
	t_list		*tmp;
	t_plane		plane;

	if (save_color(all, &(plane.color)) &&
		(save_center(all, &(plane.c)) &&
		(save_normal(all, &(plane.v))) &&
		(save_specular(all, &(plane.specular))) &&
		(save_reflect(all, &(plane.reflect))) &&
		(save_transp(all, &(plane.transp))) &&
		(save_texture(all, &(plane.tex)))))
	{
		tmp = ft_lstnew(&(plane), sizeof(t_plane));
		tmp->content_size = PLANE;
		ft_lstadd(&(all->obj), tmp);
		return (1);
	}
	ft_putendl("Incorrect info for PLANE, so it doesn't appear");
	return (0);
}

int		save_cylinder(t_all *all)
{
	t_list		*tmp;
	t_cylinder	cylinder;

	if (save_color(all, &(cylinder.color)) &&
		(save_center(all, &(cylinder.c)) &&
		(save_radius(all, &(cylinder.r)) &&
		(save_normal(all, &(cylinder.v))) &&
		(save_specular(all, &(cylinder.specular))) &&
		(save_reflect(all, &(cylinder.reflect))) &&
		(save_transp(all, &(cylinder.transp))) &&
		(save_texture(all, &(cylinder.tex))))))
	{
		tmp = ft_lstnew(&(cylinder), sizeof(t_cylinder));
		tmp->content_size = CYL;
		ft_lstadd(&(all->obj), tmp);
		return (1);
	}
	ft_putendl("Incorrect info for CYLINDER, so it doesn't appear");
	return (0);
}

int		save_sphere(t_all *all)
{
	t_list		*tmp;
	t_sphere	sphere;

	if (save_color(all, &(sphere.color)) &&
		(save_center(all, &(sphere.c)) &&
		(save_radius(all, &(sphere.r)) &&
		(save_specular(all, &(sphere.specular))) &&
		(save_reflect(all, &(sphere.reflect))) &&
		(save_transp(all, &(sphere.transp))) &&
		(save_texture(all, &(sphere.tex))))))
	{
		tmp = ft_lstnew(&sphere, sizeof(t_sphere));
		tmp->content_size = SPHERE;
		ft_lstadd(&(all->obj), tmp);
		return (1);
	}
	ft_putendl("Incorrect info for SPHERE, so it doesn't appear");
	return (0);
}

int		save_cone(t_all *all)
{
	t_list		*tmp;
	t_cone		cone;

	if (save_color(all, &(cone.color)) &&
		(save_center(all, &(cone.c)) &&
		(save_normal(all, &(cone.v))) &&
		(save_angle(all, &(cone.a))) &&
		(save_specular(all, &(cone.specular))) &&
		(save_reflect(all, &(cone.reflect))) &&
		(save_transp(all, &(cone.transp))) &&
		(save_texture(all, &(cone.tex))))) 
	{
		tmp = ft_lstnew(&cone, sizeof(t_cone));
		tmp->content_size = CONE;
		ft_lstadd(&(all->obj), tmp);
		return (1);
	}
	ft_putendl("Incorrect info for CONE, so it doesn't appear");
	return (0);
}


int		save_reflect(t_all *all, double *reflect)
{
	char		*line;
	double		tmp;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "reflection", 20) > 0))
	{
		if (num(ft_strchr(line, 58) + 2))
		{
			tmp = (double)ft_atoi(ft_strchr(line, 58) + 2);
			free(line);
			if (tmp >= 0 && tmp <= 100)
				*reflect = tmp;
			else if (tmp < 0)
				return (0);
			else
				*reflect = 100;
			return (1);
		}
	}
	return (0);
}

int		save_texture(t_all *all, double *texture)
{
	char		*line;
	double		tmp;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "texture", 20) > 0))
	{
		if (num(ft_strchr(line, 58) + 2))
		{
			tmp = (double)ft_atoi(ft_strchr(line, 58) + 2);
			free(line);
			if (tmp >= 0 && tmp <= 100)
				*texture = tmp;
			else if (tmp < 0)
				return (0);
			else
				*texture = 100;
			return (1);
		}
	}
	return (0);
}

int		save_transp(t_all *all, double *transp)
{
	char		*line;
	double		tmp;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "transparency", 20) > 0))
	{
		if (num(ft_strchr(line, 58) + 2))
		{
			tmp = (double)ft_atoi(ft_strchr(line, 58) + 2);
			free(line);
			if (tmp >= 0 && tmp <= 100)
				*transp = tmp;
			else if (tmp < 0)
				return (0);
			else
				*transp = 100;
			return (1);
		}
	}
	return (0);
}


int		save_angle(t_all *all, double *angle)
{
	char		*line;
	double		tmp;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "angle", 20) > 0))
	{
		if (num(ft_strchr(line, 58) + 2))
		{
			tmp = (double)ft_atoi(ft_strchr(line, 58) + 2);
			free(line);
			if (tmp <= 0 || tmp > 360)
				return (0);
			*angle = tan(tmp / 2);
			return (1);
		}
	}
	return (0);
}

int		save_radius(t_all *all, double *radius)
{
	char		*line;
	double		tmp;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "radius", 20) > 0))
	{
		if (num(ft_strchr(line, 58) + 2))
		{
			tmp = (double)ft_atoi(ft_strchr(line, 58) + 2);
			free(line);
			if (tmp >= 0 && tmp <= 100)
				*radius = tmp;
			else if (tmp < 0)
				return (0);
			else
				*radius = 100;
			return (1);
		}
	}
	return (0);
}


int				save_color(t_all *all, int *color)
{
	char		*line;
	
	t_vector	c;
	char		**tmp;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "color", 20) > 0))
	{
		tmp = ft_strsplit((ft_strnstr(line, "color", 20)) + 9, ',');
		free(line);
		if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
		{
			c.x = (double)ft_atoi(tmp[0]);
			c.y = (double)ft_atoi(tmp[1]);
			c.z = (double)ft_atoi(tmp[2]);
			*color = rgb_to_int(c);
			free(tmp[1]);
			free(tmp[2]);
			free(tmp);
			free(*tmp);
			return (1);
		}
	}
	return (0);
}

int				save_normal(t_all *all, t_vector *norm)
{
	char		**tmp;
	char		*line;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "normal", 20) > 0))
	{
		tmp = ft_strsplit((ft_strnstr(line, "normal", 20)) + 10, ',');
		free(line);
		if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
		{
			norm->x = (double)ft_atoi(tmp[0]);
			norm->y = (double)ft_atoi(tmp[1]);
			norm->z = (double)ft_atoi(tmp[2]);
			free(tmp[1]);
			free(tmp[2]);
			free(tmp);
			free(*tmp);
			return (1);
		}
	}
	return (0);
}


int				save_center(t_all *all, t_vector *center)
{
	char		**tmp;
	char		*line;

	

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "center", 20) > 0))
	{
		tmp = ft_strsplit((ft_strnstr(line, "center", 20)) + 10, ',');
		free(line);
		if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
		{
			center->x = (double)ft_atoi(tmp[0]);
			center->y = (double)ft_atoi(tmp[1]);
			center->z = (double)ft_atoi(tmp[2]);
			free(tmp[1]);
			free(tmp[2]);
			free(tmp);
			free(*tmp);
			return (1);
		}
	}
	return (0);
}

int		save_specular(t_all *all, double *specular)
{
	char		*line;
	double		tmp;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "specular", 20) > 0))
	{
		if (num(ft_strchr(line, 58) + 2))
		{
			tmp = (double)ft_atoi(ft_strchr(line, 58) + 2);
			free(line);
			if (tmp >= 0 && tmp <= 100)
				*specular = tmp;
			else if (tmp < 0)
				return (0);
			else
				*specular = 100;
			return (1);
		}
	}
	return (0);
}

int		save_light(t_all *all)
{
	
	t_list		*tmp;
	t_light		light;

	miss_open_brackets(all);
	if ((save_pos(all, &(light.pos)) &&
		(save_intense(all, &(light.intense)))))
	{
		all->is_light = 1;
		if (light.intense == 0)
			all->is_light = 0;
		tmp = ft_lstnew(&(light), sizeof(t_light));
		tmp->content_size = LIGHT;
		ft_lstadd(&(all->light), tmp);
		miss_closed_brackets(all);
		return (1);
	}
	ft_putendl("Incorrect info for #light, so it doesn't appear");
	return (0);
}


int		save_intense(t_all *all, double *intense)
{
	char		*line;
	double		tmp;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "intense", 20) > 0))
	{
		if (num(ft_strchr(line, ':') + 1))
		{
			tmp = (double)ft_atoi(ft_strchr(line, ':') + 1);
			free(line);
			if (tmp >= 0 && tmp <= 10)
				*intense = tmp / 10;
			else if (tmp < 0)
				return (0);
			else
				*intense = 1;
			return (1);
		}
	}
	return (0);
}

int		save_pos(t_all *all, t_vector *pos)
{
	char		*line;
	char		**tmp;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strnstr(line, "position", 20) > 0))
	{
		tmp = ft_strsplit((ft_strnstr(line, "position", 20)) + 12, ',');
		free(line);
		if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
		{
			pos->x = (double)ft_atoi(tmp[0]);
			pos->y = (double)ft_atoi(tmp[1]);
			pos->z = (double)ft_atoi(tmp[2]);
			// free(tmp[1]);
			// free(tmp[2]);
			// free(*tmp);
			// free(tmp);
			return (1);
		}
	}
	return (0);
}

void			save_cam(char *line, t_all *all)
{
	char		**tmp;

	tmp = ft_strsplit(line, ',');
	if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
	{
		all->cam.x = (double)ft_atoi(tmp[0]);
		all->cam.y = (double)ft_atoi(tmp[1]);
		all->cam.z = (double)ft_atoi(tmp[2]);
		all->is_cam = 1;
	}
	else
	{
		all->cam.x = 0;
		all->cam.y = 0;
		all->cam.z = -30;
		ft_putendl("Incorrect info for CAMERA, so I set it to (0,0,-30)");
	}
	// free(tmp[1]);
	// free(tmp[2]);
	// free(tmp);
	// free(*tmp);
}

void			save_rotation(t_all *all, char *line)
{
	char		**tmp;

	tmp = ft_strsplit(line, ',');
	if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
	{
		all->rot.x = (double)ft_atoi(tmp[0]);
		all->rot.y = (double)ft_atoi(tmp[1]);
		all->rot.z = (double)ft_atoi(tmp[2]);
	}
	else
	{
		all->rot = init_vector(0, 0, 0, 0);
		ft_putendl("Incorrect info for #rotation, so I set it to (0,0,0)");
	}
	// free(tmp[1]);
	// free(tmp[2]);
	// free(tmp);
	// free(*tmp);
}
