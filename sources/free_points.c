/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:02:35 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 18:02:36 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		free_points(t_vector **pts)
{
	int i;

	i = 0;
	while (*(pts + i))
	{
		free(*(pts + i));
		i++;
	}
	free(pts);
}

int			next_num(char *s)
{
	int		i;

	i = 0;
	while (*(s + i) == ' ')
		i++;
	while (*(s + i) != ' ' && *(s + i) != '\0')
	{
		if ((*(s + i) < '0' || *(s + i) > '9') && *(s + i) != ' '
				&& *(s + i) != '-' && *(s + i) != '+')
			return (-1);
		i++;
	}
	while (*(s + i) == ' ')
		i++;
	return (i);
}
