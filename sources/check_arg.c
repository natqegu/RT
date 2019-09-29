/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 07:52:24 by nnovikov          #+#    #+#             */
/*   Updated: 2019/09/29 07:52:36 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		num(char *str)
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

int		parse_color(char *line, t_vector *vector)
{
	char	**name;
	char	**tmp;

	name = ft_strsplit(line, ':');
	tmp = ft_strsplit(name[1], ',');		
	if (num(tmp[0] + 1) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
	{
		vector->x = (double)(ft_atoi(ft_strtrim(tmp[0] + 1)) / 255);
		vector->y = (double)(ft_atoi(ft_strtrim(tmp[1])) / 255);
		vector->z = (double)(ft_atoi(ft_strtrim(tmp[2])) / 255);
		free(tmp[1]);
		free(tmp[2]);
		free(tmp);
		return (1);
	}

	free(name[0]);
	free(name[1]);
	free(name);
	return (0);
}

int		parse_vector(char *line, t_vector *vector)
{
	char	**name;
	char	**tmp;

	name = ft_strsplit(line, ':');
	tmp = ft_strsplit(ft_strtrim(name[1]), ',');	
	if (num(tmp[0] + 1) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
	{
		vector->x = (double)ft_atoi(ft_strtrim(tmp[0] + 1));
		vector->y = (double)ft_atoi(ft_strtrim(tmp[1]));
		vector->z = (double)ft_atoi(ft_strtrim(tmp[2]));
		free(tmp[1]);
		free(tmp[2]);
		free(tmp);
		return (1);
	}
	free(name[0]);
	free(name[1]);
	free(name);
	return (0);
}

int		parse_angle(char *line, t_vector *vector)
{
	char	**name;
	char	**tmp;

	name = ft_strsplit(line, ':');
	tmp = ft_strsplit(ft_strtrim(name[1]), ',');
	if (num(tmp[0] + 1) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
	{
		vector->x = (double)ft_atoi(ft_strtrim(tmp[0] + 1)) / 57.2958;
		vector->y = (double)ft_atoi(ft_strtrim(tmp[1])) / 57.2958;
		vector->z = (double)ft_atoi(ft_strtrim(tmp[2])) / 57.2958;
		free(tmp[1]);
		free(tmp[2]);
		free(tmp);
		return (1);
	}
	free(name[0]);
	free(name[1]);
	free(name);
	return (0);
}

int		parse_int(char *line, int *number, int divisor, int max)
{
	char	**name;
	int		result;

	name = ft_strsplit(line, ':');
	if (!name[0] || !name[1] || name[2])
		return (0);
	result = ft_atoi(ft_strtrim(name[1]));
	if (result > max)
        *number = max * divisor;
    else if (result < 0)
        *number = 0;
    else
        *number = result * divisor;
	free(name[0]);
	free(name[1]);
	free(name);
	return (1);
}

int		parse_double(char *line, double *number, double divisor, double max)
{
	char	**name;
	double	result;

	name = ft_strsplit(line, ':');
	if (!name[0] || !name[1] || name[2])
		return (0);
	result = ft_atoi(ft_strtrim(name[1]));
	if (result > max)
        *number = max / divisor;
    else if (result < 0)
        *number = 0.0;
    else
        *number = result / divisor;
	free(name[0]);
	free(name[1]);
	free(name);
	return (1);
}

void	parse_init_tile_2(t_global *g, int num)
{
	if (num == 11)
		init_tile(g->id, "./tiles/blank.xpm", g->obj, g);
	if (num == 12)
		init_tile(g->id, "./tiles/helper.xpm", g->obj, g);
	if (num == 13)
		init_tile(g->id, "./tiles/space.xpm", g->obj, g);
	if (num == 14)
		init_tile(g->id, "./tiles/space1.xpm", g->obj, g);
	if (num == 15)
		init_tile(g->id, "./tiles/brick.xpm", g->obj, g);
}

void	parse_init_tile(t_global *g, int num)
{
	if (num == 1)
		init_tile(g->id, "./tiles/moon.xpm", g->obj, g);
	if (num == 2)
		init_tile(g->id, "./tiles/sun.xpm", g->obj, g);
	if (num == 3)
		init_tile(g->id, "./tiles/mercury.xpm", g->obj, g);
	if (num == 4)
		init_tile(g->id, "./tiles/venus.xpm", g->obj, g);
	if (num == 5)
		init_tile(g->id, "./tiles/earth.xpm", g->obj, g);
	if (num == 6)
		init_tile(g->id, "./tiles/mars.xpm", g->obj, g);
	if (num == 7)
		init_tile(g->id, "./tiles/jupiter.xpm", g->obj, g);
	if (num == 8)
		init_tile(g->id, "./tiles/saturn.xpm", g->obj, g);
	if (num == 9)
		init_tile(g->id, "./tiles/uranus.xpm", g->obj, g);
	if (num == 10)
		init_tile(g->id, "./tiles/neptune.xpm", g->obj, g);
}

int		parse_tile(char *line, t_global *g)
{
	char	**name;
	char	*tmp;
	int		num;

	name = ft_strsplit(line, ':');
	if (!name[0] || !name[1] || name[2])
		return (0);
	num = ft_atoi(name[1]);
	parse_init_tile(g, num);
	parse_init_tile_2(g, num);
	free(name[0]);
	free(name[1]);
	free(name);
	return (1);
}

char	*save_fdf_name(t_global *g, char *line)
{
    char	*tmp;
	char	**name;

	name = ft_strsplit(line, ':');
	if (!name[0] || !name[1] || name[2])
		return ("");
	tmp = (char *)malloc(sizeof(char) * ft_strlen(name[1]));
	if (ft_strstr(line, ","))
		tmp = ft_strsub(ft_strtrim(name[1]), 1, ft_strlen(ft_strtrim(name[1])) - 3);
	else
		tmp = ft_strsub(ft_strtrim(name[1]), 1, ft_strlen(ft_strtrim(name[1])) - 2);
	printf("tmp: %s\n", tmp);
	free(name[0]);
	free(name[1]);
	free(name);
	return (tmp);
}

int		parse_complex(t_global *g, char **data, int i)
{
	init_vector(&(g->obj[g->id].color), 1, 0, 0);
	init_vector(g->obj[g->id].ctr, 0, 0, 0);
	init_vector(&(g->obj[g->id].ang), 0, 0, 0);
	g->obj[g->id].re = 0;
	g->obj[g->id].trans = 0;
	g->obj[g->id].tile[0].data_ptr = NULL;
	g->obj[g->id].spec = 0;
	g->obj[g->id].soft = 0;
	while (data[i])
	{
		if (ft_strstr(data[i], "}"))
			break;
		if (ft_strstr(data[i], "color"))
			parse_color(data[i], &(g->obj[g->id].color));
		if (ft_strstr(data[i], "center"))
			parse_vector(data[i], g->obj[g->id].ctr);
		if (ft_strstr(data[i], "angle"))
			parse_angle(data[i], &(g->obj[g->id].ang));
		if (ft_strstr(data[i], "reflection"))
			parse_double(data[i], &(g->obj[g->id].re), 80.0, 100.0);
		if (ft_strstr(data[i], "3ds-map"))
			g->obj[g->id].pts = create_points(save_fdf_name(g, data[i]), &g->obj[g->id].ptdim, g);
		if (ft_strstr(data[i], "transparency"))
			parse_double(data[i], &(g->obj[g->id].trans), 80.0, 100.0);
		if (ft_strstr(data[i], "specular"))
			parse_int(data[i], &(g->obj[g->id].spec), 1, 10);
		if (ft_strstr(data[i], "soft"))
			parse_int(data[i], &(g->obj[g->id].soft), 1, 10);
		i++;
	}
	init_vector(&g->obj[g->id].base[0], 1, 0, 0);
	init_vector(&g->obj[g->id].base[1], 0, 1, 0);
	init_vector(&g->obj[g->id].base[2], 0, 0, 1);
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
    return (0);
}

int		parse_tri(t_global *g, char **data, int i)
{
	g->obj[g->id].id = g->id;
    g->obj[g->id].name = "tri";
	g->obj[g->id].hit = &hit_tri;
	g->obj[g->id].bright = &bright_tri;
	g->obj[g->id].simple_bright = &simple_bright_tri;
	init_vector(&(g->obj[g->id].color), 1, 0, 0);
	init_vector(g->obj[g->id].ctr, 0, 0, 0);
	init_vector(&(g->obj[g->id].ang), 0, 0, 0);
	init_vector(&(g->obj[g->id].bd1), 0, 0, 0);
	init_vector(&(g->obj[g->id].bd2), 0, 0, 0);
	init_vector(&(g->obj[g->id].bd3), 0, 0, 0);
	g->obj[g->id].rd = 10;
	g->obj[g->id].re = 0;
	g->obj[g->id].trans = 0;
	g->obj[g->id].spec = 0;	
	g->obj[g->id].tile[0].data_ptr = NULL;
	g->obj[g->id].soft = 0;

	while (data[i])
	{
		if (ft_strstr(data[i], "}"))
			break;
		if (ft_strstr(data[i], "texture"))
			parse_tile(data[i], g);
		if (ft_strstr(data[i], "color"))
			parse_color(data[i], &(g->obj[g->id].color));
		if (ft_strstr(data[i], "center"))
			parse_vector(data[i], g->obj[g->id].ctr);
		if (ft_strstr(data[i], "angle"))
			parse_angle(data[i], &(g->obj[g->id].ang));
		if (ft_strstr(data[i], "radius"))
			parse_int(data[i], &(g->obj[g->id].rd), 1, 1000);
		if (ft_strstr(data[i], "reflection"))
			parse_double(data[i], &(g->obj[g->id].re), 80.0, 100.0);
		if (ft_strstr(data[i], "point1"))
			parse_vector(data[i], &(g->obj[g->id].bd1));
		if (ft_strstr(data[i], "point2"))
			parse_vector(data[i], &(g->obj[g->id].bd2));
		if (ft_strstr(data[i], "point3"))
			parse_vector(data[i], &(g->obj[g->id].bd3));
		if (ft_strstr(data[i], "transparency"))
			parse_double(data[i], &(g->obj[g->id].trans), 80.0, 100.0);
		if (ft_strstr(data[i], "specular"))
			parse_int(data[i], &(g->obj[g->id].spec), 1, 10);
		if (ft_strstr(data[i], "soft"))
			parse_int(data[i], &(g->obj[g->id].soft), 1, 10);
		i++;
	}
	g->obj[g->id].rd2 = g->obj[g->id].rd * g->obj[g->id].rd;
	g->obj[g->id].base[1] = norm(cross(diff(g->obj[g->id].bd1, g->obj[g->id].bd3), diff(g->obj[g->id].bd2, g->obj[g->id].bd3)));
	g->id++;
    return (0);
}

int		parse_plane(t_global *g, char **data, int i)
{
	g->obj[g->id].id = g->id;
    g->obj[g->id].name = "plane";
	g->obj[g->id].hit = &hit_plane;
	g->obj[g->id].bright = &bright_plane;
	g->obj[g->id].simple_bright = &simple_bright_plane;
	init_vector(&(g->obj[g->id].color), 1, 0, 0);
	init_vector(g->obj[g->id].ctr, 0, 0, 0);
	init_vector(&(g->obj[g->id].ang), 0, 0, 0);
	g->obj[g->id].rd = 40;
	g->obj[g->id].re = 0;
	g->obj[g->id].trans = 0;
	g->obj[g->id].spec = 0;
	g->obj[g->id].tile[0].data_ptr = NULL;
	init_vector(&g->obj[g->id].base[0], 1, 0, 0);
	init_vector(&g->obj[g->id].base[1], 0, 1, 0);
	init_vector(&g->obj[g->id].base[2], 0, 0, 1);
	g->obj[g->id].soft = 0;

	while (data[i])
	{
		if (ft_strstr(data[i], "}"))
			break;
		if (ft_strstr(data[i], "texture"))
			parse_tile(data[i], g);
		if (ft_strstr(data[i], "color"))
			parse_color(data[i], &(g->obj[g->id].color));
		if (ft_strstr(data[i], "center"))
			parse_vector(data[i], g->obj[g->id].ctr);
		if (ft_strstr(data[i], "angle"))
			parse_angle(data[i], &(g->obj[g->id].ang));
		if (ft_strstr(data[i], "radius"))
			parse_int(data[i], &(g->obj[g->id].rd), 1, 1000);
		if (ft_strstr(data[i], "reflection"))
			parse_double(data[i], &(g->obj[g->id].re), 80.0, 100.0);
		if (ft_strstr(data[i], "transparency"))
			parse_double(data[i], &(g->obj[g->id].trans), 80.0, 100.0);
		if (ft_strstr(data[i], "specular"))
			parse_int(data[i], &(g->obj[g->id].spec), 1, 10);
		if (ft_strstr(data[i], "soft"))
			parse_int(data[i], &(g->obj[g->id].soft), 1, 10);
		i++;
	}
	g->obj[g->id].rd2 = g->obj[g->id].rd * g->obj[g->id].rd;
	if (g->obj[g->id].trans)
		g->obj[g->id].simple_bright = bright_plane;
	g->id++;
    return (0);
}

int		parse_cylinder(t_global *g, char **data, int i)
{
	g->obj[g->id].id = g->id;
    g->obj[g->id].name = "cylinder";
	g->obj[g->id].hit = &hit_cylinder;
	g->obj[g->id].bright = &bright_cylinder;
	g->obj[g->id].simple_bright = &simple_bright_cylinder;
	init_vector(&(g->obj[g->id].color), 1, 0, 0);
	init_vector(g->obj[g->id].ctr, 0, 0, 0);
	init_vector(&(g->obj[g->id].ang), 0, 0, 0);
	g->obj[g->id].rd = 40;
	g->obj[g->id].re = 0;
	g->obj[g->id].spec = 0;
	g->obj[g->id].trans = 0;
	g->obj[g->id].tile[0].data_ptr = NULL;
	g->obj[g->id].soft = 0;
	init_vector(&g->obj[g->id].base[0], 1, 0, 0);
	init_vector(&g->obj[g->id].base[1], 0, 1, 0);
	init_vector(&g->obj[g->id].base[2], 0, 0, 1);

	while (data[i])
	{
		if (ft_strstr(data[i], "}"))
			break;
		if (ft_strstr(data[i], "texture"))
			parse_tile(data[i], g);
		if (ft_strstr(data[i], "color"))
			parse_color(data[i], &(g->obj[g->id].color));
		if (ft_strstr(data[i], "center"))
			parse_vector(data[i], g->obj[g->id].ctr);
		if (ft_strstr(data[i], "angle"))
			parse_angle(data[i], &(g->obj[g->id].ang));
		if (ft_strstr(data[i], "radius"))
			parse_int(data[i], &(g->obj[g->id].rd), 1, 1000);
		if (ft_strstr(data[i], "reflection"))
			parse_double(data[i], &(g->obj[g->id].re), 80.0, 100.0);
		if (ft_strstr(data[i], "transparency"))
			parse_double(data[i], &(g->obj[g->id].trans), 80.0, 100.0);
		if (ft_strstr(data[i], "specular"))
			parse_int(data[i], &(g->obj[g->id].spec), 1, 10);
		if (ft_strstr(data[i], "soft"))
			parse_int(data[i], &(g->obj[g->id].soft), 1, 10);
		i++;
	}
	g->obj[g->id].rd2 = g->obj[g->id].rd * g->obj[g->id].rd;
	if (g->obj[g->id].trans)
		g->obj[g->id].simple_bright = bright_cylinder;
	g->obj[g->id].simple_bright = simple_bright_cylinder;
	g->id++;
    return (0);
}

int		parse_cone(t_global *g, char **data, int i)
{
	g->obj[g->id].id = g->id;
    g->obj[g->id].name = "cone";
	g->obj[g->id].hit = &hit_cone;
	g->obj[g->id].bright = &bright_cone;
	g->obj[g->id].simple_bright = &simple_bright_cone;
	init_vector(&(g->obj[g->id].color), 1, 1, 1);
	init_vector(g->obj[g->id].ctr, 0, 0, 400);
	init_vector(&(g->obj[g->id].ang), 0, 0, 0);
	g->obj[g->id].rd = 1;
	g->obj[g->id].re = 0;
	g->obj[g->id].trans = 0;
	g->obj[g->id].spec = 0;
	g->obj[g->id].tile[0].data_ptr = NULL;
	init_vector(&g->obj[g->id].base[0], 1, 0, 0);
	init_vector(&g->obj[g->id].base[1], 0, 1, 0);
	init_vector(&g->obj[g->id].base[2], 0, 0, 1);
	g->obj[g->id].soft = 0;

	while (data[i])
	{
		if (ft_strstr(data[i], "}"))
			break;
		if (ft_strstr(data[i], "texture"))
			parse_tile(data[i], g);
		if (ft_strstr(data[i], "color"))
			parse_color(data[i], &(g->obj[g->id].color));
		if (ft_strstr(data[i], "center"))
			parse_vector(data[i], g->obj[g->id].ctr);
		if (ft_strstr(data[i], "angle"))
			parse_angle(data[i], &(g->obj[g->id].ang));
		if (ft_strstr(data[i], "radius"))
			parse_int(data[i], &(g->obj[g->id].rd), 1, 100);
		if (ft_strstr(data[i], "reflection"))
			parse_double(data[i], &(g->obj[g->id].re), 80.0, 100.0);
		if (ft_strstr(data[i], "transparency"))
			parse_double(data[i], &(g->obj[g->id].trans), 80.0, 100.0);
		if (ft_strstr(data[i], "specular"))
			parse_int(data[i], &(g->obj[g->id].spec), 1, 10);
		if (ft_strstr(data[i], "soft"))
			parse_int(data[i], &(g->obj[g->id].soft), 1, 10);
		i++;
	}
	g->obj[g->id].rd2 = g->obj[g->id].rd * g->obj[g->id].rd;
	if (g->obj[g->id].trans)
		g->obj[g->id].simple_bright = &bright_cone;
	g->obj[g->id].simple_bright = simple_bright_cone;
	g->id++;
    return (1);
}

int		parse_sphere(t_global *g, char **data, int i)
{
	g->obj[g->id].id = g->id;
    g->obj[g->id].name = "sphere";
	g->obj[g->id].hit = &hit_sphere;
	g->obj[g->id].bright = &bright_sphere;
	g->obj[g->id].simple_bright = &simple_bright_sphere;
	init_vector(&(g->obj[g->id].color), 1, 0, 0);
	init_vector(g->obj[g->id].ctr, 0, 0, 600);
	init_vector(&(g->obj[g->id].ang), 0, 0, 0);
	g->obj[g->id].rd = 40;
	g->obj[g->id].re = 0;
	g->obj[g->id].trans = 0;
	g->obj[g->id].spec = 0;
	init_vector(&g->obj[g->id].base[0], 1, 0, 0);
	init_vector(&g->obj[g->id].base[1], 0, 1, 0);
	init_vector(&g->obj[g->id].base[2], 0, 0, 1);
	g->obj[g->id].soft = 0;
	g->obj[g->id].tile[0].data_ptr = NULL;

	while (data[i])
	{
		if (ft_strstr(data[i], "}"))
			break;
		if (ft_strstr(data[i], "texture"))
			parse_tile(data[i], g);
		if (ft_strstr(data[i], "color"))
			parse_color(data[i], &(g->obj[g->id].color));
		if (ft_strstr(data[i], "center"))
			parse_vector(data[i], g->obj[g->id].ctr);
		if (ft_strstr(data[i], "angle"))
			parse_angle(data[i], &(g->obj[g->id].ang));
		if (ft_strstr(data[i], "radius"))
			parse_int(data[i], &(g->obj[g->id].rd), 1, 1000);
		if (ft_strstr(data[i], "reflection"))
			parse_double(data[i], &(g->obj[g->id].re), 80.0, 100.0);
		if (ft_strstr(data[i], "transparency"))
			parse_double(data[i], &(g->obj[g->id].trans), 80.0, 100.0);
		if (ft_strstr(data[i], "specular"))
			parse_int(data[i], &(g->obj[g->id].spec), 1, 10);
		if (ft_strstr(data[i], "soft"))
			parse_int(data[i], &(g->obj[g->id].soft), 1, 10);
		i++;
	}
	g->obj[g->id].rd2 = g->obj[g->id].rd * g->obj[g->id].rd;
	if (g->obj[g->id].trans)
		g->obj[g->id].simple_bright = bright_sphere;
	g->obj[g->id].simple_bright = simple_bright_sphere;
	g->id++;
	return (1);
}

int		parse_objects(t_global *g, char **data, int i, int lines)
{
	int lig;

	lig = -1;
	g->id = 1;
	g->li = (t_vector *)malloc(sizeof(t_vector) * (g->lights + 1));
	g->obj = (t_object *)malloc(sizeof(t_object) * (g->argc + 2));
	g->liz = (double *)malloc(sizeof(t_vector) * (g->lights + 1));
	while (++lig <= g->argc)
		g->obj[lig].ctr = (t_vector *)malloc(sizeof(t_vector));
	lig = 0;
	
	while (i < lines)
	{
		if (ft_strstr(data[i], "LIGHT"))
		{
			parse_vector(data[i + 2], &(g->li[lig]));
			g->liz[lig] = g->li[lig].z;
			lig++;
		}
		if (ft_strstr(data[i], "SPHERE"))
			parse_sphere(g, data, i + 1);
		if (ft_strstr(data[i], "CONE"))
			parse_cone(g, data, i + 1);
		if (ft_strstr(data[i], "CYLINDER"))
			parse_cylinder(g, data, i + 1);
		if (ft_strstr(data[i], "COMPLEX"))
			parse_complex(g, data, i + 1);
		if (ft_strstr(data[i], "TRI"))
			parse_tri(g, data, i + 1);
		if (ft_strstr(data[i], "PLANE"))
			parse_plane(g, data, i + 1);
		i++;
	}
	if (!g->lights)
	{
		init_vector(&(g->li[lig]), g->cam_pos->x, g->cam_pos->y, g->cam_pos->z);
		g->liz[lig] = g->li[lig].z;
		g->lights = 1;
	}
	return (0);
}

int		parse_file(t_global *g, char **data, int lines)
{
    char    *tmp;
	int i = 0;

	g->ambient = (int *)malloc(sizeof(int));
	*g->ambient = 18;
	if (ft_strcmp("{", data[0]) && ft_strcmp("}", data[lines - 1]))
		return (0);
	while (i < lines)
	{
		if (ft_strstr(data[i], "ROTATION"))
			parse_vector(data[i], g->angle);
		if (ft_strstr(data[i], "CAMERA"))
			parse_vector(data[i], g->cam_pos);
		if (ft_strstr(data[i], "AMBIENT"))
			parse_int(data[i], g->ambient, 1, 100);
		if (ft_strstr(data[i], "OBJECTS"))
			parse_objects(g, data, i, lines);
		i++;
	}
	*g->normal = rotate(*g->normal, *g->angle);
    return (1);
}

void	ft_strjoin_free(char *s1, char *s2, int type)
{
	if (type == 'l')
		free(s1);
	else if (type == 'r')
		free(s2);
	else if (type == 'b')
	{
		free(s1);
		free(s2);
	}
}

char	*ft_strjoin_fake(char *s1, char *s2, char type)
{
	char	*n;
	int		i[2];

	i[0] = 0;
	while (s1[i[0]])
		i[0]++;
	i[1] = 0;
	while (s2[i[1]])
		i[1]++;
	n = (char *)malloc(sizeof(char) * (i[0] + i[1] + 1));
	i[0] = 0;
	while (s1[i[0]])
	{
		n[i[0]] = s1[i[0]];
		i[0]++;
	}
	i[1] = 0;
	while (s2[i[1]])
	{
		n[i[0] + i[1]] = s2[i[1]];
		i[1]++;
	}
	ft_strjoin_free(s1, s2, type);
	n[i[0] + i[1]] = '\0';
	return (n);
}

int		ft_linelen(char *buf, int k)
{
	int	len;

	len = 0;
	while (buf[k] != '\n' && buf[k] != '\0')
	{
		k++;
		len++;
	}
	return (++len);
}

char	**get_scene(char *buf, int lines)
{
	int		i;
	int		k;
	int		j;
	char	**data;

	k = 0;
	j = 0;
	if (!buf)
		return (0);
	if (!(data = (char **)malloc(sizeof(char *) * (lines + 1))))
		return (0);
	while (buf[k] != '\0' && j < lines)
	{
		i = 0;
		if (!(data[j] = ft_strnew(ft_linelen(buf, k))))
			return (0);
		while (buf[k] != '\n' && buf[k] != '\0')
			data[j][i++] = buf[k++];
		data[j][i] = '\0';
		k++;
		j++;
	}
	ft_strdel(&buf);
	return (data);
}

int		open_file(char **argv, t_global *g)
{
	int		fd;
	char	*line;
	char	*buf;
	int		lines;
	char	**data;

    fd = open(argv[1], O_RDONLY);
	lines = 0;
	buf = ft_strnew(1);
	if (argv[0][0] != '.' || argv[0][1] != '/')
		return (0);
    if (fd == -1)
        return (0);
	while (get_next_line(fd, &line))
	{
		buf = ft_strjoin_fake(buf, ft_strjoin_fake(
					ft_strtrim(line), "\n", 'l'), 'b');
		free(line);
		lines++;
	}
	if (!(data = get_scene(buf, lines)))
		data = NULL;
    parse_file(g, data, lines);
    close(fd);
	return (1);
}

int    count_objects(t_global *g, int fd)
{
    char    *line;
    char    buff[8];

	g->lights = 0;
    if (read(fd, buff, 8) < 8)
        return (0);
    while (get_next_line(fd, &line) > 0)
    {
        if (ft_strnstr(line, "PLANE", 25) || ft_strnstr(line, "CONE", 25) ||
            ft_strnstr(line, "CYLINDER", 25) || ft_strnstr(line, "TRI", 25) ||
            ft_strnstr(line, "SPHERE", 25) || ft_strnstr(line, "COMPLEX", 25))
            g->argc++;
		if (ft_strnstr(line, "LIGHT", 25))
			g->lights++;
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
	if (fd == -1 || (argv[1][0] == '.' && argv[1][1] == '/')
									|| !count_objects(g, fd))
	{
		usage(1);
		return (0);
	}
    close(fd);
    if (!open_file(argv, g))
	{
		usage(1);
        return (0);
	}
	ginit(g);
	return (1);
}
