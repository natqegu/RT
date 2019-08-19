/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:49:55 by vkarpova          #+#    #+#             */
/*   Updated: 2019/04/23 16:49:56 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RT_H
# define FT_RT_H

# define WIN_X 400
# define WIN_Y 400
# define MLX_PTR all->mlx_ptr
# define WIN_PTR all->win_ptr
# define IMG_PTR all->img_ptr

# define MLX_PTR_2 all->mlx_ptr_2
# define WIN_PTR_2 all->win_ptr_2
# define IMG_PTR_2 all->img_ptr_2

# define PLANE 100
# define SPHERE 101
# define CYL 102
# define CONE 103
# define LIGHT 104
# define FON 0
# define INF 600000
# define CORES 36



# define KOEF 1e-9

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include "math.h"
# include "mlx.h"
# include "../libft/libft.h"






// typedef struct	s_cal
// {
// 	double		tmp;
// 	double		dirinv[2][2];
// 	double		point[2];
// 	double		det;
// 	double		p;
// 	double		q;
// }			t_cal;













typedef struct	s_clos
{
	t_list		*obj;
	double		clost;
	double		y;
}				t_clos;

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
	double		res;
	double		t1;
	double		t2;
	double		t;
}				t_vector;

typedef struct	s_light
{
	t_vector	pos;
	t_vector	direction;
	double		intense;
}				t_light;

typedef struct	s_plane
{
	double		r;
	t_vector	c;
	t_vector	v;
	int			color;
	double		specular;
	double		reflect;
	double		transp;
	double		tex;
}				t_plane;

typedef struct	s_cylinder
{
	double		r;
	t_vector	c;
	t_vector	v;
	int			color;
	double		specular;
	double		reflect;
	double		transp;
	double		tex;
}				t_cylinder;

typedef struct	s_sphere
{
	double		r;
	t_vector	c;
	int			color;
	double		specular;
	double		reflect;
	double		transp;
	double		tex;
}				t_sphere;

typedef struct	s_cone
{
	double		a;
	t_vector	c;
	t_vector	v;
	int			color;
	double		specular;
	double		reflect;
	double		transp;
	double		tex;
}				t_cone;

typedef struct	s_obj
{
	t_sphere	*sphere;
	t_cone		*cone;
	t_plane		*plane;
	t_cylinder	*cylinder;
}				t_obj;

typedef struct	s_vec
{
	t_vector	d;
	t_vector	v;
	t_vector	n;
	t_vector	p;
	t_vector	l;
	t_vector	o;
	t_vector	r;
}				t_vec;


typedef struct	s_mouse
{
	char		press;
	int			x;
	int			y;
}				t_mouse;

typedef struct	s_all
{
	t_clos		clos;

	t_vector	cam;
	t_list		*obj;
	t_list		*light;
	int			fd;
	t_vector	rot;
	double		closest;
	double		d;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;

	void		*mlx_ptr_2;
	void		*win_ptr_2;
	void		*img_ptr_2;

	char		*img;
	int			size_line;
	int			bpp;
	int			opp;
	int			endian;


	char		*img_2;
	int			color_2;
	t_vector	cam_2;



	int			color;

	int		x;
	int		x_max;
	int		depth_refl;
	int		depth_refl_spec;
	int		depth_transp;
	int		depth_max;
	t_mouse		mouse;
	int			shadow;
	int			is_cam;
	int			is_light;
	int			loading;
	int			start;
	int			end;
}				t_all;

t_vector		minus(t_vector a, t_vector b);
t_vector		plus(t_vector a, t_vector b);
t_vector		times(double n, t_vector a);
double			dot(t_vector a, t_vector b);
double			dlinna(t_vector a);
t_vector		norm(t_vector a);
// void			do_it(t_all *all);
void			*do_it(void *data_ptr);
t_vector		canvas_to_viewport(t_all *all, double x, double y);
// int				trace_ray(t_all *all, t_list *list, t_vector o, t_vector d);
t_clos			closer_obj(t_list *list, t_vector o, t_vector d, double min);
void			fig_normal(t_vec *vec, t_clos *clos);
double			fig_specular(t_list *list);
int				fig_color(t_list *list);
t_vector		fig_center(t_list *list);
void			plane_normal(t_vec *vec, t_plane *plan);
void			sphere_normal(t_vec *vec, t_sphere *sphr);
void			cyl_normal(t_vec *vec, double t, t_cylinder *cyl);
void			cone_normal(t_vec *vec, double t, t_cone *cone);
int				rgb_to_int(t_vector c);
t_vector		int_to_rgb(int rgb);
int				event(int key, t_all *all);
t_vector		intersect_ray(t_list *list, t_vector o, t_vector d);
t_vector		intersect_sphere(t_sphere *sphere, t_vector o, t_vector d);
t_vector		intersect_cyl(t_cylinder *cyl, t_vector o, t_vector d);
t_vector		intersect_cone(t_cone *c, t_vector o, t_vector d);
t_vector		intersect_plane(t_plane *plane, t_vector o, t_vector d);
int				reflected_color(t_all *all, t_clos clos, t_vec *vec);
double			diff(double intense, t_vec *vec);
// double			spec(double spec, double intense, t_vec *vec);
// int				color(double i, double j, t_clos clos);
int				x_close(t_all *all);
int				main(int argc, char **argv);
void			go(t_all *all);
void			pixel_put_img(t_all *all, int x, int y, int color);
void			usage(int o);
int				open_file(char **argv, t_all *all);
void			read_file(t_all *all);
int				save_light(t_all *all);
int				save_plane(t_all *all);
int				save_cylinder(t_all *all);
int				save_sphere(t_all *all);
int				save_cone(t_all *all);
double		fig_specular(t_list *list);
int				save_angle(t_all *all, double *angle);
int				save_radius(t_all *all, double *radius);
int				save_pos(t_all *all, t_vector *pos);
int				save_intense(t_all *all, double *intense);
int				save_color(t_all *all, int *color);
int				save_normal(t_all *all, t_vector *norm);
int				save_center(t_all *all, t_vector *center);
void			save_cam(char *line, t_all *all);
t_vector		init_vector(double x, double y, double z, double t);
void			save_rotation(t_all *all, char *line);
t_vector		rotation(t_all *all, t_vector canvas);
void			rotate_x(double angle, double *y, double *z);
void			rotate_y(double angle, double *x, double *z);
void			rotate_z(double angle, double *x, double *y);
int				num(char *str);
int				shadow(t_list *list, t_list *obj, t_vector o, t_vector d);
void  threads1(t_all *all);
void  *threads2(void *v);











int		trace_ray(t_all *all, t_list *list, t_vector o, t_vector d);
int		mouse_press(int button, int x, int y, t_all *all);
int		mouse_release(int button, int x, int y, t_all *all);
int		mouse_move(int x, int y, t_all *all);
void	rotat_x(t_all *all, double angle);
void	rotat_y(t_all *all, double angle);
void	rotat_z(t_all *all, double angle);




int			save_transp(t_all *all, double *transp);
int			save_shadow(t_all *all, double *shadow);
int			save_reflect(t_all *all, double *reflect);
int			save_specular(t_all *all, double *specular);
double		fig_specular(t_list *list);
double		fig_reflect(t_list *list);
double		fig_transp(t_list *list);
void			ambient_light(t_all *all, t_list **l);
t_vector		reflect(t_all *all, t_vec *vec, t_clos closer, t_vector local_color);
t_vector		reflect_spec(t_all *all, t_vec *vec, t_clos closer, t_vector local_color);
t_vector		transp(t_all *all, t_vec *vec, t_clos closer, t_vector local_color);
t_vector		new_color(t_vector local, t_vector ref, double param);
t_vector	get_random(t_vector vec1, t_vector vec2, double param);


double			spec(double spec, double intense, t_vec *vec, double reflect);
int				calc_color(double i, double j, t_vector color);


void		shadow_type(t_vector *color, t_vec *vec, t_list *light, t_all *all, t_clos clos);
void		soft_shadow(t_vector *color, t_vec *vec, t_list *light, t_all *all, t_clos clos);


int			event_2(int key, t_all *all);


void	miss_open_brackets(t_all *all);
void	miss_closed_brackets(t_all *all);
void	save_objects(t_all *all);
int		save_texture(t_all *all, double *texture);
double		fig_texture(t_list *list);






void	stereoscopy(t_all *all);
void		blue_stereo(t_all *all);
void		red_stereo(t_all *all);
void		pixel_put_img_2(t_all *all, int x, int y, int color);



#endif
