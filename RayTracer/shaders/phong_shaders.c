/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_shaders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:22:37 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/07 15:47:44 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	phong_vs(float *vs_output, void *vertex_attribs,
		t_shader_builtins *builtins, void *uniforms)
{
	(void)vs_output;
	(void)vertex_attribs;
	(void)builtins;
	(void)uniforms;
	// t_uniforms	*u;
	// t_vec4		final_pos;
	// t_vec4		*a_pos;
	// t_vec3		transformed_normal;
	// t_vec3 *a_normal; // Added for normal
	// u = (t_uniforms *)uniforms;
	// a_pos = (t_vec4 *)vertex_attribs;
	// // Position is the first attribute
	// a_normal = (t_vec3 *)(vertex_attribs + 4);
	// // Assuming normal follows directly after position
	// mult_mat4_mat4(u->mvp_mat, u->proj, u->view);
	// final_pos = mult_mat4_vec4(u->mvp_mat, *a_pos);
	// builtins->gl_position = final_pos;
	// // Transforming the normal
	// transformed_normal = mult_mat3_vec3(u->normal_mat, *a_normal);
	// // Use a 3x3 matrix for normals
	//
		// You need to decide how to pass this transformed normal to the fragment shader.
	// // This could be via vs_output if you set it up to pass additional data.
}

void	phong_grayscale_fs(float *fs_input, t_shader_builtins *builtins,
		void *uniforms)
{
	t_vec4	color;

	(void)fs_input;
	(void)uniforms;
	color = (t_vec4){0.5, 0.5, 0.5, 1};
	builtins->gl_frag_color = color;
}
