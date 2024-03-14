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
