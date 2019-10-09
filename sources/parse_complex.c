/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 22:24:42 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 22:24:44 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

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
		tmp = ft_strsub(ft_strtrim(name[1]), 1,
							ft_strlen(ft_strtrim(name[1])) - 3);
	else
		tmp = ft_strsub(ft_strtrim(name[1]), 1,
							ft_strlen(ft_strtrim(name[1])) - 2);
	free(name[0]);
	free(name[1]);
	free(name);
	return (tmp);
}

void	complex_1(t_global *g)
{
	init_vector(&(g->obj[g->id].color), 1, 0, 0);
	init_vector(g->obj[g->id].ctr, 0, 0, 0);
	init_vector(&(g->obj[g->id].ang), 0, 0, 0);
	g->obj[g->id].re = 0;
	g->obj[g->id].trans = 0;
	g->obj[g->id].tile[0].data_ptr = NULL;
	g->obj[g->id].spec = 0;
	g->obj[g->id].soft = 0;
}

void	complex_2(t_global *g)
{
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
}

int		parse_complex(t_global *g, char **data, int i)
{
	complex_1(g);
	while (data[i++])
	{
		if (ft_strstr(data[i], "}"))
			break ;
		if (ft_strstr(data[i], "color"))
			parse_color(data[i], &(g->obj[g->id].color));
		if (ft_strstr(data[i], "center"))
			parse_vector(data[i], g->obj[g->id].ctr);
		if (ft_strstr(data[i], "angle"))
			parse_angle(data[i], &(g->obj[g->id].ang));
		if (ft_strstr(data[i], "reflection"))
			parse_double(data[i], &(g->obj[g->id].re), 100.0, 100.0);
		if (ft_strstr(data[i], "3ds-map"))
			g->obj[g->id].pts = create_points(save_fdf_name(g, data[i]),
												&g->obj[g->id].ptdim, g);
		if (ft_strstr(data[i], "transparency"))
			parse_double(data[i], &(g->obj[g->id].trans), 100.0, 100.0);
		if (ft_strstr(data[i], "specular"))
			parse_int(data[i], &(g->obj[g->id].spec), 1, 10);
		if (ft_strstr(data[i], "soft"))
			parse_int(data[i], &(g->obj[g->id].soft), 1, 10);
	}
	complex_2(g);
	return (0);
}
