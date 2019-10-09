/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_points.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:01:06 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 18:01:07 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void			make_sepia(t_global *g)
{
	t_vector	c;
	int			color;
	int			j;

	g->filter_switch = 1;
	j = g->objn;
	if (j == 0)
		j = 1;
	while (j < g->argc + 1)
	{
		c = g->obj[j].color;
		g->obj[j].color.x = (((c.x * 0.393f) + (c.y * 0.769f)
												+ (c.z * 0.189f))) / 2;
		g->obj[j].color.y = (((c.x * 0.349f) + (c.y * 0.686f)
												+ (c.z * 0.168f))) / 2;
		g->obj[j].color.z = (((c.x * 0.272f) + (c.y * 0.534f)
												+ (c.z * 0.131f))) / 2;
		j++;
	}
}

int				file_height(char *filename)
{
	char		*line;
	int			height;
	int			fd;
	int			gnl;

	height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl == -1)
			return (-1);
		height++;
		free(line);
	}
	free(line);
	close(fd);
	return (height);
}

int				o_putstr(char *put, char *clean, t_vector **del)
{
	int			i;

	i = 0;
	if (clean)
		free(clean);
	if (del)
		free_points(del);
	while (*(put + i) != '\0')
	{
		write(1, put + i, 1);
		i++;
	}
	return (0);
}

int				parse_line(t_vector **a, char *s, int j, t_vector *ptdim)
{
	int			i;
	char		*save;

	save = s;
	i = 0;
	*(a + j) = (t_vector *)malloc(sizeof(t_vector) * (ft_strlen(s) + 1));
	while (*s != '\0' && i != -1)
	{
		(*(a + j) + (i))->x = i * 20;
		(*(a + j) + i)->y = j * 20;
		(*(a + j) + i)->z = ft_atoi(s) * 20;
		if (a[j][i].z > ptdim->z)
			ptdim->z = a[j][i].z;
		if (next_num(s) == -1)
		{
			return (o_putstr("File must contain only spaces and numbers\n",
			save, a));
		}
		s = s + next_num(s);
		i++;
	}
	if (j > 0 && (i * 20 != ptdim->x))
		return (o_putstr("File must contain rectangular map\n", save, a));
	ptdim->x = i * 20;
	return (1);
}

void			shift_center(t_vector **pts, t_vector *ptdim, t_global *g)
{
	int			i;
	int			j;
	int			imax;
	t_vector	bas[3];
	t_vector	rc;

	init_vector(&g->base[0], 1, 0, 0);
	init_vector(&g->base[1], 0, 1, 0);
	init_vector(&g->base[2], 0, 0, 1);
	bas[0] = scale(ptdim->x, g->base[0]);
	bas[1] = scale(ptdim->y, g->base[1]);
	bas[2] = scale(ptdim->z, g->base[2]);
	imax = ptdim->x / 20;
	rc = scale(-0.5, sum(sum(bas[0], bas[1]), bas[2]));
	j = 0;
	while (*(pts + j))
	{
		i = 0;
		while (i < imax)
		{
			pts[j][i] = sum(pts[j][i], rc);
			i++;
		}
		j++;
	}
}
