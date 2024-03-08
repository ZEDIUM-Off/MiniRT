/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:30:54 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/04 14:15:18 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	base_vs(float *vs_output, void *vertex_attribs,
		t_shader_builtins *builtins, void *uniforms)
{
	t_uniforms	*u;
	t_vec4		final_pos;
	t_vec4		*a_pos;

	(void)vs_output;
	u = (t_uniforms *)uniforms;
	a_pos = (t_vec4 *)vertex_attribs;
	mult_mat4_mat4(u->mvp_mat, u->proj, u->view);
	final_pos = mult_mat4_vec4(u->mvp_mat, a_pos[0]);
	builtins->gl_position = final_pos;
}

void	base_fs(float *fs_input, t_shader_builtins *builtins, void *uniforms)
{
	t_vec4	color;

	(void)fs_input;
	(void)uniforms;
	color = (t_vec4){0, 1, 0, 1};
	builtins->gl_frag_color = color;
}
