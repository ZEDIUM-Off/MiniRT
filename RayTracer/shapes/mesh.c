/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:00:51 by  mchenava         #+#    #+#             */
/*   Updated: 2024/02/21 15:47:10 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_mesh(t_mesh* mesh, t_uint type)
{
	mesh->type = type;
	mesh->verts = malloc(sizeof(float) * 3);
	mesh->verts_count = 0;
	mesh->tris = malloc(sizeof(int) * 3);
	mesh->tris_count = 0;
	mesh->tex = malloc(sizeof(float) * 2);
	mesh->tex_count = 0;
	mesh->draw_verts = malloc(sizeof(float) * 3);
	mesh->draw_count = 0;
}

void	mesh_to_scene(t_rt* rt, t_mesh* mesh)
{
	t_gl_vertex_attrib	vert_attr;

	gl_gen_buffers(&rt->glx, 1, &mesh->buffer);
	gl_bind_buffer(&rt->glx, GL_ARRAY_BUFFER, mesh->buffer);
	gl_buffer_data(&rt->glx, GL_ARRAY_BUFFER, mesh->verts_count * sizeof(float) * 3, mesh->verts);
	gl_gen_buffers(&rt->glx, 1, &mesh->tri_buffer);
	gl_bind_buffer(&rt->glx, GL_ELEMENT_ARRAY_BUFFER, mesh->tri_buffer);
	gl_buffer_data(&rt->glx, GL_ELEMENT_ARRAY_BUFFER, mesh->tris_count * sizeof(int) * 3, mesh->tris);
	gl_enable_vertex_attrib_array(&rt->glx, 0);
	vert_attr = (t_gl_vertex_attrib){ .size = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .stride = 0 };;
	gl_vertex_attrib_pointer(&rt->glx, 0, vert_attr, 0);
	gl_bind_vertex_array(&rt->glx, 0);
	rt->scene.meshes = ft_realloc(rt->scene.meshes, (rt->scene.mesh_count + 1) * sizeof(t_mesh), rt->scene.mesh_count * sizeof(t_mesh));
	rt->scene.meshes[rt->scene.mesh_count++] = (*mesh);
}

void	mesh_draw(t_rt* rt, t_mesh* mesh)
{
	t_draw_elements_settings	sett;

	gl_bind_buffer(&rt->glx, GL_ELEMENT_ARRAY_BUFFER, mesh->tri_buffer);
	sett = (t_draw_elements_settings){ mesh->tris_count * 3, GL_UNSIGNED_INT, 0 };
	gl_draw_elements(&rt->glx, GL_TRIANGLES, &sett);
}
