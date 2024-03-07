/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:17:17 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/07 17:16:24 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCT_H
# define FUNCT_H

// utils
t_uint	init_rt(t_rt *rt);
t_uint	clean_rt(t_rt *rt);
int		handle_error(char *msg, t_rt *rt);
void	vec3_to_array(t_vec3 *vec, float *arr, t_uint start);
void	ivec3_to_array(t_ivec3 *vec, int *arr, t_uint start);
void	vec2_to_array(t_vec2 *vec, float *arr, t_uint start);

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

// rendering
int		render(t_rt *rt);
void	new_frame(t_rt *rt);

void	set_hooks(t_rt *rt);
void	init_cam(t_rt *rt);
void	cam_rotate(t_rt *rt, float delta_x, float delta_y);
void	cam_translate(t_rt *rt, int x_offset, int y_offset);
void	cam_proj(t_rt *rt, t_viz_uniforms *u);
void	scene_init(t_rt *rt);

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
void	expand_mesh(t_mesh *mesh);
void	all_mesh_to_scene(t_rt *rt);
void	draw_all_meshes(t_rt *rt);
void	make_mesh(t_rt *rt, t_shape *shape);
void	mesh_get_normals(t_mesh *mesh);

#endif // FUNC_H
