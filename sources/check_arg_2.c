/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 22:16:50 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 22:16:51 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			parse_angle(char *line, t_vector *vector)
{
	char	**name;
	char	**tmp;
	char	*test;
	char	*test1;
	char	*test2;
	char	*test3;

	name = ft_strsplit(line, ':');
	test3 = ft_strtrim(name[1]);
	tmp = ft_strsplit((test3), ',');
	test = ft_strtrim(tmp[0] + 1);
	test1 = ft_strtrim(tmp[1]);
	test2 = ft_strtrim(tmp[2]);
	if (num(tmp[0] + 1) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
	{
		vector->x = (double)ft_atoi(test) / 57.2958;
		vector->y = (double)ft_atoi(test1) / 57.2958;
		vector->z = (double)ft_atoi(test2) / 57.2958;
		free_n(13, test, test1, test2, test3, tmp[0], tmp[1], tmp[2], tmp[3],
								tmp, name[0], name[1], name[2], name);
		return (1);
	}
	free_n(9, tmp[0], tmp[1], tmp[2], tmp[3], tmp, name[0], name[1],
											name[2], name);
	return (0);
}

int			parse_int(char *line, int *number, int divisor, int max)
{
	char	*test;
	char	**name;
	int		result;

	name = ft_strsplit(line, ':');
	if (!name[0] || !name[1] || name[2])
	{
		free(name[0]);
		free(name[1]);
		free(name);
		return (0);
	}
	test = ft_strtrim(name[1]);
	result = ft_atoi(test);
	free(test);
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

int			parse_double(char *line, double *number, double divisor, double max)
{
	char	**name;
	double	result;
	char	*test;

	name = ft_strsplit(line, ':');
	if (!name[0] || !name[1] || name[2])
		return (0);
	test = ft_strtrim(name[1]);
	result = ft_atoi(test);
	free(test);
	if (result > max)
		*number = max / divisor;
	else if (result < 0)
		*number = 0.0;
	else
		*number = result / divisor;
	free(name[0]);
	free(name[1]);
	free(name[2]);
	free(name);
	return (1);
}

void		parse_init_tile_2(t_global *g, int num)
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

void		parse_init_tile(t_global *g, int num)
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
