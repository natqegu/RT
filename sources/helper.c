/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:30:34 by nnovikov          #+#    #+#             */
/*   Updated: 2019/10/10 20:30:56 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_do_spec	cr_spec(t_colbri *ret, t_vector *hitli, t_vector reflrayv,
															t_object obj)
{
	t_do_spec spec;

	spec.ret = ret;
	spec.hitli = hitli;
	spec.reflrayv = reflrayv;
	spec.obj = obj;
	return (spec);
}

void		hello(t_vector end)
{
	int i;

	i = 1;
	if (end.x == 0)
		i = 0;
}

int			arrheight(void **a)
{
	int			i;

	i = 0;
	while (*(a + i))
		i++;
	return (i);
}

t_vector	*cr_vec(t_vector **pts, int i, int j)
{
	t_vector	*vec;

	vec = (t_vector *)malloc(sizeof(t_vector) * 4);
	vec[0] = *(*(pts + j + 1) + i + 1);
	vec[1] = *(*(pts + j) + i + 1);
	vec[2] = *(*(pts + j + 1) + i);
	vec[3] = *(*(pts + j) + i);
	return (vec);
}

t_hunia		cr_hu(int o, t_colbri *cur, t_3_vecs co)
{
	t_hunia hu;

	hu.o = o;
	hu.co = co;
	hu.cur = cur;
	return (hu);
}
