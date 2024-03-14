/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:00:51 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/14 15:43:25 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_mesh(t_mesh *mesh, t_uint type)
{
	mesh->type = type;
	mesh->verts = malloc(sizeof(float) * 3);
	mesh->verts_count = 0;
	mesh->tris = malloc(sizeof(int) * 3);
	mesh->tris_count = 0;
	mesh->normals = malloc(sizeof(t_vec3));
	mesh->normals_count = 0;
}

void	mesh_to_scene(t_rt *rt, t_mesh *mesh)
{
	t_gl_vertex_attrib	vert_attr;

	vert_attr = (t_gl_vertex_attrib){.size = 3, .type = GL_FLOAT,
		.normalized = GL_FALSE, .stride = 0};
	gl_gen_buffers(&rt->glx, 1, &mesh->buffer);
	gl_bind_buffer(&rt->glx, GL_ARRAY_BUFFER, mesh->buffer);
	gl_buffer_data(&rt->glx, GL_ARRAY_BUFFER, mesh->verts_count * sizeof(float) * 3,
		mesh->verts);
	gl_enable_vertex_attrib_array(&rt->glx, 0);
	gl_vertex_attrib_pointer(&rt->glx, 0, vert_attr, 0);
	gl_gen_buffers(&rt->glx, 1, &mesh->tri_buffer);
	gl_bind_buffer(&rt->glx, GL_ELEMENT_ARRAY_BUFFER, mesh->tri_buffer);
	gl_buffer_data(&rt->glx, GL_ELEMENT_ARRAY_BUFFER, mesh->tris_count
		* sizeof(int) * 3, mesh->tris);
	gl_gen_buffers(&rt->glx, 1, &mesh->norm_buffer);
	gl_bind_buffer(&rt->glx, GL_ARRAY_BUFFER, mesh->norm_buffer);
	gl_buffer_data(&rt->glx, GL_ARRAY_BUFFER, mesh->normals_count
		* sizeof(float) * 3, mesh->normals);
	gl_enable_vertex_attrib_array(&rt->glx, 1);
	gl_vertex_attrib_pointer(&rt->glx, 1, vert_attr, 0);
	gl_gen_buffers(&rt->glx, 1, &mesh->color_buffer);
	gl_bind_buffer(&rt->glx, GL_ARRAY_BUFFER, mesh->color_buffer);
	gl_buffer_data(&rt->glx, GL_ARRAY_BUFFER, mesh->colors_count
		* sizeof(float) * 3, mesh->colors);
	gl_enable_vertex_attrib_array(&rt->glx, 2);
	gl_vertex_attrib_pointer(&rt->glx, 2, vert_attr, 0);
	gl_bind_vertex_array(&rt->glx, 0);
}

void	mesh_draw(t_rt *rt, t_mesh *mesh)
{
	t_draw_elements_settings	sett;

	gl_bind_vertex_array(&rt->glx, mesh->buffer);
	gl_bind_buffer(&rt->glx, GL_ELEMENT_ARRAY_BUFFER, mesh->tri_buffer);
	sett = (t_draw_elements_settings){mesh->tris_count * 3, GL_UNSIGNED_INT, 0};
	gl_draw_elements(&rt->glx, GL_TRIANGLES, &sett);
	gl_bind_vertex_array(&rt->glx, 0);
}

void	all_mesh_to_scene(t_rt *rt)
{
	t_uint	i;

	i = 0;
	create_mesh(&rt->all_meshes, MESH_MAX);
	while (i < rt->sc_input.shapes_count)
	{
		make_mesh(rt, &rt->sc_input.shapes[i]);
		i++;
	}
	mesh_get_normals(&rt->all_meshes);
	// mesh_get_colors(&rt->all_meshes);
	mesh_to_scene(rt, &rt->all_meshes);
}
