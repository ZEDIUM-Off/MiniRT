/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:17:17 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/20 11:22:08 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

t_uint	init_rt(t_rt *rt);
t_uint	setup_gl_context(t_rt *rt);
t_uint	clean_rt(t_rt *rt);
t_uint	init_window(t_rt *rt);

int		quit_rt(void *rt);
int		key_pressed(int key, t_rt *rt);
int		mouse_move(int x, int y, t_rt *rt);
int		mouse_released(int btn, int x, int y, t_rt *rt);
int		mouse_pressed(int btn, int x, int y, t_rt *rt);
int		render(t_rt *rt);

void	set_hooks(t_rt	*rt);
void	init_cam(t_rt	*rt);
void	cam_rotate(t_rt *rt, float delta_x, float delta_y);
void	cam_translate(t_rt *rt, int x_offset, int y_offset);
void	cam_proj(t_rt *rt, t_uniforms *u);
void	scene_init(t_rt *rt);
void	grid_vs(float *vs_output, void *vertex_attribs,
			t_shader_builtins *builtins, void *uniforms);
void	grid_fs(float *fs_input,
			t_shader_builtins *builtins, void *uniforms);
void	init_shader(t_rt *rt);

#endif //FUNC_H
