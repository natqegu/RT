/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_points.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 20:40:40 by vkarpova          #+#    #+#             */
/*   Updated: 2019/10/11 20:40:41 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_vector	**initialize_points(int height)
{
	int			i;
	t_vector	**ret;

	i = 0;
	ret = (t_vector **)malloc(sizeof(t_vector *) * height);
	while (i < height)
	{
		*(ret + i) = NULL;
		i++;
	}
	return (ret);
}
