#include "rt.h"

int		mouse_press(int button, int x, int y, void *param)
{
	t_global *g;

	g = param;
	ft_bzero((int *)g->data_ptr, g->sz_l * HEIGHT);
	if (button == 1)
	{
		shot.x = -WIDTH / 2 + x;
		shot.y = HEIGHT / 2 - y;
		// printf("\n%f, %f\n", shot.x, shot.y);
//		printf("object is %d %s %f, %f, %f\n%f,%f, %f\n", g->objn, a.name, a.ctr->x, a.ctr->y, a.ctr->z, a.nr.x, a.nr.y, a.nr.z);
		// printf("mouse press -> realc\n");

		if (x > 300 && x < 500 && y > 520 && y < 555)
    	{
			if (g->objn < 1)
				g->objn = g->argc + 1;
			g->objn -= 1;
    		//object--
    	}
		if (x > 500 && x < 700 && y > 520 && y < 555)
    	{
			g->objn = (g->objn + 1) % (g->argc + 1);
    		//object++
    	}

		if (x > 50 && x < 250 && y > 170 && y < 244)
    	{
			system("screencapture -i ~/Desktop/screen.png");
    		//screenshot
    	}
    	if (x > 50 && x < 250 && y > 262 && y < 336)
    	{
			
			int i = 0;
			while (i < 100)
			{
				ft_bzero((int *)g->data_ptr, g->sz_l * HEIGHT);
				int j = 0;
				while (j < 2)
				{
					g->obj[g->objn].ctr->y++;
					start_threads(recalc, g);
					
					printf("ctr->x: %f", g->obj[g->objn].ctr->x);
					j++;
				}
				i++;
			}
    		//animation
    	}
    	if (x > 50 && x < 250 && y > 354 && y < 428)
    	{
    		//memes
    	}
    	if (x > 50 && x < 250 && y > 446 && y < 520)
    	{
    		//music
    	}



    	if (x > 360 && x < 400 && y > 661 && y < 691)
    	{
    		//mip-map - on
    	}
    	if (x > 400 && x < 440 && y > 661 && y < 691)
    	{
    		//mip-map - off
    	}
    	if (x > 360 && x < 400 && y > 720 && y < 750)
    	{
    		//reflection++
    	}
    	if (x > 400 && x < 440 && y > 720 && y < 750)
    	{
    		//reflection--
    	}
    	if (x > 360 && x < 400 && y > 784 && y < 814)
    	{
			*g->ambient += 5;
			printf("ambient %d\n", *g->ambient);
    	}
    	if (x > 400 && x < 440 && y > 784 && y < 814)
    	{
			*g->ambient -= 5;
			printf("ambient %d\n", *g->ambient);
    	}
    	if (x > 360 && x < 400 && y > 848 && y < 878)
    	{
    		//transparency++
    	}
    	if (x > 400 && x < 440 && y > 848 && y < 878)
    	{
    		//transparency--
    	}
    	if (x > 360 && x < 400 && y > 912 && y < 942)
    	{
			g->obj[g->objn].rd++;
			start_threads(recalc, g);
			printf("RADIUS %d\n", g->obj[g->objn].rd);
    		//radius++
    	}
    	if (x > 400 && x < 440 && y > 912 && y < 942)
    	{
			g->obj[g->objn].rd--;
			start_threads(recalc, g);
			printf("RADIUS %d\n", g->obj[g->objn].rd);
    		//radius--
    	}



    	if (x > 750 && x < 950 && y > 170 && y < 220)
    	{
    		//sepia
    	}
    	if (x > 750 && x < 950 && y > 230 && y < 280)
    	{
    		//black-white
    	}
    	if (x > 750 && x < 950 && y > 290 && y < 340)
    	{
    		//negative
    	}
    	if (x > 750 && x < 950 && y > 350 && y < 400)
    	{
    		//stereoscopy
    	}
    	if (x > 750 && x < 950 && y > 410 && y < 460)
    	{
    		//bright
    	}
    	if (x > 750 && x < 950 && y > 470 && y < 530)
    	{
    		//cartoon
    	}




    	if (x > 550 && x < 650 && y > 650 && y < 750)
    	{
			g->obj[g->objn].tile[0].data_ptr = NULL;
			init_tile(g->objn, "./tiles/space.xpm", g->obj, g);
    		//texture 1
    	}
    	if (x > 650 && x < 750 && y > 650 && y < 750)
    	{
			g->obj[g->objn].tile[0].data_ptr = NULL;
			init_tile(g->objn, "./tiles/moon.xpm", g->obj, g);
    		//texture 2
    	}
    	if (x > 750 && x < 850 && y > 650 && y < 750)
    	{
			g->obj[g->objn].tile[0].data_ptr = NULL;
			init_tile(g->objn, "./tiles/saturn.xpm", g->obj, g);
    		//texture 3
    	}
    	if (x > 850 && x < 950 && y > 650 && y < 750)
    	{
			g->obj[g->objn].tile[0].data_ptr = NULL;
			init_tile(g->objn, "./tiles/space1.xpm", g->obj, g);
    		//texture 4
    	}
    	if (x > 550 && x < 650 && y > 750 && y < 850)
    	{
			g->obj[g->objn].tile[0].data_ptr = NULL;
			init_tile(g->objn, "./tiles/uranus.xpm", g->obj, g);
    		//texture 5
    	}
    	if (x > 650 && x < 750 && y > 750 && y < 850)
    	{
			g->obj[g->objn].tile[0].data_ptr = NULL;
			init_tile(g->objn, "./tiles/venus.xpm", g->obj, g);
    		//texture 6
    	}
    	if (x > 750 && x < 850 && y > 750 && y < 850)
    	{
			g->obj[g->objn].tile[0].data_ptr = NULL;
			init_tile(g->objn, "./tiles/jupiter.xpm", g->obj, g);
    		//texture 7
    	}
    	if (x > 850 && x < 950 && y > 750 && y < 850)
    	{
			g->obj[g->objn].tile[0].data_ptr = NULL;
			init_tile(g->objn, "./tiles/helper.xpm", g->obj, g);
    		//texture 8
    	}
    	if (x > 550 && x < 650 && y > 850 && y < 950)
    	{
			g->obj[g->objn].tile[0].data_ptr = NULL;
			init_tile(g->objn, "./tiles/earth.xpm", g->obj, g);
    		//texture 9
    	}
    	if (x > 650 && x < 750 && y > 850 && y < 950)
    	{
			g->obj[g->objn].tile[0].data_ptr = NULL;
			init_tile(g->objn, "./tiles/brick.xpm", g->obj, g);
    		//texture 10
    	}
    	if (x > 750 && x < 850 && y > 850 && y < 950)
    	{
			g->obj[g->objn].tile[0].data_ptr = NULL;
			init_tile(g->objn, "./tiles/blank.xpm", g->obj, g);
    		//texture 11
    	}
    	if (x > 850 && x < 950 && y > 850 && y < 950)
    	{
			g->obj[g->objn].tile[0].data_ptr = NULL;
			init_tile(g->objn, "./tiles/sun.xpm", g->obj, g);
    		//texture 12
    	}
		start_threads(move, g);
	}
	
	return (start_threads(recalc, g));
}