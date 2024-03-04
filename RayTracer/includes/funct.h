/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:17:17 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/04 02:08:17 by agaley           ###   ########lyon.fr   */
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
int		key_pressed(int key, t_rt *rt);
int		mouse_move(int x, int y, t_rt *rt);
int		mouse_released(int btn, int x, int y, t_rt *rt);
int		mouse_pressed(int btn, int x, int y, t_rt *rt);

// rendering
int		render(t_rt *rt);
void	new_frame(t_rt *rt);

void	set_hooks(t_rt *rt);
void	init_cam(t_rt *rt);
void	cam_rotate(t_rt *rt, float delta_x, float delta_y);
void	cam_translate(t_rt *rt, int x_offset, int y_offset);
void	cam_proj(t_rt *rt, t_uniforms *u);
void	scene_init(t_rt *rt);
void	grid_vs(float *vs_output, void *vertex_attribs,
			t_shader_builtins *builtins, void *uniforms);
void	grid_fs(float *fs_input, t_shader_builtins *builtins, void *uniforms);
void	init_shader(t_rt *rt);

// Shapes
void	make_plane(t_mesh *mesh, t_plane_params *params);
void	make_sphere(t_mesh *mesh, t_sphere_params *params);
void	push_top_tris_part1(t_mesh *mesh, t_shpere_vars *vars,
			t_sphere_params *params);
void	push_top_tris_part2(t_mesh *mesh, t_shpere_vars *vars,
			t_sphere_params *params);
void	add_bottom_cap(t_mesh *mesh, t_shpere_vars *vars,
			t_sphere_params *params);

// Mesh
void	mesh_to_scene(t_rt *rt, t_mesh *mesh);
void	create_mesh(t_mesh *mesh, t_uint type);
void	mesh_draw(t_rt *rt, t_mesh *mesh);
void	expand_mesh(t_mesh *mesh);

#endif // FUNC_H
