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

void	init_grid(t_rt* rt)
{
	ft_memcpy(rt->grid.verts, (float[]) {
		-1.0f, -1.0f,
			-1.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, -1.0f,
	}, sizeof(float) * 8);
	ft_memcpy(rt->grid.indices, (t_uint[]) {
		0, 1, 2,
			0, 2, 3,
	}, sizeof(t_uint) * 6);
	rt->grid = (t_grid){ .verts_count = 8, .id_count = 6 };
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
	gl_vertex_attrib_pointer(&rt->glx, 0, (t_gl_vertex_attrib) {
		.size = 2,
			.type = GL_FLOAT, .normalized = GL_FALSE,
			.stride = 2 * sizeof(float)
	}, 0);
	gl_enable_vertex_attrib_array(&rt->glx, 0);
}

t_uint	init_rt(t_rt* rt)
{
	t_uint	status;

	printf("init RT...\n");
	status = init_window(rt);
	if (status != CONTINUE)
		return (status);
	printf("window inited\n");
	status = setup_gl_context(rt);
	if (status != CONTINUE)
		return (status);
	printf("gl inited\n");
	init_cam(rt);
	printf("cam inited\n");
	set_hooks(rt);
	printf("hooks inited\n");
	// scene_init(rt);
	init_grid(rt);
	printf("grid inited\n");
	init_shader(rt);
	printf("shaders inited\n");
	rt->ctrl.rotate = false;
	rt->ctrl.translate = false;
	return (CONTINUE);
}
