/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadshader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:34:32 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/07 17:46:15 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	init_shader(t_rt *rt)
{
	t_gl_uint		shader;
	t_gl_program	prog_attr;
	t_gl_enum		interp[4] = {SMOOTH, SMOOTH, SMOOTH, SMOOTH};

	prog_attr = (t_gl_program){.vertex_shader = default_vs,
		.fragment_shader = rt_frag_shader, .vs_output_size = 4,
		.fragdepth_or_discard = GL_FALSE};
	shader = lgl_create_program(&rt->glx, prog_attr, interp);
	gl_use_program(&rt->glx, shader);
	lgl_set_uniform(&rt->glx, &rt->uniforms);
	identity_mat4(rt->uniforms.proj);
	identity_mat4(rt->uniforms.view);
	identity_mat4(rt->uniforms.mvp_mat);
	rt->uniforms.grid_scale = 1;
	rt->uniforms.rt = rt;
}
