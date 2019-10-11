/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:11:14 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/30 00:11:15 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		ginit(t_global *g)
{
	int			i;
	t_objecthit ***hits;

	g->ray->z = round(WIDTH / (double)2000 * 1600);
	g->mip_map = 0;
	init_vector(&g->fifteen, 0, 0, 15);
	init_vector(&g->base[0], 1, 0, 0);
	init_vector(&g->base[1], 0, 1, 0);
	init_vector(&g->base[2], 0, 0, 1);
	init_vector(&g->white, 1, 1, 1);
	g->light_switch = 0;
	g->filter_switch = 0;
	g->music = 0;
	g->objn = 0;
	g->prim = 0;
	(hits) = (t_objecthit ***)malloc(sizeof(t_objecthit **) * HEIGHT + 1);
	init_hits(hits);
	g->hits = hits;
	init_rays(&g->rays);
	g->line_taken = (int *)malloc(sizeof(int) * HEIGHT);
	ft_bzero(g->line_taken, 4 * WIDTH);
	g->recursion = 0;
	i = -1;
	while (++i < CORES)
		g->tcps[i] = (t_global *)malloc(sizeof(t_global));
}

void		stretch(int *a, int d, int h)
{
	int			i;
	int			j;

	i = d / 2 - 1;
	j = h / 2 - 1;
	while (j >= 0)
	{
		i = d / 2 - 1;
		while (i >= 0)
		{
			*(a + d * 2 * j + 2 * i) = *(a + d * j + i);
			*(a + d * 2 * j + 2 * i + 1) = *(a + d * j + i);
			*(a + d * (2 * j + 1) + 2 * i) = *(a + d * j + i);
			*(a + d * (2 * j + 1) + 2 * i + 1) = *(a + d * j + i);
			i--;
		}
		j--;
	}
}

void		init_tile(int i, char *tile, t_object *q, t_global *g)
{
	int			k;

	k = 0;
	q[i].tile[0].ptr = mlx_xpm_file_to_image(g->mlx_ptr,
						tile, &q[i].tile[0].w, &q[i].tile[0].h);
	q[i].tile[0].data_ptr = (int *)mlx_get_data_addr(q[i].tile[0].ptr,
				&q[i].tile[0].bpp, &q[i].tile[0].sz_l, &q[i].tile[0].e);
	q[i].tile[0].w2 = q[i].tile[0].w / 2;
	q[i].tile[0].h2 = q[i].tile[0].h / 2;
}

t_vector	**create_points(char *filename, t_vector *ptdim, t_global *g)
{
	t_vector	**ret;
	char		*line;
	int			height;
	int			fd;
	int			j;

	j = 0;
	height = file_height(filename);
	if (height == -1)
		return (NULL);
	ret = initialize_points(height + 1);
	fd = open(filename, O_RDONLY);
	ptdim->z = 0;
	while (j < height)
	{
		if (get_next_line(fd, &line) == -1)
			return (NULL);
		if (!(parse_line(ret, line, j, ptdim)))
			return (NULL);
		free(line);
		j++;
	}
	ptdim->y = height * 20;
	shift_center(ret, ptdim, g);
	return (ret);
}
