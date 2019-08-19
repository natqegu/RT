/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:52:40 by vkarpova          #+#    #+#             */
/*   Updated: 2019/02/01 17:52:41 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		usage(int o)
{
	if (o == 1)
		ft_putendl("Something wrong with file, try another one");
	ft_putendl("	usage: ./RT [example_scene.json]");
}


void		go(t_all *all)
{
	MLX_PTR = mlx_init();
	WIN_PTR = mlx_new_window(MLX_PTR, WIN_X, WIN_Y, "RT");
	IMG_PTR = mlx_new_image(MLX_PTR, WIN_X, WIN_Y);
	all->d = 1;
	all->size_line = WIN_X;
	all->bpp = 32;
	all->endian = 0;
	all->depth_refl_spec = 0;
	all->depth_refl = 0;
	all->depth_transp = 0;
	all->depth_max = 1;
	all->is_cam = 0;
	all->img =
	mlx_get_data_addr(IMG_PTR, &all->bpp, &all->size_line, &all->endian);

 	threads1(all);

	mlx_hook(WIN_PTR, 2, 5, event, all);
	mlx_hook(WIN_PTR, 4, 1L << 2, mouse_press, all);
	mlx_hook(WIN_PTR, 5, 1L << 3, mouse_release, all);
	mlx_hook(WIN_PTR, 6, 1L << 13, mouse_move, all);
	mlx_hook(WIN_PTR, 17, 1L << 17, x_close, all);

	mlx_loop(MLX_PTR);
}

int			main(int argc, char **argv)
{
	t_all		*all;

	all = (t_all *)malloc(sizeof(t_all));
	ft_bzero(all, sizeof(t_all));

	all->is_light = 0;
	all->loading = 0;
	all->start = 0;
	all->end = 0;

	if (argc == 2)
	{
		if (open_file(argv, all))
		{
			go(all);
		}
		else
			usage(1);
	}
	else
		usage(0);
	return (0);
}

int			x_close(t_all *all)
{
	mlx_clear_window(MLX_PTR, WIN_PTR);
	free(all);
	exit(0);
	return (0);
}
