/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:35:51 by vkarpova          #+#    #+#             */
/*   Updated: 2019/10/11 18:35:52 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIRST_H
# define FIRST_H

# define WIDTH HEIGHT
# define HEIGHT 400
# define WHOLE_MENU 1000
# define WINDOW_START_X 300
# define WINDOW_START_Y 120
# define WIDTH_2 200
# define HEIGHT_2 WIDTH_2
# define TASK 20
# define STRIPS HEIGHT / TASK
# define CORES 16
# define M_T 6.28318530718
# define MAX_REC 3

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <pthread.h>
# include <fcntl.h>
# include <stdarg.h>

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_3_vecs
{
	t_vector		one;
	t_vector		*two;
	t_vector		three;
}					t_3_vecs;

typedef	struct		s_colbri
{
	t_vector		col;
	t_vector		colself;
	t_vector		nrm;
	int				bri;
}					t_colbri;

typedef	struct		s_tile
{
	int				bpp;
	int				sz_l;
	int				e;
	int				w;
	int				h;
	int				w2;
	int				h2;
	int				mipq;
	int				*data_ptr;
	void			*ptr;
}					t_tile;

typedef struct		s_hunia
{
	int				o;
	t_colbri		*cur;
	t_3_vecs		co;
}					t_hunia;

typedef struct		s_masi
{
	double			*s;
	int				*obss;
	int				*io;
}					t_masi;

#endif
