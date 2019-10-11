/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:18:20 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/30 00:18:21 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		mouse_move(int x, int y, void *param)
{
	t_global	*g;
	t_vector	p;
	double		block;

	g = param;
	if (g->light_switch >= 1 && g->light_switch <= g->lights)
	{
		block = g->liz[g->light_switch - 1] / g->ray->z;
		p.x = (-WIDTH_2 + x) * block;
		p.y = (-y + HEIGHT_2) * block;
		p.z = g->liz[g->light_switch - 1];
		g->li[g->light_switch - 1] = sum(*g->cam_pos, rotate(p, *g->angle));
		start_threads(toimg, g);
	}
	else if (g->light_switch > g->lights)
	{
		p.y = ((-WIDTH_2 + x) * 0.0045);
		p.x = (0.0045 * (y - HEIGHT_2));
		p.z = 0;
		*g->angle = p;
		*g->normal = rotate(g->fifteen, p);
		start_threads(recalc, g);
	}
	return (1);
}
