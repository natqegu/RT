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

#include "../includes/rt.h"

void	obstructed(t_colbri *cur, t_vector hit, t_vector *hitli, t_vector reflrayv, t_object obj, t_global *g)
{
	int			ilpko[5];
	int			obss[g->lights];
	t_vector	nrm_ray_obstructed[3];
	t_dstpst	t;
	t_colbri	tmp;
	double		soft[g->lights];

	ft_bzero(obss, 4 * g->lights);
	init_vector(&tmp.col, 0, 0, 0);
	ilpko[3] = 0;
	ilpko[0] = 0;
	obj.nr = nrm_ray_obstructed[0];
	while (ilpko[0] < g->lights)
	{
		nrm_ray_obstructed[1] = hitli[ilpko[0]];
		ilpko[1] = 0;
		ilpko[2] = g->prim;
		while (++ilpko[1] < g->argc + 1)
		{
			if (ilpko[2] == 0)
				ilpko[2] = (ilpko[2] + 1) % (g->argc + 1);
			if (obj.id != g->obj[ilpko[2]].id || 0)
			{
<<<<<<< HEAD
				t = g->obj[iobjn[1]].hit(cr_2_ve(hit, g->li[i]), ray, g->obj[iobjn[1]], g);
=======
				t = g->obj[ilpko[2]].hit(hit, g->li[ilpko[0]], nrm_ray_obstructed[1], g->obj[ilpko[2]], g);
>>>>>>> f35b03c4c7525a24787fe02fe3e8c80f18f4e912
				if (t.dst < 0.000001)
				{
					ilpko[0]++;
					break;
				}
				if (t.dst < 1)
				{
					if (obj.soft)
					{
						nrm_ray_obstructed[2] = sum(scale(t.dst, nrm_ray_obstructed[1]), hit);
						soft[ilpko[0]] = dot(norm(diff(nrm_ray_obstructed[2], *g->obj[ilpko[2]].ctr)), norm(nrm_ray_obstructed[1]));
						soft[ilpko[0]] = tothe2(soft[ilpko[0]], obj.soft);
					}
					g->prim = ilpko[2];
					ilpko[3]++;
					obss[ilpko[0]] = 1;
					break;
				}
			}
			ilpko[2] = (ilpko[2] + 1) % (g->argc + 1);
		}
		ilpko[0]++;
	}
	ilpko[0] = -1;
	if (obj.spec)
	{
		while (++ilpko[0] < g->lights)
		{
			if (obss[ilpko[0]] == 0)
				do_1_spec(&tmp, cur, hit, hitli, nrm_ray_obstructed[0], reflrayv, obj, ilpko[0], g);
		}
		ilpko[4] = g->lights - ilpko[3];
		if (ilpko[3] < g->lights)
		{
			tmp.col = scale(1 / (double)ilpko[4], tmp.col);
			cur->col = tmp.col;
		}
	}
	if (ilpko[3] > 0)
	{	
		if (obj.soft)
			cur->bri = fmax(*g->ambient, cur->bri * (1 - soft[0])) + ((g->lights - ilpko[3]) * (cur->bri - *g->ambient) / (double)g->lights);
		else
			cur->bri = *g->ambient + ((g->lights - ilpko[3]) * (cur->bri - *g->ambient) / (double)g->lights);
	}
}
<<<<<<< HEAD

