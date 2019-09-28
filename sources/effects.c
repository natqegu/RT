/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:02:01 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/24 15:02:02 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"


void	make_sepia(t_global *g)
{
	t_vector	c;
	int			color;
	int			j;

	g->filter_switch = 1;
	j = g->objn;
	if (j == 0)
		j = 1;
	while (j < g->argc + 1)
	{
		if (g->obj[j].tile[0].data_ptr != NULL)
			tile_sepia(g, j);
		else
		{
			printf("color sepia\n");
			c = g->obj[j].color;
			g->obj[j].color.x = ((c.x * 0.393f) + (c.y * 0.769f) + (c.z * 0.189f));
			g->obj[j].color.y = ((c.x * 0.349f) + (c.y * 0.686f) + (c.z * 0.168f));
			g->obj[j].color.z = ((c.x * 0.272f) + (c.y * 0.534f) + (c.z * 0.131f));
		}
		j++;
	}
}

void	tile_sepia(t_global *g, int id)
{
	int k = 1;
	int s = 0;

	printf("effect sepia\n");
	while (k < 10)
	{
		s = 0;
		sepia_2(g->obj[id].tile[k].data_ptr,g->obj[id].tile[k].w, g->obj[id].tile[k].h, g);
		k++;
	}
	g->obj[id].tile[0].mipq = fmin(log2(g->obj[id].tile[0].h), log2(g->obj[id].tile[0].w));
}

void	sepia_2(int *a, int w, int h, t_global *g)
{
	int			i;
	int			j;
	int			*orig;
	t_vector	sepia;
	t_vector	c;

	j = 0;
	orig = (int *)malloc(sizeof(int) * w * h + 1);
	save_im(a, orig, w, h);
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			c = rgb(*(orig + (j * w + i)));
			sepia.x = lround(0.09 * ((c.x * 0.393f) + (c.y * 0.769f) + (c.z * 0.189f)));
			sepia.y = lround(0.09 * ((c.x * 0.349f) + (c.y * 0.686f) + (c.z * 0.168f)));
			sepia.z = lround(0.09 * ((c.x * 0.272f) + (c.y * 0.534f) + (c.z * 0.131f)));
			*(a + (j * w + i)) = brg(sepia);
			g->ray->x = i - h / 2;
			g->ray->y = -j + w / 2;
			i++;
		}
		j++;
	}
}



















void	make_gray_scale(t_global *g)
{
	t_vector	c;
	int			color;
	int			j;
	double		a;

	g->filter_switch = 2;
	j = g->objn;
	if (j == 0)
		j = 1;
	while (j < g->argc + 1)
	{
		if (g->obj[j].tile[0].data_ptr != NULL)
			tile_gray_scale(g, j);
		else
		{
			printf("color gray scale\n");
			c = g->obj[j].color;
			a = (c.x * 0.3f + c.y * 0.59f + c.z * 0.11f);
			g->obj[j].color.x = a;
			g->obj[j].color.y = a;
			g->obj[j].color.z = a;
		}
		j++;
	}
}

void	tile_gray_scale(t_global *g, int id)
{
	int k = 1;
	int s = 0;
	int	i;

	i = g->objn;
	if (i == 0)
		i += 1;
	while (k < 2)
	{
		s = 0;
		gray_scale_2(g->obj[id].tile[k].data_ptr, g->obj[id].tile[k].w, g->obj[id].tile[k].h, g);
		k++;
	}
	// g->obj[id].tile[0].mipq = fmin(log2(g->obj[id].tile[0].h), log2(g->obj[id].tile[0].w));

}

void	gray_scale_2(int *a, int w, int h, t_global *g)
{
	int i;
	int j;
	int *orig;
	int		color;
	t_vector bw;
	t_vector c;
	int		m;

	j = 0;
	orig = (int *)malloc(sizeof(int) * w * h + 1);
	save_im(a, orig, w, h);
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			c = rgb(*(orig + (j * w + i)));
			
			m = (c.x * 0.3f + c.y * 0.59f + c.z * 0.11f);
			bw.x = lround(0.0039 * m);
			bw.y = lround(0.0039 * m);
			bw.z = lround(0.0039 * m);
			*(a + (j * w + i)) = brg(bw);
			g->ray->x = i - h / 2;
			g->ray->y = -j + w / 2;
			i++;
		}
		j++;
	}
}



























void	make_negative(t_global *g)
{
	t_vector	c;
	int			color;
	int			j;

	g->filter_switch = 3;
	j = g->objn;
	if (j == 0)
		j = 1;
	while (j < g->argc + 1)
	{
		if (g->obj[j].tile[0].data_ptr != NULL)
			tile_negative(g, j);
		else
		{
			printf("color negative\n");
			c = g->obj[j].color;
			g->obj[j].color.x = (fabs(1.0f - g->obj[j].color.x));
			g->obj[j].color.y = (fabs(1.0f - g->obj[j].color.y));
			g->obj[j].color.z = (fabs(1.0f - g->obj[j].color.z));
		}
		j++;
	}
}

