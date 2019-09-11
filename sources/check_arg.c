/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 20:20:33 by tpokalch          #+#    #+#             */
/*   Updated: 2019/07/03 20:22:26 by tpokalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		if (str[i] == ']' || str[i] == ',')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

int		usage(int o)
{
	if (o == 1)
		ft_putendl("Something is wrong with file, try another one");
    else
	    ft_putendl("	usage: ./RT [example_scene.json]");
    return (0);
}


void        save_cam(char *line, t_global *g)
{
    char **tmp;

    tmp = ft_strsplit(line, ',');
    if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
        init_vector(g->cam_pos, (double)ft_atoi(tmp[0]), (double)ft_atoi(tmp[1]), (double)ft_atoi(tmp[2]));
    else
    {
        init_vector(g->cam_pos, 0, 0, 0);
        ft_putendl("Incorrect info for CAMERA, so I set it to (0,0,0)");
    }
}

void        save_rotation(t_global *g, char *line)
{
    char		**tmp;

	tmp = ft_strsplit(line, ',');
	if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
        init_vector(g->angle, (double)ft_atoi(tmp[0]), (double)ft_atoi(tmp[1]), (double)ft_atoi(tmp[2]));
	else
	{
		init_vector(g->angle, 0, 0, 0);
		ft_putendl("Incorrect info for ROTATION, so I set it to (0,0,0)");
	}
}

void        save_ambient(t_global *g, int am)
{
    if (am > 255)
    {  
        g->ambient = 255;
        ft_putendl("Ambient ligth should be not bigger than 255, setted to 255");
    }
    else if (am < 0)
    {
        g->ambient = 0;
        ft_putendl("Ambient ligth should be bigger than 0, setted to 0");
    }
    else
        g->ambient = am;
}

void	miss_open_brackets(t_global *g, int fd)
{
	char		*line;

	if ((get_next_line(fd, &line) > 0) && (ft_strnstr(line, "[", 10) > 0))
	{
		if ((get_next_line(fd, &line) > 0) && (ft_strnstr(line, "{", 10) > 0))
			free(line);
	}
}

int         save_color(t_global *g, t_vector *color, int fd)
{
	char		*line;
	char		**tmp;

	if (get_next_line(fd, &line) > 0 && ft_strnstr(line, "color", 20) > 0)
	{
		tmp = ft_strsplit((ft_strnstr(line, "color", 20)) + 9, ',');
		free(line);
		if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
		{
			color->x = (double)(ft_atoi(tmp[0]) / 255);
			color->y = (double)(ft_atoi(tmp[1]) / 255);
			color->z = (double)(ft_atoi(tmp[2]) / 255);
			color->x > 1 ? color->x = 1 : color->x;
			color->x < 0 ? color->x = 0 : color->x;
			color->y > 1 ? color->y = 1 : color->y;
			color->y < 0 ? color->y = 0 : color->y;
			color->z > 1 ? color->z = 1 : color->z;
			color->z < 0 ? color->x = 0 : color->z;
			free(tmp[1]);
			free(tmp[2]);
			free(tmp);
			free(*tmp);
			printf("color\n");
			return (1);
		}
	}
	return (0);
}

int         save_center(t_global *g, t_vector *center, int fd)
{
	char		*line;
	char		**tmp;

	if (get_next_line(fd, &line) > 0 && ft_strnstr(line, "center", 20) > 0)
	{
		tmp = ft_strsplit((ft_strnstr(line, "center", 20)) + 10, ',');
		free(line);
		// printf("color.tmp[0]: %s\n", tmp[0]);
		// printf("color.tmp[1]: %s\n", tmp[1]);
		// printf("color.tmp[2]: %s\n", tmp[2]);
		// printf("color.tmp[3]: %s\n", tmp[3]);
		if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
		{
			center->x = (double)ft_atoi(tmp[0]);
			center->y = (double)ft_atoi(tmp[1]);
			center->z = (double)ft_atoi(tmp[2]);
			// printf("color.center->x: %d\n", ft_atoi(tmp[0]));
			// printf("color.center->y: %d\n", ft_atoi(tmp[1]));
			// printf("color.center->z: %d\n", ft_atoi(tmp[2]));
			free(tmp[1]);
			free(tmp[2]);
			free(tmp);
			free(*tmp);
			printf("center\n");
			return (1);
		}
	}
	return (0);
}

int         save_tile(t_global *g, int fd)
{
	char    *line;
    char	*tmp;
	char 	*tmp1;

	if ((get_next_line(fd, &line) > 0) && ft_strnstr(line, "texture", 20) > 0)
	{
		tmp = (char *)malloc(sizeof(char) * 61);
		tmp1 = (char *)malloc(sizeof(char) * ft_strlen(tmp));
		if (ft_strchr(line, 58))
		{
			tmp = ft_strchr(line, 58) + 2;
			free(line);

			//needs to check every texture we have to not have segfault
		
			tmp1 = ft_strsub(tmp, 1, ft_strlen(tmp) - 3);
			init_tile(g->id, tmp1, g->obj, g);
    		// free(g->obj[g->id].tile[0].data_ptr);
			// g->obj[g->id].tile[0].data_ptr = NULL;
			// free(tmp);
			free(tmp1);
			printf("texture\n");
			return (1);
		}
	}
	return (0);
}

int        save_radius(t_global *g, int *rd, int *rd2, int fd)
{
    char    *line;
    int     tmp;

    if (get_next_line(fd, &line) > 0 && ft_strnstr(line, "radius", 20) > 0)
	{
		if (num(ft_strchr(line, 58) + 1))
		{
			tmp = ft_atoi(ft_strchr(line, 58) + 2);
			free(line);
			if (tmp >= 0 && tmp <= 100)
				*rd = tmp;
			else if (tmp < 0)
				return (0);
			else
				*rd = 100;
			*rd2 = tmp * tmp;
			printf("radius\n");
			return (1);
		}
	}
	return (0);
}

int			save_reflection(t_global *g, double *reflection, int fd)
{
	char    *line;
    int     tmp;

    if (get_next_line(fd, &line) > 0 && ft_strnstr(line, "reflection", 20) > 0)
	{
		if (num(ft_strchr(line, 58) + 1))
		{
			tmp = ft_atoi(ft_strchr(line, 58) + 2);
			// printf("REFLECTION: %d\n", tmp);
			free(line);
			if (tmp >= 0 && tmp <= 100)
				*reflection = (double)(tmp / 100.0);
			else if (tmp < 0)
				*reflection = 0.0;
			else
				*reflection = 1.0;
			printf("REFLECTION: %f\n", *reflection);
			return (1);
		}
	}
	else
		*reflection = 0.0;
	return (0);
}

int			save_angle(t_global *g, t_vector *angle, int fd)
{
	char		*line;
	char		**tmp;

	if (get_next_line(fd, &line) > 0 && ft_strnstr(line, "angle", 20) > 0)
	{
		tmp = ft_strsplit((ft_strnstr(line, "angle", 20)) + 9, ',');
		free(line);
		if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
		{
			angle->x = (double)ft_atoi(tmp[0]);
			angle->y = (double)ft_atoi(tmp[1]);
			angle->z = (double)ft_atoi(tmp[2]);
			free(tmp[1]);
			free(tmp[2]);
			free(tmp);
			free(*tmp);
			printf("angle\n");
			return (1);
		}
	}	
	return (0);
}

int			save_point(t_global *g, t_vector *point, char *point_num, int fd)
{
	char		*line;
	char		**tmp;

	if (get_next_line(fd, &line) > 0 && ft_strnstr(line, point_num, 20) > 0)
	{
		tmp = ft_strsplit((ft_strnstr(line, point_num, 20)) + 10, ',');
		free(line);
		if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
		{
			point->x = (double)ft_atoi(tmp[0]);
			point->y = (double)ft_atoi(tmp[1]);
			point->z = (double)ft_atoi(tmp[2]);
			free(tmp[1]);
			free(tmp[2]);
			free(tmp);
			free(*tmp);
			printf("point, g->id %d\n", g->id);
			return (1);
		}
	}	
	return (0);
}

char         *save_fdf_name(t_global *g, int fd)
{
	char    *line;
    char	*tmp;

	if ((get_next_line(fd, &line) > 0) && ft_strnstr(line, "fdf-map", 20) > 0)
	{
		tmp = (char *)malloc(sizeof(char) * 61);
		
		if (ft_strchr(line, 58))
		{
			tmp = ft_strchr(line, 58) + 2;
			free(line);

			printf("texture\n");
			tmp = ft_strsub(tmp, 1, ft_strlen(tmp) - 2);
		}
		else
			tmp = "";
	}
	return (tmp);
}

int         save_complex(t_global *g, int fd)
{
	g->obj[g->id].ctr = (t_vector *)malloc(sizeof(t_vector));

	if (save_color(g, &(g->obj[g->id].color), fd) &&
    	save_center(g, g->obj[g->id].ctr, fd) &&
		save_angle(g, &(g->obj[g->id].ang), fd) &&
		save_reflection(g, &(g->obj[g->id].re), fd))
	{
		init_vector(&g->obj[g->id].base[0], 1, 0, 0);
		init_vector(&g->obj[g->id].base[1], 0, 1, 0);
		init_vector(&g->obj[g->id].base[2], 0, 0, 1);
		g->obj[g->id].pts = create_points(save_fdf_name(g, fd), &g->obj[g->id].ptdim, g);
		if (g->obj[g->id].pts)
		{
			g->obj[g->id].frame = init_frame(g->obj[g->id], g);
			g->obj[g->id].tris = create_tris(g->obj[g->id].pts, g->obj[g->id], g);
			g->obj[g->id].rd = g->obj[g->id].tris->rd - 1;
			g->obj[g->id].rd2 = g->obj[g->id].rd * g->obj[g->id].rd;
		}
		else
			exit(1);
		g->obj[g->id].id = g->id;
   		g->obj[g->id].name = "complex";
		g->obj[g->id].hit = &hit_complex;
		g->obj[g->id].bright = &bright_plane;
		g->obj[g->id].simple_bright = &simple_bright_plane;
		g->id++;
	}
    return (0);
}

int         save_tri(t_global *g, int fd)
{
	g->obj[g->id].ctr = (t_vector *)malloc(sizeof(t_vector));

	g->obj[g->id].id = g->id;
    g->obj[g->id].name = "tri";
	g->obj[g->id].hit = &hit_tri;
	g->obj[g->id].bright = &bright_plane;
	g->obj[g->id].simple_bright = &simple_bright_plane;

    save_tile(g, fd);
	save_color(g, &(g->obj[g->id].color), fd);
    save_center(g, g->obj[g->id].ctr, fd);
	save_angle(g, &(g->obj[g->id].ang), fd);
	save_radius(g, &(g->obj[g->id].rd), &(g->obj[g->id].rd2), fd);
	save_point(g, &(g->obj[g->id].bd1), "point1", fd);
	save_point(g, &(g->obj[g->id].bd2), "point2", fd);
	save_point(g, &(g->obj[g->id].bd3), "point3", fd);
	save_reflection(g, &(g->obj[g->id].re), fd);
    
	g->id++;
    return (0);
}

int         save_cylinder(t_global *g, int fd)
{
	g->obj[g->id].ctr = (t_vector *)malloc(sizeof(t_vector));

	g->obj[g->id].id = g->id;
    g->obj[g->id].name = "cylinder";
	g->obj[g->id].hit = &hit_cylinder;
	g->obj[g->id].bright = &bright_cylinder;
	g->obj[g->id].simple_bright = &simple_bright_cylinder;

	init_vector(&g->obj[g->id].base[0], 1, 0, 0);
	init_vector(&g->obj[g->id].base[1], 0, 1, 0);
	init_vector(&g->obj[g->id].base[2], 0, 0, 1);

    save_tile(g, fd);
	save_color(g, &(g->obj[g->id].color), fd);
    save_center(g, g->obj[g->id].ctr, fd);
	save_angle(g, &(g->obj[g->id].ang), fd);
	save_radius(g, &(g->obj[g->id].rd), &(g->obj[g->id].rd2), fd);
	save_reflection(g, &(g->obj[g->id].re), fd);
	g->id++;
    return (0);
}

int         save_cone(t_global *g, int fd)
{
	g->obj[g->id].ctr = (t_vector *)malloc(sizeof(t_vector));

	g->obj[g->id].id = g->id;
    g->obj[g->id].name = "cone";
	g->obj[g->id].hit = &hit_cone;
	g->obj[g->id].bright = &bright_cone;
	g->obj[g->id].simple_bright = &simple_bright_cone;

	init_vector(&g->obj[g->id].base[0], 1, 0, 0);
	init_vector(&g->obj[g->id].base[1], 0, 1, 0);
	init_vector(&g->obj[g->id].base[2], 0, 0, 1);

    save_tile(g, fd);
	save_color(g, &(g->obj[g->id].color), fd);
    save_center(g, g->obj[g->id].ctr, fd);
	save_angle(g, &(g->obj[g->id].ang), fd);
	save_radius(g, &(g->obj[g->id].rd), &(g->obj[g->id].rd2), fd);
	save_reflection(g, &(g->obj[g->id].re), fd);

	g->id++;
    return (0);
}

int         save_plane(t_global *g, int fd)
{
	g->obj[g->id].ctr = (t_vector *)malloc(sizeof(t_vector));

	g->obj[g->id].id = g->id;
    g->obj[g->id].name = "plane";
	g->obj[g->id].hit = &hit_plane;
	g->obj[g->id].bright = &bright_plane;
	g->obj[g->id].simple_bright = &simple_bright_plane;

	init_vector(&g->obj[g->id].base[0], 1, 0, 0);
	init_vector(&g->obj[g->id].base[1], 0, 1, 0);
	init_vector(&g->obj[g->id].base[2], 0, 0, 1);

    save_tile(g, fd);
	save_color(g, &(g->obj[g->id].color), fd);
    save_center(g, g->obj[g->id].ctr, fd);
	save_angle(g, &(g->obj[g->id].ang), fd);
	save_radius(g, &(g->obj[g->id].rd), &(g->obj[g->id].rd2), fd);
	save_reflection(g, &(g->obj[g->id].re), fd);

	g->id++;
    return (0);
}

int         save_sphere(t_global *g, int fd)
{
	g->obj[g->id].ctr = (t_vector *)malloc(sizeof(t_vector) * g->argc); // memory needs to be freed
    g->obj[g->id].hit = &hit_sphere;
	g->obj[g->id].bright = &bright_sphere;
	g->obj[g->id].simple_bright = &simple_bright_sphere;
	g->obj[g->id].id = g->id;
    g->obj[g->id].name = "sphere";

	init_vector(&g->obj[g->id].base[0], 1, 0, 0);
	init_vector(&g->obj[g->id].base[1], 0, 1, 0);
	init_vector(&g->obj[g->id].base[2], 0, 0, 1);

	t_vector dir[8];

	init_vector(&dir[0], 100, 100, 100);
	init_vector(&dir[1], -100, 100, 100);
	init_vector(&dir[2], 100, -100, 100);
	init_vector(&dir[3], -100, -100, 100);

	init_vector(&dir[4], 100, 100, -100);
	init_vector(&dir[5], -100, 100, -100);
	init_vector(&dir[6], 100, -100, -100);
	init_vector(&dir[7], -100, -100, -100);

	g->obj[g->id].box[0] = diff(*g->obj[g->id].ctr, dir[0]);
	g->obj[g->id].box[1] = diff(*g->obj[g->id].ctr, dir[1]);
	g->obj[g->id].box[2] = diff(*g->obj[g->id].ctr, dir[2]);
	g->obj[g->id].box[3] = diff(*g->obj[g->id].ctr, dir[3]);
	g->obj[g->id].box[4] = diff(*g->obj[g->id].ctr, dir[4]);
	g->obj[g->id].box[5] = diff(*g->obj[g->id].ctr, dir[5]);
	g->obj[g->id].box[6] = diff(*g->obj[g->id].ctr, dir[6]);
	g->obj[g->id].box[7] = diff(*g->obj[g->id].ctr, dir[7]);

	save_tile(g, fd);
	save_color(g, &(g->obj[g->id].color), fd);
	save_center(g, g->obj[g->id].ctr, fd);
	save_angle(g, &(g->obj[g->id].ang), fd);
	save_radius(g, &(g->obj[g->id].rd), &(g->obj[g->id].rd2), fd);
	save_reflection(g, &(g->obj[g->id].re), fd);

	g->id++;
    return (0);
}

void        save_objects(t_global *g, int fd)
{
    char    *line;
    char    *tmp;
    
    miss_open_brackets(g, fd);
    g->obj = (t_object *)malloc(sizeof(t_object) * (g->argc + 2));
    g->id = 1;
    while (get_next_line(fd, &line) > 0)
    {
        if (ft_strnstr(line, "name", 20) > 0)
        {
            tmp = ft_strchr(line, 58);
            if (ft_strncmp(tmp + 3, "PLANE", 5) == 0)
                save_plane(g, fd);
            if (ft_strncmp(tmp + 3, "SPHERE", 6) == 0)
                save_sphere(g, fd);
            if (ft_strncmp(tmp + 3, "CONE", 4) == 0)
                save_cone(g, fd);
            if (ft_strncmp(tmp + 3, "CYLINDER", 8) == 0)
                save_cylinder(g, fd);
            if (ft_strncmp(tmp + 3, "TRI", 3) == 0)
                save_tri(g, fd);
            if (ft_strncmp(tmp + 3, "COMPLEX", 5) == 0)
                save_complex(g, fd);
        }
        free(line);
    }
}

void		save_light(char *line, t_vector *light)
{

	char	**tmp;
	
	

			tmp = ft_strsplit((ft_strnstr(line, "position", 20)) + 11, ',');
			printf("light0[]: %s\n", tmp[0]);
			printf("light1[]: %s\n", tmp[1]);
			printf("light2[]: %s\n", tmp[2]);
			printf("light3[]: %s\n", tmp[3]);
				
			if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
			{
				light->x = (double)ft_atoi(tmp[0]);
				light->y = (double)ft_atoi(tmp[1]);
				light->z = (double)ft_atoi(tmp[2]);
				printf("color.center->x: %d\n", ft_atoi(tmp[0]));
				printf("color.center->y: %d\n", ft_atoi(tmp[1]));
				printf("color.center->z: %d\n", ft_atoi(tmp[2]));
				free(tmp[1]);
				free(tmp[2]);
				free(tmp);
				free(*tmp);
				printf("position\n");
			}
}

void        read_file(t_global *g, int fd)
{
    char    *line;
    char    *tmp;
	int i = 0;

    while (get_next_line(fd, &line) > 0)
    {
        if (ft_strnstr(line, "CAMERA", 20) > 0)
        {
            tmp = ft_strchr(line, 58);
            save_cam(tmp + 2, g);
        }
        if (ft_strnstr(line, "ROTATION", 20) > 0)
        {
            tmp = ft_strchr(line, 58);
			save_rotation(g, tmp + 2);
        }
        if (ft_strnstr(line, "AMBIENT", 20) > 0)
        {
            tmp = ft_strchr(line, 58);
            save_ambient(g, ft_atoi(tmp + 1));
        }
        if (ft_strnstr(line, "LIGHT", 20) > 0)
		{
			g->li = (t_vector *)malloc(sizeof(t_vector) * g->lights);
			
		}
		if (ft_strnstr(line, "position", 20) > 0)
			{
				save_light(line, &(g->li[i]));
				i++;
			}
        if (ft_strnstr(line, "OBJECTS", 20) > 0)
            save_objects(g, fd);
        free(line);
    }
}

int			open_file(char **argv, t_global *g)
{
	int		fd;

    fd = open(argv[1], O_RDONLY);
	if (argv[0][0] != '.' || argv[0][1] != '/') //saves from segfault when ./RT from another directory executes
		return (0);
    if (fd == -1)
        return (0);
    read_file(g, fd);
    close(fd);
	return (1);
}

int    count_objects(t_global *g, int fd)
{
    char    *line;
    char    buff[8];

    if (read(fd, buff, 8) < 8)
        return (0);
    while (get_next_line(fd, &line) > 0)
    {
		if (ft_strnstr(line, "position", 20))
			g->lights++;
        if (ft_strnstr(line, "PLANE", 25) || ft_strnstr(line, "CONE", 25) ||
            ft_strnstr(line, "CYLINDER", 25) || ft_strnstr(line, "TRI", 25) ||
            ft_strnstr(line, "SPHERE", 25) || ft_strnstr(line, "COMPLEX", 25))
            g->argc++;
        free(line);
    }
    return (g->argc);
}

int		check_arg(char **argv, int argc, t_global *g, t_vector *ctr)
{
    int fd;

	if (argc != 2)
		return (usage(0));
    fd = open(argv[1], O_RDONLY);
    if (!count_objects(g, fd))
        return (0);
    close(fd);
    if (!open_file(argv, g))
        return (0);
    printf("%d\n", g->argc);

	return (1);
}
