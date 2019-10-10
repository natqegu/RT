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

#include "rt.h"

t_object	*ret_retc(t_object *ret, int retc)
{
	ret[retc].hit = &hit_tri;
	ret[retc + 1].hit = &hit_tri;
	ret[retc].bright = &bright_tri;
	ret[retc].simple_bright = &bright_tri;
	ret[retc + 1].bright = &bright_tri;
	ret[retc + 1].simple_bright = &bright_tri;
	ret[retc].name = "tri";
	ret[retc + 1].name = "tri";
	ret[retc + 1].color = rgb(0x010000);
	ret[retc].base[0] = norm(diff(ret[retc].bd1, ret[retc].bd3));
	ret[retc].base[2] = norm(diff(ret[retc].bd2, ret[retc].bd3));
	ret[retc].base[1] = norm(cross(diff(ret[retc].bd1, ret[retc].bd3),
								diff(ret[retc].bd2, ret[retc].bd3)));
	ret[retc + 1].base[0] = norm(diff(ret[retc + 1].bd1, ret[retc + 1].bd3));
	ret[retc + 1].base[2] = norm(diff(ret[retc + 1].bd2, ret[retc + 1].bd3));
	ret[retc + 1].base[1] = norm(cross(diff(ret[retc + 1].bd1, ret[retc + 1].
							bd3), diff(ret[retc + 1].bd2, ret[retc + 1].bd3)));
	return (ret);
}

t_object	*ret_retc_obj(t_object *ret, int retc, t_object obj, t_global *g)
{
	ret[retc].id = g->argc + retc + 1;
	ret[retc + 1].id = g->argc + retc + 2;
	ret[retc].ctr = obj.ctr;
	ret[retc + 1].ctr = obj.ctr;
	ret[retc].tile[0] = obj.tile[0];
	ret[retc + 1].tile[0] = obj.tile[0];
	ret[retc].color = obj.color;
	ret[retc].re = obj.re;
	ret[retc + 1].re = obj.re;
	ret[retc].trans = obj.trans;
	ret[retc + 1].trans = obj.trans;
	ret[retc + 1].spec = obj.spec;
	return (ret);
}

void		hrrrr(t_object *h, t_vector *vec, t_object *obj)
{
	t_vector	smallspace;

	init_vector(&smallspace, 0, 0, 0);
	h->bd1 = sum(rotate(vec[3], obj->ang), *obj->ctr);
	h->bd2 = sum(rotate(vec[1], obj->ang), *obj->ctr);
	h->bd3 = sum(rotate(vec[2], obj->ang), *obj->ctr);
	(h + 1)->bd1 = sum(rotate(sum(vec[0], smallspace), obj->ang), *obj->ctr);
	(h + 1)->bd2 = sum(rotate(sum(vec[1], smallspace), obj->ang), *obj->ctr);
	(h + 1)->bd3 = sum(rotate(sum(vec[2], smallspace), obj->ang), *obj->ctr);
}

t_object	*create_tris(t_vector **pts, t_object obj, t_global *g)
{
	int			j;
	int			i;
	int			retc;
	t_object	*ret;

	ret = (t_object *)malloc(sizeof(t_object) *
			(obj.ptdim.x / 20 * arrheight((void **)pts) * 2 + 1));
	j = -1;
	retc = 0;
	while (*(pts + ++j + 1))
	{
		i = -1;
		while (++i < obj.ptdim.x / 20 - 1)
		{
			ret_retc_obj(ret, retc, obj, g);
			hrrrr(&ret[retc], cr_vec(pts, i, j), &obj);
			ret_retc(ret, retc);
			retc += 2;
		}
	}
	(ret)->rd = (obj.ptdim.x / 20 - 1) * (arrheight((void **)pts) - 1) * 2 + 1;
	return (ret);
}

t_object	*init_frame(t_object obj, t_global *g)
{
	t_object *ret;
	t_vector bas[3];
	t_vector rc;

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
