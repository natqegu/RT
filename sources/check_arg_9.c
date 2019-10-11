/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_9.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 22:25:13 by vkarpova          #+#    #+#             */
/*   Updated: 2019/10/10 19:24:06 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		objects_1(t_global *g)
{
	int		lig;

	lig = -1;
	g->id = 1;
	g->li = (t_vector *)malloc(sizeof(t_vector) * (g->lights + 1));
	g->obj = (t_object *)malloc(sizeof(t_object) * (g->argc + 2));
	g->liz = (double *)malloc(sizeof(t_vector) * (g->lights + 1));
	while (++lig <= g->argc)
		g->obj[lig].ctr = (t_vector *)malloc(sizeof(t_vector));
}

void		objects_2(t_global *g, char **data, int i)
{
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
}

int			parse_objects(t_global *g, char **data, int i, int lines)
{
	int		lig;

	lig = 0;
	objects_1(g);
	while (i < lines)
	{
		if (ft_strstr(data[i], "LIGHT"))
		{
			parse_vector(data[i + 2], &(g->li[lig]));
			g->liz[lig] = g->li[lig].z;
			lig++;
		}
		objects_2(g, data, i);
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

int			ft_linelen(char *buf, int k)
{
	int		len;

	len = 0;
	while (buf[k] != '\n' && buf[k] != '\0')
	{
		k++;
		len++;
	}
	return (++len);
}

int			parse_file(t_global *g, char **data, int lines)
{
	int		i;

	i = 0;
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
