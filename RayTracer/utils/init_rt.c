/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:27:28 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/13 11:14:07 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	init_grid(t_rt	*rt)
{
	rt->grid.verts = (float [8]){
		-1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, -1.0f,
	};
	rt->grid.indices = (t_uint [6]){
		0, 1, 2,
		0, 2, 3,
	};
	rt->grid = {.verts_count = 8, .id_count = 6};
	gl_gen_vertex_arrays(&rt->glx, 1, &rt->grid.vao);
	gl_gen_buffers(&rt->glx, 1, &rt->grid.vbo);
	gl_gen_buffers(&rt->glx, 1, &rt->grid.ebo);
	gl_bind_vertex_array(&rt->glx, rt->grid.vao);
	gl_bind_buffer(&rt->glx, GL_ARRAY_BUFFER, rt->grid.vbo);
	gl_buffer_data(&rt->glx, GL_ARRAY_BUFFER,
		sizeof(rt->grid.verts), rt->grid.verts);
	gl_bind_buffer(&rt->glx, GL_ELEMENT_ARRAY_BUFFER, rt->grid.ebo);
	gl_buffer_data(&rt->glx, GL_ELEMENT_ARRAY_BUFFER,
		sizeof(rt->grid.indices), rt->grid.indices);
	gl_vertex_attrib_pointer(&rt->glx, 0, (t_gl_vertex_attrib){.size = 2,
		.type = GL_FLOAT, .normalized = GL_FALSE,
		.stride = 2 * sizeof(float)}, 0);
	gl_enable_vertex_attrib_array(&rt->glx, 0);
}

t_uint	init_rt(t_rt *rt)
{
	t_uint	status;

	status = init_window(rt);
	if (status != CONTINUE)
		return (status);
	status = setup_gl_context(rt);
	if (status != CONTINUE)
		return (status);
	init_cam(rt);
	set_hooks(rt);
	scene_init(rt);
	init_shader(rt);
	init_grid(rt);
	rt->ctrl.rotate = false;
	rt->ctrl.translate = false;
	return (CONTINUE);
}
