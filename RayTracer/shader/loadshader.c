/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadshader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:34:32 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 11:20:31 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	load_rt_shader(t_rt *rt)
{
	t_gl_program	prog_attr;
	t_gl_uint		shader_id;

	prog_attr = (t_gl_program){.vertex_shader = base_vs,
		.fragment_shader = rt_frag_shader, .vs_output_size = 3,
		.fragdepth_or_discard = GL_FALSE};
	shader_id = lgl_create_program(&rt->glx, prog_attr, (t_gl_enum[3]){SMOOTH,
			SMOOTH, SMOOTH});
	rt->shaders[MODE_RENDER] = shader_id;
}

void	load_viz_shader(t_rt *rt)
{
	t_gl_program	prog_attr;
	t_gl_uint		shader_id;

	prog_attr = (t_gl_program){.vertex_shader = base_vs,
		.fragment_shader = base_fs, .vs_output_size = 3,
		.fragdepth_or_discard = GL_FALSE};
	shader_id = lgl_create_program(&rt->glx, prog_attr, (t_gl_enum[3]){SMOOTH,
			SMOOTH, SMOOTH});
	rt->shaders[MODE_VIZ] = shader_id;
}

void	init_uiniforms(t_rt *rt)
{
	identity_mat4(rt->uniforms.proj);
	identity_mat4(rt->uniforms.view);
	identity_mat4(rt->uniforms.mvp_mat);
	rt->uniforms.rt = rt;
	lgl_set_uniform(&rt->glx, &rt->uniforms);
}

void	init_shader(t_rt *rt)
{
	load_rt_shader(rt);
	load_viz_shader(rt);
	gl_use_program(&rt->glx, rt->shaders[rt->mode]);
	init_uiniforms(rt);
}
