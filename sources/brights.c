/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brights.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 20:37:08 by tpokalch          #+#    #+#             */
/*   Updated: 2019/10/10 19:22:47 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_3_vecs	create_3_vecs(t_vector one, t_vector *two, t_vector three)
{
	t_3_vecs vec;

	vec.one = one;
	vec.two = two;
	vec.three = three;
	return (vec);
}

void		init_hitli(t_vector *hitli, t_vector hit, t_global *g)
{
	int i;

	i = 0;
	while (i < g->lights)
	{
		hitli[i] = diff(g->li[i], hit);
		i++;
	}
}

void		init_bri(int *bri, t_vector *hitli, t_vector nrm, t_global *g)
{
	int i;

	i = 0;
	*bri = 0;
	while (i < g->lights)
	{
		*bri += fmax(round(255 * dot(norm(hitli[i]), nrm)), *g->ambient);
		i++;
	}
	*bri = round(*bri / (double)g->lights);
}

void		do_1_spec(t_colbri *tmp, t_do_spec sp, t_global *g, int i)
{
	g->cosa[i] = dot(norm(sp.hitli[i]), norm(sp.reflrayv));
	if (g->cosa[i] > 0)
	{
		g->cosa[i] = tothe2(g->cosa[i], sp.obj.spec);
		tmp->col = sum(tmp->col, sum(scale(g->cosa[i], g->white),
					scale((1 - g->cosa[i]), sp.ret->col)));
	}
	else
		tmp->col = sum(tmp->col, sp.ret->col);
}

void		do_spec(t_colbri *ret, t_3_vecs co, t_object obj, t_global *g)
{
	int			i;
	t_colbri	tmp;
	t_vector	hitli[g->lights];

	i = -1;
	while (++i < g->lights)
		hitli[i] = diff(g->li[i], co.one);
	init_vector(&tmp.col, 0, 0, 0);
	i = -1;
	while (++i < g->lights)
		do_1_spec(&tmp, cr_spec(ret, hitli, co.three, obj), g, i);
	tmp.col = scale(1 / (double)g->lights, tmp.col);
	ret->col = tmp.col;
}
