/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fourth.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:32:45 by vkarpova          #+#    #+#             */
/*   Updated: 2019/10/11 18:32:46 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOURTH_H
# define FOURTH_H

# include "first.h"
# include "second.h"

typedef struct			s_global
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	void				*img_ptr_2;
	int					*data_ptr;
	int					*data_ptr_2;
	int					bpp;
	int					sz_l;
	int					e;
	int					id;
	int					light_switch;
	int					filter_switch;
	int					music;
	struct s_vector		fifteen;
	struct s_vector		base[3];
	struct s_vector		*ray;
	struct s_vector		*li;
	struct s_vector		*cam_pos;
	double				*liz;
	struct s_vector		*angle;
	struct s_vector		*normal;
	struct s_object		*obj;
	struct s_object		*all_obj;
	struct s_objecthit	***hits;
	struct s_vector		***rays;
	struct s_vector		white;
	int					objn;
	int					argc;
	pthread_t			tid[CORES];
	int					core;
	int					prim;
	int					*ambient;
	int					my_line;
	int					*line_taken;
	int					mip_map;
	pthread_mutex_t		mutex;
	int					lights;
	struct s_vector		*savehitli;
	struct s_vector		prev;
	double				*cosa;
	struct s_vector		*hitli;
	struct s_vector		*ctrli;
	struct s_global		*tcps[CORES];
	int					*recursion;
	t_vector			shot;
}						t_global;

#endif