void	tile_negative(t_global *g, int id)
{
	int k = 1;
	int s = 0;
	int	i;

	i = g->objn;
	if (i == 0)
		i += 1;
	while (k < 2)
	{
		s = 0;
		negative_2(g->obj[id].tile[k].data_ptr, g->obj[id].tile[k].w, g->obj[id].tile[k].h, g);
		k++;
	}
	g->obj[id].tile[0].mipq = fmin(log2(g->obj[id].tile[0].h), log2(g->obj[id].tile[0].w));
}

void	negative_2(int *a, int w, int h, t_global *g)
{
	int i;
	int j;
	int *orig;
	int		color;
	t_vector neg;
	t_vector c;
	int		m;

	j = 0;
	orig = (int *)malloc(sizeof(int) * w * h + 1);
	save_im(a, orig, w, h);
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			c = rgb(*(orig + (j * w + i)));
			neg.x = 255 - c.x;
			neg.y = 255 - c.y;
			neg.z = 255 - c.z;
			*(a + (j * w + i)) = brg(neg);
			g->ray->x = i - h / 2;
			g->ray->y = -j + w / 2;
			i++;
		}
		j++;
	}
}














// double			dlinna(t_vector a)
// {
// 	t_vector	res;

// 	res.x = sqrt(dot(a, a));
// 	return (res.x);
// }

// int				rgb_to_int(t_vector c)
// {
// 	int		rgb;

// 	rgb = c.x;
// 	rgb = (rgb << 8) + c.y;
// 	rgb = (rgb << 8) + c.z;
// 	return (rgb);
// }

// t_vector		int_to_rgb(int rgb)
// {
// 	t_vector	c;

// 	c.x = (rgb >> 16) & 0xFF;
// 	c.y = (rgb >> 8) & 0xFF;
// 	c.z = rgb & 0xFF;
// 	return (c);
// }

// int				calc_color(double i, double j, t_vector color)
// {
// 	color.x += j * 255;
// 	color.y += j * 255;
// 	color.z += j * 255;
// 	color.x *= i;
// 	color.y *= i;
// 	color.z *= i;
// 	if (color.x > 255)
// 		color.x = 255;
// 	if (color.y > 255)
// 		color.y = 255;
// 	if (color.z > 255)
// 		color.z = 255;
// 	if (color.x < 0)
// 		color.x = 0;
// 	if (color.y < 0)
// 		color.y = 0;
// 	if (color.z < 0)
// 		color.z = 0;
// 	return (rgb_to_int(color));
// }



// int		catroon(t_global *g, int j)
// {
// 	double		dif;
// 	double		spec;
// 	double		nl;
// 	t_vector	r;
// 	double		rv;

// 	// make_gray_scale(g);
// 	g->light_switch = 1;
// 	// g->light_switch = (g->light_switch + 1) % (2 + g->lights);
// 	dif = 0;
// 	nl = dot(g->obj[j].ang, *g->li);
// 	if (nl > 0)
// 		dif = 2 * nl / (dlinna(g->obj[j].ang) * dlinna(*g->li));
// 	r = diff(scale(2 * dot(g->obj[j].ang, *g->li), g->obj[j].ang), *g->li);
// 	rv = dot(r, g->obj[j].ang);
// 	if (rv > 0)
// 		spec = 2 * pow((rv / (dlinna(r) * dlinna(g->obj[j].ang))), 100);

// 	// printf("color = %d\n", (calc_color(dif, spec, g->obj[j].color)));
// 	return ((calc_color(dif, spec, g->obj[j].color)));
// }

// void	make_cartoon(t_global *g)
// {
// 	t_vector	c;
// 	int			color;
// 	int			j;

// 	g->filter_switch = 5;
// 	j = g->objn;
// 	if (j == 0)
// 		j = 1;
// 	j++;
// 	while (j < g->argc + 1 && j < 4)
// 	{
// 		// if (g->obj[j].tile[0].data_ptr != NULL)
// 		// 	tile_cartoon(g, j);
// 		// else
// 		// {
// 			printf("color cartoon\n");

// 			g->obj[j].color = rgb(catroon(g, j));
// 			// c = g->obj[j].color;
// 			// g->obj[j].color.x = lround(1.6 * c.x);
// 			// g->obj[j].color.y = lround(1.6 * c.y);
// 			// g->obj[j].color.z = lround(1.6 * c.z);
// 		// }
// 		j++;
// 	}
// }

// void	tile_cartoon(t_global *g, int id)
// {
// 	int k = 1;
// 	int s = 0;
// 	int	i;

// 	printf("effect cartoon\n");
// 	i = g->objn;
// 	if (i == 0)
// 		i += 1;
// 	while (k < 2)
// 	{
// 		s = 0;
// 		cartoon_2(g->obj[id].tile[k].data_ptr, g->obj[id].tile[k].w, g->obj[id].tile[k].h, g);
// 		k++;
// 	}
// 	// g->obj[id].tile[0].mipq = fmin(log2(g->obj[id].tile[0].h), log2(g->obj[id].tile[0].w));
// }

