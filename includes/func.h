/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:33:01 by vkarpova          #+#    #+#             */
/*   Updated: 2019/10/11 18:33:01 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

# include "rt.h"

typedef struct s_vector		t_vector;
typedef struct s_3_vecs		t_3_vecs;
typedef struct s_object		t_object;
typedef struct s_colbri		t_colbri;
typedef struct s_dstpst		t_dstpst;
typedef struct s_objecthit	t_objecthit;
typedef struct s_global		t_global;

t_do_spec			cr_spec(t_colbri *ret, t_vector *hitli,
					t_vector reflrayv, t_object obj);
void				do_1_spec(t_colbri *tmp, t_do_spec sp, t_global *g,
					int i);
t_3_vecs			create_3_vecs(t_vector one, t_vector *two,
					t_vector three);
void				sphere_1(t_global *g);
void				sphere_2(t_global *g);
void				do_spec(t_colbri *ret, t_3_vecs co, t_object obj,
					t_global *g);
void				free_n(int nbr, ...);
int					brg(t_vector rgb);
double				dot(t_vector a, t_vector b);
t_vector			diff(t_vector a, t_vector b);
t_vector			sum(t_vector a, t_vector b);
t_vector			norm(t_vector a);
int					color(int b, t_vector c);
t_vector			scale(double a, t_vector b);
void				ginit(t_global *g);
void				init_plane(t_vector *ctr, int i, t_global *g);
void				init_cylinder(t_vector *ctr, int i, t_global *g);
void				init_sphere(t_vector *ctr, int i, t_global *g);
void				init_spheror(t_vector *ctr, int i, t_global *g);
void				init_cone(t_vector *ctr, int i, t_global *g);
void				init_tri(t_vector *ctr, int i, t_global *g);
void				init_complex(t_vector *ctr, int i, t_global *g);
int					mouse_press(int button, int x, int y, void *param);
void				init_tile(int i, char *tile, t_object *obj,
					t_global *g);
int					check_arg(char **argv, int argc, t_global *g);
int					arg_valid(char **argv);
int					fill_objects(t_vector *ctr, char **argv, t_global *g);
void				fill_obj(char **argv, int n, t_global *g);
void				vectorify(void *obj_coord, char **argv);
int					is_coords(char *argv);
int					putstr(char *s, int ret);
void				free_arr(char **arr);
int					init_objects(t_vector *ctr, char **argv, t_global *g);
int					obj_traver(char **argv, char *c);
void				init_rays(t_vector ****ray);
void				init_hits(t_objecthit ***hits);
int					key_press(int kk, void *param);
void				copy_tcps(t_global *g);
void				copy(t_global *tcps, t_global *g);
int					move_obj(int kk, t_global *g);
int					move_phys(int keycode, t_global *g);
void				move_cam(char s, t_global *g);
int					free_hits(t_global *g);
int					start_threads(void *f, t_global *g);
int					mouse_move(int x, int y, void *param);
void				debug(t_global *g);
void				*recalc(void *p);
void				*move(void *p);
void				*toimg(void *tcp);
double				len2(t_vector a);
t_dstpst			*nani(t_dstpst *t);
void				objecthit(t_dstpst *ret, t_3_vecs co, t_object *obj,
					int objc);
t_dstpst			hit_plane(t_vector st, t_vector end, t_vector ray,
					t_object *obj);
t_colbri			bright_spheror(t_vector st, t_vector hit,
					t_object obj, t_global *g);
t_colbri			simple_bright_spheror(t_vector st, t_vector hit,
					t_object obj, t_global *g);
t_colbri			simple_bright_sphere(t_vector st, t_vector hit,
					t_object *obj, t_global *g);
t_colbri			bright_sphere(t_vector st, t_vector hit,
					t_object *obj, t_global *g);
t_colbri			simple_bright_plane(t_vector st, t_vector hit,
					t_object *obj, t_global *g);
t_colbri			bright_plane(t_vector st, t_vector hit, t_object *obj,
					t_global *g);
t_colbri			bright_sphere(t_vector st, t_vector hit, t_object *obj,
					t_global *g);
t_colbri			simple_bright_sphere(t_vector st, t_vector hit,
					t_object *obj, t_global *g);
t_dstpst			hit_sphere(t_vector st, t_vector end, t_vector ray,
					t_object *obj);
t_dstpst			hit_cylinder(t_vector st, t_vector end, t_vector ray,
					t_object *obj);
t_colbri			bright_cylinder(t_vector st, t_vector hit, t_object *obj,
					t_global *g);
t_colbri			simple_bright_cylinder(t_vector st, t_vector hit,
					t_object *obj, t_global *g);
t_colbri			bright_cone(t_vector st, t_vector hit, t_object *obj,
					t_global *g);
t_colbri			simple_bright_cone(t_vector st, t_vector hit,
					t_object *obj, t_global *g);
t_colbri			bright_tri(t_vector st, t_vector hit, t_object *obj,
					t_global *g);
t_colbri			simple_bright_tri(t_vector st, t_vector hit,
					t_object *obj, t_global *g);
int					file_height(char *filename);
int					parse_line(t_vector **a, char *s, int j,
					t_vector *ptdim);
void				shift_center(t_vector **pts, t_vector *ptdim, t_global *g);
void				init_tile(int i, char *tile, t_object *obj, t_global *g);
t_dstpst			hit_cone(t_vector st, t_vector end, t_vector ray,
					t_object *obj);
t_dstpst			hit_tri(t_vector st, t_vector end, t_vector ray,
					t_object *obj);
t_dstpst			hit_complex(t_vector st, t_vector end,
					t_vector ray, t_object *obj);
void				alias(int *dst, int *a, int w, int h,
					int xmax, int ymax);
t_dstpst			*nani(t_dstpst *t);
void				obstructed(t_colbri *i, t_3_vecs co, t_object *obj,
					t_global *g);
t_vector			rotate(t_vector ray, t_vector angle);
void				init_vector(t_vector *current, double x, double y,
					double z);
int					con(t_global *g);
t_vector			rgb(int c);
t_vector			base(t_vector c);
int					pinside(t_vector p, t_object object, t_vector nr);
void				screen(int *a, int w, int h, t_global *g);
t_vector			cross(t_vector a, t_vector b);
double				det(t_vector a, t_vector b);
void				stretch(int *a, int d, int h);
void				smooth(int *a, int w, int h, int xmax, int ymax,
					t_global *g);
void				save_im(int *a, int *b, int w, int h);
t_vector			base255(t_vector dir);
void				white(int *a, int w, int h, int c);
t_vector			**initialize_points(int height);
t_vector			**create_points(char *filename, t_vector *ptdim,
					t_global *g);
void				free_points(t_vector **pts);
double				mymod(double x, int m);
double				myacos(t_vector ax, t_vector v, t_vector nrm);
int					myintmod(int x, int m);
int					left(t_vector a, t_vector b, t_vector nrm);
t_object			*init_frame(t_object obj, t_global *g);
t_object			*create_tris(t_vector **pts, t_object obj,
					t_global *g);
double				tothe2(double x, int e);
int					x_close(t_global *g);
void				tile_sepia(t_global *g, int id);
void				tile_gray_scale(t_global *g, int id);
void				tile_negative(t_global *g, int id);
void				tile_cartoon(t_global *g, int id);
void				tile_smooth(t_global *g, int id);
void				make_sepia(t_global *g);
void				make_gray_scale(t_global *g);
void				make_negative(t_global *g);
void				make_stereo(t_global *g);
void				make_cartoon(t_global *g);
void				make_smooth(t_global *g);
void				sepia_2(int *a, int w, int h, t_global *g);
void				gray_scale_2(int *a, int w, int h, t_global *g);
void				negative_2(int *a, int w, int h, t_global *g);
void				cartoon_2(int *a, int w, int h, t_global *g);
void				red_stereo(t_global *g);
void				blue_stereo(t_global *g);
void				stereoscopy(t_global *g);
int					mouse_press(int button, int x, int y, void *param);
int					x_close(t_global *g);
t_colbri			refl(t_vector refl, t_vector hit, t_global *g);
t_vector			reflray(t_vector st, t_vector end, t_vector nrm);
void				init_hitli(t_vector *hitli, t_vector hit,
					t_global *g);
void				init_bri(int *bri, t_vector *hitli, t_vector nrm,
					t_global *g);
void				do_re(t_vector refl, t_vector hit, t_object *obj,
					t_global *g);
void				make_motion(t_global *g);
void				do_trans(t_3_vecs co, t_colbri *ret, t_object obj,
					t_global *g);
t_vector			mip_col(double x, double y, double dst2, t_object obj,
					t_global *g);
void				buttons1(int x, int y, t_global *g);
void				buttons2(int x, int y, t_global *g);
void				buttons3(int x, int y, t_global *g);
void				buttons4(int x, int y, t_global *g);
void				buttons5(int x, int y, t_global *g);
void				buttons6(int x, int y, t_global *g);
void				buttons7(int x, int y, t_global *g);
void				buttons8(int x, int y, t_global *g);
t_vector			*norm_tile(int *tile, int w, int h);
void				init_tile_2(int i, char *tile, t_object *obj,
					t_global *g);
void				copy2(t_global *tcps, t_global *g);
void				menu(t_global	*g);
int					num(char *str);
int					usage(int o);
int					parse_color(char *line, t_vector *vector);
void				free_n(int nbr, ...);
int					parse_vector(char *line, t_vector *vector);
int					parse_angle(char *line, t_vector *vector);
int					parse_int(char *line, int *number, int divisor,
					int max);
int					parse_double(char *line, double *number,
					double divisor, double max);
void				parse_init_tile_2(t_global *g, int num);
void				parse_init_tile(t_global *g, int num);
int					parse_tile(char *line, t_global *g);
char				*save_fdf_name(char *line);
int					parse_complex(t_global *g, char **data, int i);
void				complex_2(t_global *g);
void				complex_1(t_global *g);
int					parse_tri(t_global *g, char **data, int i);
void				tri_1(t_global *g);
void				tri_2(t_global *g);
void				tri_3(t_global *g, char **data, int i);
int					parse_plane(t_global *g, char **data, int i);
void				plane_1(t_global *g);
void				plane_2(t_global *g);
void				plane_3(t_global *g, char **data, int i);
int					parse_cylinder(t_global *g, char **data, int i);
void				cylinder_1(t_global *g);
void				cylinder_2(t_global *g);
void				cylinder_3(t_global *g, char **data, int i);
int					parse_cone(t_global *g, char **data, int i);
void				cone_1(t_global *g);
void				cone_2(t_global *g);
void				cone_3(t_global *g, char **data, int i);
void				ft_strjoin_free(char *s1, char *s2, int type);
int					parse_sphere(t_global *g, char **data, int i);
void				sphere_1(t_global *g);
void				sphere_2(t_global *g);
void				sphere_3(t_global *g, char **data, int i);
char				*ft_strjoin_fake(char *s1, char *s2, char type);
int					parse_objects(t_global *g, char **data, int i,
					int lines);
void				objects_1(t_global *g);
void				objects_2(t_global *g, char **data, int i);
int					ft_linelen(char *buf, int k);
int					parse_file(t_global *g, char **data, int lines);
char				**get_scene(char *buf, int lines);
void				open_2(int lines, char *buf, t_global *g);
int					open_file(char **argv, t_global *g);
int					count_objects(t_global *g, int fd);
int					next_num(char *s);
void				init_vector(t_vector *i, double x, double y,
					double z);
t_vector			cross(t_vector a, t_vector b);
double				det(t_vector a, t_vector b);
t_vector			rotate(t_vector ray, t_vector angle);
double				tothe2(double x, int e);
t_dstpst			*nani(t_dstpst *t);
t_do_spec			cr_spec(t_colbri *ret, t_vector *hitli,
					t_vector reflrayv, t_object obj);
void				hello(t_vector end);
int					arrheight(void **a);
t_vector			*cr_vec(t_vector **pts, int i, int j);
t_hunia				cr_hu(int o, t_colbri *cur, t_3_vecs co);
double				len2(t_vector a);
t_masi				cr_masi(double *soft, int *obss, int *io);
void				*recalc(void *p);
void				recalc_row(int jheight, int j, t_global *g);
void				*move(void *p);
void				move_row(int j, int jheight, t_global *g);
int					free_hits(t_global *g);

#endif