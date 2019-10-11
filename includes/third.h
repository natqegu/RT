/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:30:50 by vkarpova          #+#    #+#             */
/*   Updated: 2019/10/11 18:30:50 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THIRD_H
# define THIRD_H

# include "first.h"
# include "second.h"

typedef	struct			s_dstpst
{
	double				dst;
	double				pst;
	struct s_object		obj;
}						t_dstpst;

typedef	struct			s_objecthit
{
	struct s_object		obj;
	struct s_vector		hit;
}						t_objecthit;

typedef struct			s_do_spec
{
	struct s_colbri		*ret;
	struct s_vector		*hitli;
	struct s_vector		reflrayv;
	struct s_object		obj;
}						t_do_spec;

#endif
