/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:24:56 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/30 00:24:57 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int				con(t_global *g)
{
	return (g->shot.x == g->ray->x && g->shot.y == g->ray->y);
}

void			free_arr(char **arr)
{
	int			i;

	i = 0;
	while (*(arr + i) != NULL)
	{
		free(*(arr + i));
		i++;
	}
}

int				putstr(char *s, int ret)
{
	int			i;

	i = 0;
	while (*(s + i) != '\0')
	{
		write(1, s + i, 1);
		i++;
	}
	return (ret);
}

void			screen(int *a, int x, int y, t_global *g)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (j < y)
	{
		i = 0;
		while (i < x)
		{
			mlx_pixel_put(g->mlx_ptr, g->win_ptr, i, j, *(a + j * x + i));
			i++;
		}
		j++;
	}
}
