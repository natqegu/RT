/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ta_du_zaebal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 20:42:40 by vkarpova          #+#    #+#             */
/*   Updated: 2019/10/11 20:42:41 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void			buttons6(int x, int y, t_global *g)
{
	if (x > 750 && x < 950 && y > 290 && y < 340)
	{
		if (g->filter_switch == 3)
			return ;
		else
			make_negative(g);
	}
	if (x > 750 && x < 950 && y > 350 && y < 400)
	{
		if (g->filter_switch == 4)
			return ;
		else
			make_stereo(g);
	}
	if (x > 750 && x < 950 && y > 410 && y < 460)
	{
		*g->ambient = 250;
		g->obj[g->objn].trans = 0;
		g->obj[g->objn].re = 0;
	}
}

void			buttons7(int x, int y, t_global *g)
{
	if (g->objn && ft_strcmp(g->obj[g->objn].name, "sphere") == 0)
	{
		if (x > 550 && x < 650 && y > 650 && y < 750)
			init_tile(g->objn, "./tiles/space.xpm", g->obj, g);
		if (x > 650 && x < 750 && y > 650 && y < 750)
			init_tile(g->objn, "./tiles/moon.xpm", g->obj, g);
		if (x > 750 && x < 850 && y > 650 && y < 750)
			init_tile(g->objn, "./tiles/saturn.xpm", g->obj, g);
		if (x > 850 && x < 950 && y > 650 && y < 750)
			init_tile(g->objn, "./tiles/space1.xpm", g->obj, g);
		if (x > 550 && x < 650 && y > 750 && y < 850)
			init_tile(g->objn, "./tiles/uranus.xpm", g->obj, g);
		if (x > 650 && x < 750 && y > 750 && y < 850)
			init_tile(g->objn, "./tiles/venus.xpm", g->obj, g);
		if (x > 750 && x < 850 && y > 750 && y < 850)
			init_tile(g->objn, "./tiles/jupiter.xpm", g->obj, g);
		buttons8(x, y, g);
	}
}

void			buttons8(int x, int y, t_global *g)
{
	if (x > 850 && x < 950 && y > 750 && y < 850)
		init_tile(g->objn, "./tiles/helper.xpm", g->obj, g);
	if (x > 550 && x < 650 && y > 850 && y < 950)
		init_tile(g->objn, "./tiles/earth.xpm", g->obj, g);
	if (x > 650 && x < 750 && y > 850 && y < 950)
		init_tile(g->objn, "./tiles/brick.xpm", g->obj, g);
	if (x > 750 && x < 850 && y > 850 && y < 950)
		init_tile(g->objn, "./tiles/blank.xpm", g->obj, g);
	if (x > 850 && x < 950 && y > 850 && y < 950)
		init_tile(g->objn, "./tiles/sun.xpm", g->obj, g);
}

int				mouse_press(int button, int x, int y, void *param)
{
	t_global	*g;

	g = param;
	ft_bzero((int *)g->data_ptr, g->sz_l * HEIGHT);
	if (button == 1)
	{
		g->shot.x = -WIDTH / 2 + x;
		g->shot.y = HEIGHT / 2 - y;
		buttons1(x, y, g);
		buttons2(x, y, g);
		buttons3(x, y, g);
		buttons4(x, y, g);
		buttons5(x, y, g);
		buttons6(x, y, g);
		buttons7(x, y, g);
	}
	return (start_threads(recalc, g));
}
