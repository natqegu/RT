/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_8.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 22:25:09 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 22:25:09 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	sphere_1(t_global *g)
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
}

void	sphere_2(t_global *g)
{
	g->obj[g->id].rd2 = g->obj[g->id].rd * g->obj[g->id].rd;
	if (g->obj[g->id].trans)
		g->obj[g->id].simple_bright = bright_sphere;
	g->obj[g->id].simple_bright = simple_bright_sphere;
	g->id++;
}

void	sphere_3(t_global *g, char **data, int i)
{
	if (ft_strstr(data[i], "reflection"))
		parse_double(data[i], &(g->obj[g->id].re), 80.0, 100.0);
	if (ft_strstr(data[i], "transparency"))
		parse_double(data[i], &(g->obj[g->id].trans), 80.0, 100.0);
	if (ft_strstr(data[i], "specular"))
		parse_int(data[i], &(g->obj[g->id].spec), 1, 10);
	if (ft_strstr(data[i], "soft"))
		parse_int(data[i], &(g->obj[g->id].soft), 1, 10);
}

int		parse_sphere(t_global *g, char **data, int i)
{
	sphere_1(g);
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
		if (ft_strstr(data[i], "radius"))
			parse_int(data[i], &(g->obj[g->id].rd), 1, 1000);
		sphere_3(g, data, i);
		i++;
	}
	sphere_2(g);
	return (1);
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
