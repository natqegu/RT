/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:41:33 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 18:41:33 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void			buttons1(int x, int y, t_global *g)
{
	if (x > 300 && x < 500 && y > 520 && y < 555)
	{
		if (g->objn < 1)
			g->objn = g->argc + 1;
		g->objn -= 1;
		if (g->obj[g->objn].rd == 0 && g->obj[g->objn].trans == 1)
			g->objn--;
	}
	if (x > 500 && x < 700 && y > 520 && y < 555)
	{
		g->objn = (g->objn + 1) % (g->argc + 1);
		if (g->obj[g->objn].rd == 0 && g->obj[g->objn].trans == 1)
			g->objn++;
	}
	if (x > 50 && x < 250 && y > 170 && y < 244)
		system("screencapture -i ~/Desktop/screen.png");
}

void			buttons2(int x, int y, t_global *g)
{
	if (x > 50 && x < 250 && y > 354 && y < 428)
	{
		if (g->objn && g->objn != g->argc)
		{
			g->obj[g->objn].rd = 0;
			g->obj[g->objn].trans = 1;
			g->obj[g->objn].rd2 = g->obj[g->objn].rd * g->obj[g->objn].rd;
			g->obj[g->objn].tile[0].data_ptr = NULL;
			g->objn++;
		}
	}
	if (x > 50 && x < 250 && y > 446 && y < 520)
	{
		if (g->music == 0)
		{
			g->music = 1;
			system("afplay ./music_4.mp3 &");
		}
		else
		{
			g->music = 0;
			system("killall afplay");
		}
	}
}

void			buttons3(int x, int y, t_global *g)
{
	if (x > 360 && x < 400 && y > 661 && y < 691)
	{
		g->obj[g->objn].spec++;
		if (g->obj[g->objn].spec > 10)
			g->obj[g->objn].spec = 10;
	}
	if (x > 400 && x < 440 && y > 661 && y < 691)
	{
		g->obj[g->objn].spec--;
		if (g->obj[g->objn].spec < 0)
			g->obj[g->objn].spec = 0;
	}
	if (x > 360 && x < 400 && y > 720 && y < 750)
	{
		g->obj[g->objn].re += 0.05;
		if (g->obj[g->objn].re > 0.75)
			g->obj[g->objn].re = 0.8;
	}
	if (x > 400 && x < 440 && y > 720 && y < 750)
	{
		g->obj[g->objn].re -= 0.05;
		if (g->obj[g->objn].re < 0.05)
			g->obj[g->objn].re = 0.01;
	}
}

void			buttons4(int x, int y, t_global *g)
{
	if (x > 360 && x < 400 && y > 784 && y < 814)
	{
		*g->ambient += 5;
		if (*g->ambient > 95)
			*g->ambient = 100;
	}
	if (x > 400 && x < 440 && y > 784 && y < 814)
	{
		*g->ambient -= 5;
		if (*g->ambient < 18)
			*g->ambient = 18;
	}
	if (x > 360 && x < 400 && y > 848 && y < 878)
	{
		g->obj[g->objn].trans += 0.05;
		if (g->obj[g->objn].trans > 0.75)
			g->obj[g->objn].trans = 0.8;
	}
	if (x > 400 && x < 440 && y > 848 && y < 878)
	{
		g->obj[g->objn].trans -= 0.05;
		if (g->obj[g->objn].trans < 0.05)
			g->obj[g->objn].trans = 0;
	}
}

void			buttons5(int x, int y, t_global *g)
{
	if (x > 360 && x < 400 && y > 912 && y < 942)
	{
		g->obj[g->objn].rd++;
		g->obj[g->objn].rd2 = g->obj[g->objn].rd * g->obj[g->objn].rd;
	}
	if (x > 400 && x < 440 && y > 912 && y < 942)
	{
		g->obj[g->objn].rd--;
		g->obj[g->objn].rd2 = g->obj[g->objn].rd * g->obj[g->objn].rd;
	}
	if (x > 750 && x < 950 && y > 170 && y < 220)
	{
		if (g->filter_switch == 1)
			return ;
		else
			make_sepia(g);
	}
	if (x > 750 && x < 950 && y > 230 && y < 280)
	{
		if (g->filter_switch == 2)
			return ;
		else
			make_gray_scale(g);
	}
}

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
		shot.x = -WIDTH / 2 + x;
		shot.y = HEIGHT / 2 - y;
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
