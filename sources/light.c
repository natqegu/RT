/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:52:30 by vkarpova          #+#    #+#             */
/*   Updated: 2019/02/01 17:52:31 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int				shadow(t_list *list, t_list *obj, t_vector o, t_vector d)
{
	t_clos		closer;
	t_vector	a;
	double		n;

	n = sqrtf(dot(d, d));
	a = init_vector(600000, 600000, 600000, 600000);
	closer.clost = 600000;
	closer.obj = 0;
	d = norm(d);
	while (list != NULL)
	{
		if (list != obj)
		{
			a = intersect_ray(list, o, d);
			if (a.t1 > 0.0001 && a.t1 < closer.clost)
				closer.clost = a.t1;
			if (a.t2 > 0.0001 && a.t2 < closer.clost)
				closer.clost = a.t2;
			if (closer.clost < n)
				return (0);
		}
		list = list->next;
	}
	return (1);
}

void		ambient_light(t_all *all, t_list **l)
{
	// t_list		*tmp;
	t_light		light;


	all->is_light = 0;
	light.intense = 0.2;
	light.pos = init_vector(0,5,-50,0);
	*l = ft_lstnew(&(light), sizeof(t_light));
	(*l)->content_size = LIGHT;
	ft_lstadd(&(all->light), *l);
}

int				reflected_color(t_all *all, t_clos clos, t_vec *vec)
{
	t_list		*light;
	t_vector	k;
	int			s;
	double		spec1;

	if (all->light == NULL)
		ambient_light(all, &light);
	light = all->light;
	while (light)
	{
		spec1 = fig_specular(clos.obj);
		if (fig_reflect(clos.obj) > 0)
			spec1 /= 10;
		vec->l = minus(((t_light *)(light->content))->pos, vec->p);
		s = shadow(all->obj, clos.obj, vec->p, vec->l);
		if (s != 0)
		{
			if (all->is_light == 0)
			{
				((t_light *)(light->content))->intense = 0.2;
				spec1 = 0;
			}
			k.x += diff(((t_light *)(light->content))->intense, vec);
			if ((spec1) > 0)
				k.y += spec(spec1,
					((t_light *)(light->content))->intense, vec, fig_reflect(clos.obj));
		}
		light = light->next;
	}
	return (calc_color(k.x, k.y, int_to_rgb(fig_color(clos.obj))));
}

t_vector		reflect(t_all *all, t_vec *vec, t_clos closer, t_vector local_color)
{
	t_vector	color;
	int			ref_color;

	color = init_vector(0,0,0,0);
	vec->r = minus(times(2 * dot(vec->n, vec->v), vec->n), vec->v);
	vec->r = norm(vec->r);
	if (all->depth_transp < all->depth_max)
	{
		all->depth_refl++;
		ref_color = trace_ray(all, all->obj, all->cam, vec->r);
		color = new_color(local_color, int_to_rgb(ref_color), fig_reflect(closer.obj) / 100);
	}
	return (color);
}

t_vector		get_random(t_vector vec1, t_vector vec2, double param)
{
	t_vector	a;
	t_vector	b;

	a.x = rand() / RAND_MAX * param * (param * 0.5);
	a.y = rand() / RAND_MAX * param * (param * 0.5);
	a.z = rand() / RAND_MAX * param * (param * 0.5);
	b = plus(plus(vec1, vec2), a);
	b = norm(b);
	return(b);
}

// t_vector		reflect_spec(t_all *all, t_vec *vec, t_clos closer, t_vector local_color)
// {
// 	t_vector	color;
// 	t_vector	a;
// 	// int			i;
// 	// int			sampling;
// 	int			ref_color;

// 	color = init_vector(0,0,0,0);
// 	vec->r = plus(vec->n, times(-2 * dot(vec->d, vec->n), vec->n));
// 	vec->r = norm(vec->r);
// 	a = vec->r;
// 	if (all->depth_refl_spec < all->depth_max)
// 	{
// 		all->depth_refl_spec++;
// 		vec->r = get_random(vec->p, vec->d, fig_specular(closer.obj));
// 		ref_color = trace_ray(all, all->obj, all->cam, vec->r);
// 		color = new_color(local_color, int_to_rgb(ref_color), fig_reflect(closer.obj) / 100);
// 	}
// 	return (color);
// }


t_vector		transp(t_all *all, t_vec *vec, t_clos closer, t_vector local_color)
{
	t_vector	color;
	int			ref_color;
	t_vector	a;

	color = init_vector(0,0,0,0);
	if (all->depth_transp < all->depth_max)
	{
		all->depth_transp++;
		a.x = dot(vec->n, vec->d);
		if (a.x > 0)
		{
			a.y = fig_transp(closer.obj);
			a.z = 1;
			vec->n = minus(init_vector(0,0,0,0), vec->n);
		}
		else
		{
			a.y = 1;
			a.z = fig_transp(closer.obj);
			a.x = -a.x ;
		}
		a.t1 = a.y / a.z;
		a.t2 = a.t1 * a.t1 * (1 - a.x * a.x);
		a.t = sqrt(1 - a.t2);
		vec->r = plus(times(a.t1, vec->r), times((a.t1 * a.x - a.t), vec->n));
		vec->r = norm(vec->r);
		ref_color = trace_ray(all, all->obj, all->cam, vec->r);
		color = new_color(local_color, int_to_rgb(ref_color), fig_transp(closer.obj) / 100);
	}
	return (color);
}

double			diff(double intense, t_vec *vec)
{
	double		i;
	double		nl;

	i = 0;
	nl = dot(vec->n, vec->l);
	if (nl > 0)
		i = intense * nl / (dlinna(vec->n) * dlinna(vec->l));
	return (i);
}

double			spec(double spec, double intense, t_vec *vec, double reflect)
{
	t_vector	r;
	double		rv;
	double		j;

	j = 0;
	r = minus(times(2 * dot(vec->n, vec->l), vec->n), vec->l);
	// r = norm(r);
	rv = dot(r, vec->v);
	if (rv > 0)
	{
		if (reflect > 0 && reflect < 50)
			intense = 7;
		else if (reflect >= 50 && reflect < 85)
			intense = 10;
		else if (reflect >= 85)
		{
			spec = 150;
			intense = 10;
		}
		j += intense * pow((rv / (dlinna(r) * dlinna(vec->v))), spec);
	}
	return (j);
}

int				calc_color(double i, double j, t_vector color)
{
	// t_vector	color;

	// color = int_to_rgb(fig_color(clos.obj));
	color.x += j * 255;
	color.y += j * 255;
	color.z += j * 255;
	color.x *= i;
	color.y *= i;
	color.z *= i;
	if (color.x > 255)
		color.x = 255;
	if (color.y > 255)
		color.y = 255;
	if (color.z > 255)
		color.z = 255;
	if (color.x < 0)
		color.x = 0;
	if (color.y < 0)
		color.y = 0;
	if (color.z < 0)
		color.z = 0;
	return (rgb_to_int(color));
}

t_vector		new_color(t_vector local, t_vector ref, double param)
{
	t_vector	color;

	if (param == 1)
		param = 0.9;
	color.x = local.x * (1 - param) + ref.x * param;;
	color.y = local.y * (1 - param) + ref.y * param;
	color.z = local.z * (1 - param) + ref.z * param;
	if (color.x > 255)
		color.x = 255;
	if (color.y > 255)
		color.y = 255;
	if (color.z > 255)
		color.z = 255;
	if (color.x < 0)
		color.x = 0;
	if (color.y < 0)
		color.y = 0;
	if (color.z < 0)
		color.z = 0;
	return (color);
}

// void		shadow_type(t_vector *color, t_vec *vec, t_list *light, t_all *all, t_clos clos)
// {
// 	if (fig_shadow(clos.obj) == 0)
// 		soft_shadow(color, vec, light, all, clos);
	// else
	// 	hard_shadow();
// }

// void			soft_shadow(t_vector *color, t_vec *vec, t_list *light, t_all *all, t_clos clos)
// {
// 	double		shadow_intense;

// 	shadow_intense = 0.002;
// 	vec->r = norm(minus(vec->p, ((t_light *)(light->content))->pos));
// 	vec->p = ((t_light *)(light->content))->pos;
// 	if (shadow(all->obj, clos.obj, vec->p, vec->l) != 0)
// 		*color = times((1 - shadow_intense), *color);
// }

// void			hard_shadow(t_vector *color, t_vec *vec, t_list light, t_all *all, t_list *obj)
// {

// }
