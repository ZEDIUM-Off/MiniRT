/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:30:54 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/14 16:09:21 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	base_vs(float *vs_output, void *vertex_attribs,
		t_shader_builtins *builtins, void *uniforms)
{
	t_uniforms	*u;
	t_vec4		*v_attribs;
	t_vec3		*vs_out;
	// t_vec4		normal;

	u = (t_uniforms *)uniforms;
	v_attribs = (t_vec4 *)vertex_attribs;
	vs_out = (t_vec3 *)vs_output;
	// printf("v_attribs pos: %f %f %f\n", v_attribs[0].x, v_attribs[0].y, v_attribs[0].z);
	// printf("v_attribs normal: %f %f %f\n", v_attribs[1].x, v_attribs[1].y, v_attribs[1].z);
	mult_mat4_mat4(u->mvp_mat, u->proj, u->view);
	// normal = mult_mat4_vec4(u->mvp_mat, *(t_vec4 *)&v_attribs[1]);
	// vs_out[0] = (t_vec3){normal.x, normal.y, normal.z};
	vs_out[0] = (t_vec3){v_attribs[2].x, v_attribs[2].y, v_attribs[2].z};
	printf("vs_out color: %f %f %f\n", vs_out[0].x, vs_out[0].y,vs_out[0].z);
	builtins->gl_position = mult_mat4_vec4(u->mvp_mat, v_attribs[0]);
}

void	base_fs(float *fs_input, t_shader_builtins *builtins, void *uniforms)
{
	t_vec4	color;
	t_vec3	in_color;
	// t_vec3	normal;

	(void)uniforms;
	// normal = ((t_vec3*)fs_input)[0];
	in_color = ((t_vec3*)fs_input)[0];
	// printf("normal: %f %f %f\n", normal.x, normal.y, normal.z);
	printf("in_color: %f %f %f\n", in_color.x, in_color.y, in_color.z);
	color = (t_vec4){in_color.x, in_color.y, in_color.z, 1};
	builtins->gl_frag_color = color;
}
