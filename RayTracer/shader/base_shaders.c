/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:30:54 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 11:35:52 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	base_vs(float *vs_output, void *vertex_attribs,
		t_shader_builtins *builtins, void *uniforms)
{
	t_uniforms	*u;
	t_vec4		*v_attribs;
	t_vec3		*vs_out;

	u = (t_uniforms *)uniforms;
	v_attribs = (t_vec4 *)vertex_attribs;
	vs_out = (t_vec3 *)vs_output;
	mult_mat4_mat4(u->mvp_mat, u->proj, u->view);
	vs_out[0] = vec4_to_vec3(v_attribs[1]);
	builtins->gl_position = mult_mat4_vec4(u->mvp_mat, v_attribs[0]);
}

void	base_fs(float *fs_input, t_shader_builtins *builtins, void *uniforms)
{
	t_vec4	color;
	t_vec3	in_color;

	(void)uniforms;
	in_color = ((t_vec3 *)fs_input)[0];
	color = (t_vec4){in_color.x, in_color.y, in_color.z, 1};
	builtins->gl_frag_color = color;
}
