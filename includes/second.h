/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:27:08 by vkarpova          #+#    #+#             */
/*   Updated: 2019/10/11 18:27:11 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECOND_H
# define SECOND_H

# include "rt.h"
# include "first.h"
# include "fourth.h"

typedef struct			s_object
{
	char				*name;
	int					id;
	int					cam_pos;
	struct s_dstpst		(*hit)(struct s_vector, struct s_vector,
						struct s_vector, struct s_object *);
	struct s_colbri		(*bright)(struct s_vector, struct s_vector,
						struct s_object *, struct s_global *);
	struct s_colbri		(*simple_bright)(struct s_vector, struct s_vector,
						struct s_object *, struct s_global *);
	t_vector			bd1;
	t_vector			bd2;
	t_vector			bd3;
	t_vector			base[3];
	t_tile				tile[15];
	t_vector			*ctr;
	t_vector			ang;
	t_vector			color;
	int					rd;
	t_vector			nr;
	int					spec;
	int					rd2;
	t_vector			**pts;
	struct s_object		*tris;
	double				re;
	double				trans;
	t_vector			ptdim;
	struct s_object		*frame;
	t_vector			box[8];
	int					soft;
}						t_object;

#endif
