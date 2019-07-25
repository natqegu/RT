/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_fig.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:53:09 by vkarpova          #+#    #+#             */
/*   Updated: 2019/02/01 17:53:10 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		save_light(t_all *all)
{
	t_list		*tmp;
	t_light		light;

	if (save_intense(all, &(light.intense)) &&
		(save_pos(all, &(light.pos))))
	{
		all->is_light = 1;
		if (light.intense == 0)
			all->is_light = 0;
		tmp = ft_lstnew(&(light), sizeof(t_light));
		tmp->content_size = LIGHT;
		ft_lstadd(&(all->light), tmp);
		return (1);
	}
	ft_putendl("Incorrect info for #light, so it doesn't appear");
	return (0);
}

int		save_plane(t_all *all)
{
	t_list		*tmp;
	t_plane		plane;

	if (save_color(all, &(plane.color)) &&
		(save_specular(all, &(plane.specular))) &&
		(save_reflect(all, &(plane.reflect))) &&
		(save_transp(all, &(plane.transp))) &&
		(save_shadow(all, &(plane.shadow))) &&
		(save_normal(all, &(plane.v))) &&
		(save_center(all, &(plane.c))))
	{
		tmp = ft_lstnew(&(plane), sizeof(t_plane));
		tmp->content_size = PLANE;
		ft_lstadd(&(all->obj), tmp);
		return (1);
	}
	ft_putendl("Incorrect info for #plane, so it doesn't appear");
	return (0);
}

int		save_cylinder(t_all *all)
{
	t_list		*tmp;
	t_cylinder	cylinder;

	if (save_color(all, &(cylinder.color)) &&
		(save_specular(all, &(cylinder.specular))) &&
		(save_reflect(all, &(cylinder.reflect))) &&
		(save_transp(all, &(cylinder.transp))) &&
		(save_shadow(all, &(cylinder.shadow))) &&
		(save_radius(all, &(cylinder.r))) &&
		(save_normal(all, &(cylinder.v))) &&
		(save_center(all, &(cylinder.c))))
	{
		tmp = ft_lstnew(&(cylinder), sizeof(t_cylinder));
		tmp->content_size = CYL;
		ft_lstadd(&(all->obj), tmp);
		return (1);
	}
	ft_putendl("Incorrect info for #cylinder, so it doesn't appear");
	return (0);
}

int		save_sphere(t_all *all)
{
	t_list		*tmp;
	t_sphere	sphere;

	if (save_color(all, &(sphere.color)) &&
		(save_specular(all, &(sphere.specular))) &&
		(save_reflect(all, &(sphere.reflect))) &&
		(save_transp(all, &(sphere.transp))) &&
		(save_shadow(all, &(sphere.shadow))) &&
		(save_radius(all, &(sphere.r))) &&
		(save_center(all, &(sphere.c))))
	{
		tmp = ft_lstnew(&sphere, sizeof(t_sphere));
		tmp->content_size = SPHERE;
		ft_lstadd(&(all->obj), tmp);
		return (1);
	}
	ft_putendl("Incorrect info for #sphere, so it doesn't appear");
	return (0);
}

int		save_cone(t_all *all)
{
	t_list		*tmp;
	t_cone		cone;

	if (save_color(all, &(cone.color)) &&
		(save_specular(all, &(cone.specular))) &&
		(save_reflect(all, &(cone.reflect))) &&
		(save_transp(all, &(cone.transp))) &&
		(save_shadow(all, &(cone.shadow))) &&
		(save_angle(all, &(cone.a))) &&
		(save_normal(all, &(cone.v))) &&
		(save_center(all, &(cone.c))))
	{
		tmp = ft_lstnew(&cone, sizeof(t_cone));
		tmp->content_size = CONE;
		ft_lstadd(&(all->obj), tmp);
		return (1);
	}
	ft_putendl("Incorrect info for #cone, so it doesn't appear");
	return (0);
}
