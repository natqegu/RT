/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:28:00 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 20:28:00 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			copy2(t_global *tcps, t_global *g)
{
	tcps->argc = g->argc;
	tcps->core = g->core;
	tcps->hits = g->hits;
	tcps->rays = g->rays;
	tcps->prim = g->prim;
	tcps->ambient = g->ambient;
	tcps->base[0] = g->base[0];
	tcps->base[1] = g->base[1];
	tcps->base[2] = g->base[2];
	tcps->line_taken = g->line_taken;
	tcps->mip_map = g->mip_map;
	tcps->recursion = g->recursion;
	tcps->lights = g->lights;
	tcps->white = g->white;
	tcps->hitli = (t_vector *)malloc(sizeof(t_vector) * g->lights);
	tcps->savehitli = (t_vector *)malloc(sizeof(t_vector) * g->lights);
	tcps->cosa = (double *)malloc(sizeof(double) * g->lights);
	tcps->recursion = (int *)malloc(sizeof(int) * (g->argc + 1));
	ft_bzero(tcps->recursion, sizeof(int) * (g->argc + 1));
}

void			copy(t_global *tcps, t_global *g)
{
	tcps->win_ptr = g->win_ptr;
	tcps->mlx_ptr = g->mlx_ptr;
	tcps->img_ptr = g->img_ptr;
	tcps->img_ptr_2 = g->img_ptr_2;
	tcps->data_ptr_2 = g->data_ptr_2;
	tcps->data_ptr = g->data_ptr;
	tcps->bpp = g->bpp;
	tcps->sz_l = g->sz_l;
	tcps->e = g->e;
	tcps->core = g->core;
	tcps->light_switch = g->light_switch;
	tcps->filter_switch = g->filter_switch;
	tcps->music = g->music;
	tcps->ray = g->ray;
	tcps->angle = g->angle;
	tcps->normal = g->normal;
	tcps->li = g->li;
	tcps->cam_pos = g->cam_pos;
	tcps->obj = g->obj;
	tcps->objn = g->objn;
	copy2(tcps, g);
}

void			copy_tcps(t_global *g)
{
	int			i;

	i = -1;
	while (++i < CORES)
	{
		copy(g->tcps[i], g);
		g->tcps[i]->core = i;
	}
}

void			init_hits(t_objecthit ***hits)
{
	int			i;
	int			j;

	i = -1;
	while (++i < HEIGHT)
		*(hits + i) = (t_objecthit **)malloc(sizeof(t_objecthit) * WIDTH + 1);
	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			*(*(hits + i) + j) = (t_objecthit *)malloc(sizeof(t_objecthit));
	}
}

void			init_rays(t_vector ****ray)
{
	int			i;
	int			j;

	(*ray) = (t_vector ***)malloc(sizeof(t_vector **) * HEIGHT + 1);
	i = -1;
	while (++i < HEIGHT)
		*(*ray + i) = (t_vector **)malloc(sizeof(t_vector) * WIDTH + 1);
	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			*(*(*ray + i) + j) = (t_vector *)malloc(sizeof(t_vector));
	}
}
