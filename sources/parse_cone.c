/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 22:25:04 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 22:25:04 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	cone_1(t_global *g)
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
}

void	cone_2(t_global *g)
{
	g->obj[g->id].rd2 = g->obj[g->id].rd * g->obj[g->id].rd;
	if (g->obj[g->id].trans)
		g->obj[g->id].simple_bright = &bright_cone;
	g->obj[g->id].simple_bright = simple_bright_cone;
	g->id++;
}

void	cone_3(t_global *g, char **data, int i)
{
	if (ft_strstr(data[i], "radius"))
		parse_int(data[i], &(g->obj[g->id].rd), 1, 100);
	if (ft_strstr(data[i], "reflection"))
		parse_double(data[i], &(g->obj[g->id].re), 100.0, 100.0);
	if (ft_strstr(data[i], "transparency"))
		parse_double(data[i], &(g->obj[g->id].trans), 100.0, 100.0);
	if (ft_strstr(data[i], "specular"))
		parse_int(data[i], &(g->obj[g->id].spec), 1, 10);
	if (ft_strstr(data[i], "soft"))
		parse_int(data[i], &(g->obj[g->id].soft), 1, 10);
}

int		parse_cone(t_global *g, char **data, int i)
{
	cone_1(g);
	while (data[i])
	{
		if (ft_strstr(data[i], "}"))
			break ;
		if (ft_strstr(data[i], "texture"))
			parse_tile(data[i], g);
		if (ft_strstr(data[i], "color"))
			parse_color(data[i], &(g->obj[g->id].color));
		if (ft_strstr(data[i], "center"))
			parse_vector(data[i], g->obj[g->id].ctr);
		if (ft_strstr(data[i], "angle"))
			parse_angle(data[i], &(g->obj[g->id].ang));
		cone_3(g, data, i);
		i++;
	}
	cone_2(g);
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