// void	cartoon_2(int *a, int w, int h, t_global *g)
// {
// 	int i;
// 	int j;
// 	int *orig;
// 	int		color;
// 	t_vector br;
// 	t_vector c;
// 	int		m;

// 	j = 0;
// 	orig = (int *)malloc(sizeof(int) * w * h + 1);
// 	save_im(a, orig, w, h);
// 	while (j < h)
// 	{
// 		i = 0;
// 		while (i < w)
// 		{
// 			c = rgb(*(orig + (j * w + i)));
// 			// int factor = (259 * (128 + 255)) / (255 * (259 - 128));
// 			// int factor = 10;
// 			// br.x = lround(factor * (c.x - 128) + 128);
// 			// br.y = lround(factor * (c.y - 128) + 128);
// 			// br.z = lround(factor * (c.z - 128) + 128);
// 			br.x = ((c.x * 0.393f) + (c.y * 0.769f) + (c.z * 0.189f));
// 			br.y = ((c.x * 0.349f) + (c.y * 0.686f) + (c.z * 0.168f));
// 			br.z = ((c.x * 0.272f) + (c.y * 0.534f) + (c.z * 0.131f));
// 			br.x = lround(0.002 * br.x);
// 			br.y = lround(0.002 * br.y);
// 			br.z = lround(0.002 * br.z);
// 			*(a + (j * w + i)) = brg(br);
// 			g->ray->x = i - h / 2;
// 			g->ray->y = -j + w / 2;
// 			i++;
// 		}
// 		j++;
// 	}
// }















































void		blue_stereo(t_global *g)
{
	int	x;
	int	y;
	int	pos;


	pos = 0;
	x = -1;
	while (++x <= WIDTH)
	{
		y = - 1;
		while (++y <= HEIGHT)
		{
			pos = (y * WIDTH + x);
			*(g->data_ptr_2 + pos) += (*(g->data_ptr + pos) / 1.5);
			*(g->data_ptr_2 + pos + 1) += (*(g->data_ptr + pos + 1) / 1.5);
		}
	}
}

void		red_stereo(t_global *g)
{
	int	x;
	int	y;
	int	pos;

	pos = 0;
	x = -1;
	while (++x <= WIDTH)
	{
		y = - 1;
		while (++y <= HEIGHT)
		{
			pos = (y * WIDTH + x);
			*(g->data_ptr_2 + pos + 2) += (*(g->data_ptr + pos + 2) / 1.5);
		}
	}
}


void		stereoscopy(t_global *g)
{
	g->img_ptr_2 = mlx_new_image(g->mlx_ptr, WIDTH, HEIGHT);
	g->data_ptr_2 =
	(int*)mlx_get_data_addr(g->img_ptr_2, &g->bpp, &g->sz_l, &g->e);

	init_vector(g->cam_pos, -6, 0, 0);
	start_threads(recalc, g);
	blue_stereo(g);

	init_vector(g->cam_pos, 6, 0, 0);
	start_threads(recalc, g);
	red_stereo(g);

	g->img_ptr = g->img_ptr_2;
}

void	make_stereo(t_global *g)
{
	t_vector	c;
	int			color;
	int			j;

	g->filter_switch = 4;
	j = g->objn;
	if (j == 0)
		j = 1;
	*g->ambient = 100;
	while (j < g->argc + 1)
	{
		g->obj[j].soft = 0;
		g->obj[j].trans = 0;
		g->obj[j].spec = 0;
		g->obj[j].re = 0;
		stereoscopy(g);
		j++;
	}
}

































void	make_smooth(t_global *g)
{
	t_vector	c;
	int			color;
	int			j;


	g->filter_switch = 6;
	j = g->objn;
	if (j == 0)
		j = 1;
	while (j < g->argc + 1)
	{
		if (g->obj[j].tile[0].data_ptr != NULL)
			tile_smooth(g, j);
		else
		{
			printf("color smooth - ничего не делает пока что\n");
			c = g->obj[j].color;
			g->obj[j].color.x = ((c.x - 1e-10) * 6 / 5);
			g->obj[j].color.y = ((c.y - 1e-10) * 6 / 5);
			g->obj[j].color.z = ((c.z - 1e-10) * 6 / 5);
		}
		j++;
	}
}


void	tile_smooth(t_global *g, int id)
{
	int k = 1;
	int s = 0;

	printf("effect smooth\n");
	while (k < 2)
	{
		s = 0;
		smooth(g->obj[id].tile[k].data_ptr, g->obj[id].tile[k].w,
			g->obj[id].tile[k].h,g->obj[id].tile[k].w / exp2(k),
			g->obj[id].tile[k].h / exp2(k), g);
		while (s++ < k)
			stretch(g->obj[id].tile[k].data_ptr, g->obj[id].tile[k].w , g->obj[id].tile[k].h);
		k++;
	}
	g->obj[id].tile[0].mipq = fmin(log2(g->obj[id].tile[0].h), log2(g->obj[id].tile[0].w));
}








