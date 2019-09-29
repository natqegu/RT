/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:11:21 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/30 00:11:23 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			arrheight(void **a)
{
	int			i;

	i = 0;
	while (*(a + i))
		i++;
	return (i);
}

void		ctd(t_object *ret, int jihul[5])
{
	t_object	obj;

	obj = ret[999];
	R[Y].base[1] = R4;
	R[Y + 1].base[0] = norm(diff(R[Y + 1].bd1, R[Y + 1].bd3));
	R[Y + 1].ctr = obj.ctr;
	R[Y].tile[0] = obj.tile[0];
	R[Y + 1].tile[0] = obj.tile[0];
	R[Y].color = obj.color;
	R[Y + 1].color = rgb(0x010000);
	R[Y].re = obj.re;
	R[Y + 1].re = obj.re;
	R[Y].spec = obj.spec;
	R[Y + 1].spec = obj.spec;
	Y = Y + 2;
	R[Y + 1].base[2] = norm(diff(R[Y + 1].bd2, R[Y + 1].bd3));
	R[Y + 1].base[1] = R5;
	R[Y].ctr = obj.ctr;
}

void		c_tris_add(t_object *ret, int jihul[5], t_global *g, t_vector **pts)
{
	t_object	obj;
	t_vector	smallspace;

	smallspace = (t_vector){1, 2, 3};
	obj = ret[999];
	R[Y].bd1 = sum(rotate(*(*(pts + Q) + W), obj.ang), *obj.ctr);
	R[Y].bd2 = sum(rotate(*(*(pts + Q) + W + 1), obj.ang), *obj.ctr);
	R[Y].bd3 = sum(rotate(*(*(pts + Q + 1) + W), obj.ang), *obj.ctr);
	R[Y + 1].bd1 = R1;
	R[Y + 1].bd2 = R2;
	R[Y + 1].bd3 = R3;
	R[Y].hit = &hit_tri;
	R[Y + 1].hit = &hit_tri;
	R[Y].bright = &bright_tri;
	R[Y].simple_bright = &bright_tri;
	R[Y + 1].bright = &bright_tri;
	R[Y + 1].simple_bright = &bright_tri;
	R[Y].id = g->argc + Y + 1;
	R[Y + 1].id = g->argc + Y + 2;
	R[Y].name = "tri";
	R[Y + 1].name = "tri";
	R[Y].base[0] = norm(diff(R[Y].bd1, R[Y].bd3));
	R[Y].base[2] = norm(diff(R[Y].bd2, R[Y].bd3));
	ret[999] = obj;
	ctd(ret, jihul);
}

t_object	*create_tris(t_vector **pts, t_object obj, t_global *g)
{
	t_vector	smallspace;
	t_object	*ret;
	int			jihul[5];

	T = obj.ptdim.x / 20;
	E = arrheight((void **)pts);
	R = (t_object *)malloc(sizeof(t_object) * (T * E * 2 + 1));
	Q = -1;
	W = 0;
	Y = 0;
	init_vector(&smallspace, 0, 0, 0);
	while (*(pts + ++Q + 1))
	{
		W = -1;
		while (++W + 1 < T)
		{
			ret[999] = obj;
			c_tris_add(ret, jihul, g, pts);
		}
	}
	(R)->rd = (T - 1) * (E - 1) * 2 + 1;
	return (R);
}

t_object	*init_frame(t_object obj, t_global *g)
{
	t_object	*ret;
	t_vector	bas[3];
	t_vector	rc;

	ret = (t_object *)malloc(sizeof(t_object));
	ret->name = "sphere";
	ret->hit = &hit_sphere;
	ret->ctr = obj.ctr;
	bas[0] = scale(obj.ptdim.x, g->base[0]);
	bas[1] = scale(obj.ptdim.y, g->base[1]);
	bas[2] = scale(obj.ptdim.z, g->base[2]);
	rc = scale(-0.5, sum(sum(bas[0], bas[1]), bas[2]));
	ret->rd2 = ceil(dot(rc, rc)) - 5000;
	ret->rd = sqrt(ret->rd2);
	return (ret);
}
