/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:54:48 by nnovikov          #+#    #+#             */
/*   Updated: 2019/10/10 20:54:50 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		*toimg(void *tcp)
{
	int			j;
	int			i;
	t_colbri	bright;
	t_global	*g;
	int			jheight;

	g = tcp;
	j = g->core * HEIGHT / CORES - 1;
	jheight = j * HEIGHT;
	while ((++j < (g->core + 1) * HEIGHT / CORES) && (i = -1))
	{
		jheight += HEIGHT;
		while (++i < WIDTH)
		{
			if (g->hits[j][i]->obj.name != NULL)
			{
				bright = (g->hits[j][i])->obj.
				simple_bright(*g->cam_pos, (g->hits[j][i])->hit,
										&(g->hits)[j][i]->obj, g);
				g->data_ptr[jheight + i] = color(bright.bri, bright.col);
			}
		}
	}
	return (NULL);
}

t_dstpst	*nani(t_dstpst *t)
{
	t->dst = NAN;
	t->obj.name = NULL;
	return (t);
}
