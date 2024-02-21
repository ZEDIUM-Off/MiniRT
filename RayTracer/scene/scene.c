/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:26:29 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/20 21:59:10 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	scene_init(t_rt* rt)
{
	float						points[] = {
		-0.5, 0,-0.5,
		0.5, 0, -0.5,
		0.5, 0, 0.5,
		-0.5, 0, 0.5
	};
	unsigned int				indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	t_gl_uint					elements;
	t_gl_vertex_attrib			attr;

	t_gl_uint square;
	gl_gen_buffers(&rt->glx, 1, &square);
	gl_bind_buffer(&rt->glx, GL_ARRAY_BUFFER, square);
	gl_buffer_data(&rt->glx, GL_ARRAY_BUFFER, sizeof(points), points);

	gl_enable_vertex_attrib_array(&rt->glx, 0);
	attr = (t_gl_vertex_attrib){ .size = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .stride = 0 };
	gl_vertex_attrib_pointer(&rt->glx, 0, attr, 0);
	gl_gen_buffers(&rt->glx, 1, &elements);
	gl_bind_buffer(&rt->glx, GL_ELEMENT_ARRAY_BUFFER, elements);
	gl_buffer_data(&rt->glx, GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices);
	gl_enable_vertex_attrib_array(&rt->glx, 0);
	attr = (t_gl_vertex_attrib){ .size = 3, .type = GL_FLOAT,
		.normalized = GL_FALSE, .stride = 0 };
	gl_vertex_attrib_pointer(&rt->glx, 0, attr, 0);
}
