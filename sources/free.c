/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:53:48 by nnovikov          #+#    #+#             */
/*   Updated: 2019/10/10 20:53:50 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int				free_hits(t_global *g)
{
	int			i;
	int			j;

	i = -1;
	while (++i < HEIGHT && (j = -1))
		while (++j < WIDTH)
			free(*(*(g->hits + i) + j));
	i = -1;
	while (++i < HEIGHT)
		free(*(g->hits + i));
	free(g->hits);
	i = -1;
	while (++i < HEIGHT && (j = -1))
		while (++j < WIDTH)
			free(*(*(g->rays + i) + j));
	i = -1;
	while (++i < HEIGHT)
		free(*(g->rays + i));
	free(g->rays);
	i = -1;
	while (++i < CORES)
		free(g->tcps[i]);
	return (1);
}
