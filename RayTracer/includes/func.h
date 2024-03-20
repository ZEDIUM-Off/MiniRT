/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:17:17 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/20 12:21:49 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

// utils
t_uint	init_rt(t_rt *rt);
t_uint	clean_rt(t_rt *rt);
int		handle_error(char *msg, t_rt *rt);
void	vec3_to_array(t_vec3 *vec, float *arr, t_uint start);
void	ivec3_to_array(t_ivec3 *vec, int *arr, t_uint start);
void	vec2_to_array(t_vec2 *vec, float *arr, t_uint start);
bool	is_number(char *input);
t_uint	setup_gl_context(t_rt *rt);
t_uint	init_window(t_rt *rt);
int		quit_rt(void *rt);

// input
int		key_pressed(int key, t_rt *rt);
int		mouse_move(int x, int y, t_rt *rt);
int		mouse_released(int btn, int x, int y, t_rt *rt);
int		mouse_pressed(int btn, int x, int y, t_rt *rt);
void	switch_mode(t_rt *rt);
void	print_cam_properties(t_rt *rt);
void	switch_bumpmap_mode(t_rt *rt);
void	switch_checkerboard(t_rt *rt);
void	switch_mandatory(t_rt *rt);
void	switch_soft_shadow(t_rt *rt);

// rendering
int		render(t_rt *rt);
void	new_frame(t_rt *rt);
void	render_raytraced(t_rt *rt, bool up);
void	set_hooks(t_rt *rt);
void	init_cam(t_rt *rt);
void	cam_rotate(t_rt *rt, float delta_x, float delta_y);
void	cam_translate(t_rt *rt, int x_offset, int y_offset);
void	cam_proj(t_rt *rt, t_uniforms *u);
void	scene_init(t_rt *rt);
void	cam_zoom(t_rt *rt, int zoom);

// Shaders
void	grid_vs(float *vs_output, void *vertex_attribs,
			t_shader_builtins *builtins, void *uniforms);
void	grid_fs(float *fs_input, t_shader_builtins *builtins, void *uniforms);
void	init_shader(t_rt *rt);
void	base_vs(float *vs_output, void *vertex_attribs,
			t_shader_builtins *builtins, void *uniforms);
void	base_fs(float *fs_input, t_shader_builtins *builtins, void *uniforms);
void	phong_vs(float *vs_output, void *vertex_attribs,
			t_shader_builtins *builtins, void *uniforms);
void	phong_grayscale_fs(float *fs_input, t_shader_builtins *builtins,
			void *uniforms);
void	rt_frag_shader(float *fs_input, t_shader_builtins *builtins, void *uni);

// Shapes
void	make_plane(t_mesh *mesh, t_plane_params *params);
void	make_sphere(t_mesh *mesh, t_sphere_params *params);
void	make_cylinder(t_mesh *mesh, t_cylinder_params *params);
void	make_cone(t_mesh *mesh, t_cone_params *params);
void	new_sphere(t_rt *rt, t_shape *shape);
void	new_plane(t_rt *rt, t_shape *shape);
void	new_cylinder(t_rt *rt, t_shape *shape);
void	new_cone(t_rt *rt, t_shape *shape);

// Mesh
void	mesh_to_scene(t_rt *rt, t_mesh *mesh);
void	create_mesh(t_mesh *mesh, t_uint type);
void	mesh_draw(t_rt *rt, t_mesh *mesh);
void	all_mesh_to_scene(t_rt *rt);
void	make_mesh(t_rt *rt, t_shape *shape);
void	mesh_get_normals(t_mesh *mesh);

// Scene Editor
void	editor_menu(t_rt *rt);
bool	input_first_menu(t_rt *rt, char *input);
void	obj_menu(t_rt *rt, t_obj *obj);
bool	rotate_obj(t_obj *obj);
bool	translate_obj(t_obj *obj);
bool	modify_obj_props(t_obj *obj);
void	modify_cylinder_props(t_shape *shape);
void	modify_cone_props(t_shape *shape);
void	modify_plane_props(t_shape *shape);
void	modify_sphere_props(t_shape *shape);
void	modify_light_props(t_s_light *light);
t_vec3	get_axis(char *axis_name);
bool	modif_shape_color(t_shape *shape);
bool	is_float(char *input);
bool	is_in_range(char *input, float min, float max);
bool	is_color(char *input);
void	display_sphere_props(size_t i, t_shape *shape);
void	display_plane_props(size_t i, t_shape *shape);
void	display_cylinder_props(size_t i, t_shape *shape);
void	display_cone_props(size_t i, t_shape *shape);
void	display_light_props(size_t i, t_s_light *light);
void	update_scene(t_rt *rt);
bool	modify_mesh_details(t_rt *rt);
bool	input_scene_menu(t_rt *rt, char *input);
float	get_float(char *message);

#endif // FUNC_H
