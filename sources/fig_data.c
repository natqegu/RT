/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fig_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:52:07 by vkarpova          #+#    #+#             */
/*   Updated: 2019/02/01 17:52:07 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		fig_reflect(t_list *list)
{
	if (list->content_size == CONE)
		return (((t_cone *)(list->content))->reflect);
	else if (list->content_size == CYL)
		return (((t_cylinder *)(list->content))->reflect);
	else if (list->content_size == SPHERE)
		return (((t_sphere *)(list->content))->reflect);
	else if (list->content_size == PLANE)
		return (((t_plane *)(list->content))->reflect);
	return (0);
}

double		fig_transp(t_list *list)
{
	if (list->content_size == CONE)
		return (((t_cone *)(list->content))->transp);
	else if (list->content_size == CYL)
		return (((t_cylinder *)(list->content))->transp);
	else if (list->content_size == SPHERE)
		return (((t_sphere *)(list->content))->transp);
	else if (list->content_size == PLANE)
		return (((t_plane *)(list->content))->transp);
	return (0);
}

double		fig_shadow(t_list *list)
{
	if (list->content_size == CONE)
		return (((t_cone *)(list->content))->shadow);
	else if (list->content_size == CYL)
		return (((t_cylinder *)(list->content))->shadow);
	else if (list->content_size == SPHERE)
		return (((t_sphere *)(list->content))->shadow);
	else if (list->content_size == PLANE)
		return (((t_plane *)(list->content))->shadow);
	return (0);
}

double		fig_specular(t_list *list)
{
	if (list->content_size == CONE)
		return (((t_cone *)(list->content))->specular);
	else if (list->content_size == CYL)
		return (((t_cylinder *)(list->content))->specular);
	else if (list->content_size == SPHERE)
		return (((t_sphere *)(list->content))->specular);
	else if (list->content_size == PLANE)
		return (((t_plane *)(list->content))->specular);
	return (0);
}

int			fig_color(t_list *list)
{
	if (list->content_size == CONE)
		return (((t_cone *)(list->content))->color);
	else if (list->content_size == CYL)
		return (((t_cylinder *)(list->content))->color);
	else if (list->content_size == SPHERE)
		return (((t_sphere *)(list->content))->color);
	else if (list->content_size == PLANE)
		return (((t_plane *)(list->content))->color);
	return (0);
}

t_vector	fig_center(t_list *list)
{
	if (list->content_size == CONE)
		return (((t_cone *)(list->content))->c);
	else if (list->content_size == CYL)
		return (((t_cylinder *)(list->content))->c);
	else if (list->content_size == SPHERE)
		return (((t_sphere *)(list->content))->c);
	else if (list->content_size == PLANE)
		return (((t_plane *)(list->content))->c);
	return (init_vector(0, 0, 0, 0));
}

void		fig_normal(t_vec *vec, t_clos *clos)
{
	if ((clos->obj)->content_size == PLANE)
		plane_normal(vec, (t_plane *)((clos->obj)->content));
	else if ((clos->obj)->content_size == SPHERE)
		sphere_normal(vec, (t_sphere *)((clos->obj)->content));
	else if ((clos->obj)->content_size == CYL)
		cyl_normal(vec, clos->clost, (t_cylinder *)((clos->obj)->content));
	else if ((clos->obj)->content_size == CONE)
		cone_normal(vec, clos->clost, (t_cone *)((clos->obj)->content));
}
