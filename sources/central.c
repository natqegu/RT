/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 20:10:51 by tpokalch          #+#    #+#             */
/*   Updated: 2019/07/03 20:36:09 by tpokalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_hunia		cr_hu(int o, t_colbri *cur, t_3_vecs co)
{
	t_hunia hu;

	hu.o = o;
	hu.co = co;
	hu.cur = cur;
	return (hu);
}

void	if_obj_spec(t_global *g, t_object *obj, t_hunia hu, int *obss)
{
	t_colbri	tmp;
	int			i;

	init_vector(&tmp.col, 0, 0, 0);
	i = -1;
	if (obj->spec)
	{
		while (++i < g->lights)
		{
			if (obss[i] == 0)
				do_1_spec(&tmp, cr_spec(hu.cur, hu.co.two, hu.co.three,
															*obj), g, i);
		}
		if (hu.o < g->lights)
		{
			tmp.col = scale(1 / (double)(g->lights - hu.o), tmp.col);
			hu.cur->col = tmp.col;
		}
	}
}

void	if_io_2(t_global *g, t_object *obj, double *soft, t_hunia hu)
{
	int i;
	int	darken[g->lights];

	i = -1;
	if (hu.o > 0)
	{
		if (obj->soft)
		{
			while (++i < g->lights)
			{
				darken[i] = ((hu.cur->bri - *g->ambient) / g->lights) * soft[i];
				hu.cur->bri = hu.cur->bri - darken[i];
			}
		}
		else
			hu.cur->bri = *g->ambient + ((g->lights - hu.o) * (hu.cur->bri -
										*g->ambient) / (double)g->lights);
	}
}

t_masi	cr_masi(double *soft, int *obss, int *io)
{
	t_masi masivchik;

	masivchik.s = soft;
	masivchik.obss = obss;
	masivchik.io = io;
	return (masivchik);
}

int		if_obj_id(t_3_vecs co, t_object *obj, t_global *g, t_masi m)
{
	t_dstpst	t;

	if (obj->id != g->obj[m.io[1]].id || 0)
	{
		t = g->obj[m.io[1]].hit(co.one, g->li[m.io[3]], co.two[m.io[3]],
													&g->obj[m.io[1]]);
		if (t.dst < 0.000001)
		{
			m.io[3]++;
			return (0);
		}
		if (t.dst < 1)
		{
			if (obj->soft)
			{
				m.s[m.io[3]] = dot(norm(diff(sum(scale(t.dst, co.two[m.io[3]]),
					co.one), *g->obj[m.io[1]].ctr)), norm(co.two[m.io[3]]));
				m.s[m.io[3]] = tothe2(m.s[m.io[3]], obj->soft);
			}
			m.io[2]++;
			m.obss[m.io[3]] = 1;
			return (0);
		}
	}
	return (1);
}

void	obstructed(t_colbri *cur, t_3_vecs co, t_object *obj, t_global *g)
{
	int			obss[g->lights];
	double		soft[g->lights];
	int			io[4];

	ft_bzero(obss, 4 * g->lights);
	io[2] = 0;
	io[3] = -1;
	while (++io[3] < g->lights)
	{
		io[0] = 0;
		io[1] = g->prim;
		while (++io[0] < g->argc + 1)
		{
			if (io[1] == 0)
				io[1] = (io[1] + 1) % (g->argc + 1);
			if (!if_obj_id(co, obj, g, cr_masi(soft, obss, io)))
				break ;
			io[1] = (io[1] + 1) % (g->argc + 1);
		}
	}
	if_obj_spec(g, obj, cr_hu(io[2], cur, co), obss);
	if_io_2(g, obj, soft, cr_hu(io[2], cur, co));
}

void	objecthit(t_dstpst *ret, t_3_vecs co, t_object *obj, int objc)
{
	int			i;
	int			legal_hit;
	t_dstpst	t_crt;
	double		closest_tmp;
	t_vector	ray;

	i = 0;
	legal_hit = 0;
	ray = diff(co.three, co.one);
	while (++i < objc)
	{
		t_crt = obj[i].hit(co.one, co.three, ray, &obj[i]);
		if ((t_crt.dst >= 0.0000001) && (!legal_hit || t_crt.dst < closest_tmp))
		{
			legal_hit = 1;
			closest_tmp = t_crt.dst;
			*ret = t_crt;
			ret->obj.cam_pos = t_crt.pst;
		}
	}
	if (!legal_hit)
		ret->obj.name = NULL;
}

void	*toimg(void *tcp)
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

void	move_row(int j, int jheight, t_global *g)
{
	int			i;
	t_dstpst	ret;
	t_colbri	bright;

	i = -1;
	while (++i < WIDTH)
	{
		objecthit(&ret, create_3_vecs(*g->cam_pos, NULL, sum(*g->rays[j][i],
										*g->cam_pos)), g->obj, g->argc + 1);
		g->hits[j][i]->hit = sum(scale(ret.dst, *g->rays[j][i]), *g->cam_pos);
		g->hits[j][i]->obj = ret.obj;
		if (g->hits[j][i]->obj.name != NULL)
		{
			bright = ret.obj.bright(*g->cam_pos, (g->hits[j][i])->hit,
												&(g->hits)[j][i]->obj, g);
			g->data_ptr[jheight + i] = color(bright.bri, bright.col);
		}
		else
			g->data_ptr[jheight + i] = 0;
	}
}

void	*move(void *p)
{
	t_global	*g;
	int			j;
	int			end;
	int			jheight;

	g = (t_global *)p;
	end = (g->core + 1) * HEIGHT / CORES;
	j = g->core * HEIGHT / CORES - 1;
	jheight = j * HEIGHT;
	while (++j < end)
	{
		jheight += HEIGHT;
		move_row(j, jheight, g);
	}
	return (NULL);
}

void	load(int w)
{
	    int k;
        int i;
    if (w == 100)
   		write(1, "LOADING 100%\n", 13);
	else
	{
   		k = w/10 + 48;
        i = w % 10 + 48;
    	if (k != 58)
    	{
       
       		 if (i >= 48 && i <= 57)
        	{
          	 write(1, "LOADING ", 8);
          		 if (k > 48)
           			  write(1, &k, 1);
         	 write(1, &i, 1);
          	 write(1, "%\n", 2);
        	}
		}
	}

}

void	recalc_row(int jheight, int j, t_global *g)
{
	t_vector	ray;
	t_dstpst	ret;
	int			i;
	t_colbri	bright;

	i = -1;
	// if (g->core == 4)
	// 	load((int)((j/(double)(HEIGHT / (double)CORES)) * 100 / 4));
	while (++i < WIDTH)
	{
		init_vector(&ray, i - WIDTH_2, HEIGHT_2 - j, g->ray->z);
		ray = rotate(ray, *g->angle);
		*g->rays[j][i] = ray;
		objecthit(&ret, create_3_vecs(*g->cam_pos, NULL, sum(ray, *g->cam_pos)),
														g->obj, g->argc + 1);
		g->hits[j][i]->obj = ret.obj;
		g->hits[j][i]->hit = sum(scale(ret.dst, *g->rays[j][i]), *g->cam_pos);
		if (g->hits[j][i]->obj.name != NULL)
		{
			bright = g->hits[j][i]->obj.
			bright(*g->cam_pos, g->hits[j][i]->hit, &(g->hits)[j][i]->obj, g);
			g->data_ptr[jheight + i] = color(bright.bri, bright.col);
		}
		else
			g->data_ptr[jheight + i] = 0;
	}
}

void	*recalc(void *p)
{
	t_global	*g;
	int			j;
	int			end;
	int			jheight;

	g = (t_global *)p;
	end = (g->core + 1) * HEIGHT / CORES;
	j = g->core * HEIGHT / CORES - 1;
	jheight = j * HEIGHT;
	while (++j < end)
	{
		jheight += HEIGHT;
		recalc_row(jheight, j, g);
	}
	return (NULL);
}