void	objecthit(t_dstpst *ret, t_2_vec st_end, t_object *obj, int objc, t_global *g)
=======
void	objecthit(t_dstpst *ret, t_vector st, t_vector end, t_object *obj, int objc, t_global *g)
>>>>>>> f35b03c4c7525a24787fe02fe3e8c80f18f4e912
{
	int i;
	int legal_hit;
	t_dstpst t_crt;
	double closest_tmp;
	t_vector ray;

	i = 0;
	legal_hit = 0;
	ray = diff(st_end.two, st_end.one);
	while (++i < objc)
	{
		t_crt = obj[i].hit(st_end, ray, obj[i], g);
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

int		empty_line(int current, int *line_taken)
{
	int i;

	i = current;
	while (line_taken[i])
		i++;
	if (i >= STRIPS)
		return (-1);
	return (i);
}

void		*toimg(void *tcp)
{
	int j;
	int	i;
 	t_colbri	bright;
	t_global *g;
	int end;
	int jheight;

	g = tcp;
	end = (g->core + 1) * HEIGHT / CORES;
	j = g->core * HEIGHT / CORES - 1;
	jheight = j * HEIGHT;
	while ((++j < end) && (i = -1))
	{
		jheight += HEIGHT; 
		while (++i < WIDTH)
		{
			init_vector(g->ray, i - WIDTH_2, HEIGHT_2 - j, g->ray->z);
			if (g->hits[j][i]->obj.name != NULL)
			{
				bright = (g->hits[j][i])->obj.
				simple_bright(*g->cam_pos, (g->hits[j][i])->hit, (g->hits)[j][i]->obj, g);
				g->data_ptr[jheight + i] = color(bright.bri, bright.col);
			}
		}
	}
	pthread_exit(0);
}

void	*move(void *p)
{
	t_global *g;
	int i;
	int j;
	int end;
	t_colbri bright;
	t_dstpst ret;
	int	jheight;

	g = (t_global *)p;
	end = (g->core + 1) * HEIGHT / CORES;
	j = g->core * HEIGHT / CORES - 1;
	jheight = j * HEIGHT;
	while (++j < end && (i = -1))
	{
		jheight += HEIGHT;
		while (++i < WIDTH)
		{
			objecthit(&ret, cr_2_ve(*g->cam_pos, sum(*g->rays[j][i], *g->cam_pos)), g->obj, g->argc + 1, g);
			g->hits[j][i]->hit = sum(scale(ret.dst, *g->rays[j][i]), *g->cam_pos);
			g->hits[j][i]->obj = ret.obj;
			if (g->hits[j][i]->obj.name != NULL)
			{
				bright = (g->hits[j][i])->obj.bright(*g->cam_pos, (g->hits[j][i])->hit, (g->hits)[j][i]->obj, g);
				g->hits[j][i]->obj.bright = g->hits[j][i]->obj.simple_bright;
				g->hits[j][i]->obj.color = bright.colself;
				g->hits[j][i]->obj.nr = bright.nrm;
				g->data_ptr[jheight + i] = color(bright.bri, bright.col);
			}
			else
				g->data_ptr[jheight + i] = 0;			
		}
	}
	pthread_exit(0);
}

void	*recalc(void *p)
{
	t_global *g;
	int i;
	int j;
	t_vector ray;
	int end;
	t_colbri bright;
	t_dstpst ret;
	int jheight;
	
	g = (t_global *)p;

	end = (g->core + 1) * HEIGHT / CORES;
	j = g->core * HEIGHT / CORES - 1;
	jheight = j * HEIGHT;
	while (++j < end && (i = -1))
	{
		// if (g->core == 0)
			// printf("LOADING = %f%s\n", j / (double)(HEIGHT / (double)CORES) + 1 - g->core, "\%");
		jheight += HEIGHT;
		while (++i < WIDTH)
		{
			init_vector(g->ray, i - WIDTH_2, HEIGHT_2 - j, g->ray->z);
			init_vector(&ray, i - WIDTH_2, HEIGHT_2 - j, g->ray->z);
			ray = rotate(ray, *g->angle);
			*g->rays[j][i] = ray;
			objecthit(&ret, cr_2_ve(*g->cam_pos, sum(ray, *g->cam_pos)), g->obj, g->argc + 1, g);
			g->hits[j][i]->obj = ret.obj;
			g->hits[j][i]->hit = sum(scale(ret.dst, *g->rays[j][i]), *g->cam_pos);
			if (g->hits[j][i]->obj.name != NULL)
			{
				bright = g->hits[j][i]->obj.
				bright(*g->cam_pos, g->hits[j][i]->hit, (g->hits)[j][i]->obj, g);
				g->hits[j][i]->obj.color = bright.colself;
				g->hits[j][i]->obj.nr = bright.nrm;
				g->data_ptr[jheight + i] = color(bright.bri, bright.col);
			}
			else
				g->data_ptr[jheight + i] = 0;
		}
	}
	pthread_exit(0);
}
