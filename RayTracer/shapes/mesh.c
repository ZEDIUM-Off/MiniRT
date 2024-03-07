/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:00:51 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/07 20:12:12 by mchenava         ###   ########.fr       */
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
	mesh->draw_verts = malloc(sizeof(float) * 3);
	mesh->draw_count = 0;
	mesh->normals = malloc(sizeof(t_vec3));
	mesh->normals_count = 0;
}

void	mesh_to_scene(t_rt *rt, t_mesh *mesh)
{
	t_gl_vertex_attrib	vert_attr;

	gl_gen_buffers(&rt->glx, 1, &mesh->buffer);
	gl_bind_buffer(&rt->glx, GL_ARRAY_BUFFER, mesh->buffer);
	gl_buffer_data(&rt->glx, GL_ARRAY_BUFFER, mesh->verts_count * sizeof(float)
		* 3, mesh->verts);
	gl_gen_buffers(&rt->glx, 1, &mesh->tri_buffer);
	gl_bind_buffer(&rt->glx, GL_ELEMENT_ARRAY_BUFFER, mesh->tri_buffer);
	gl_buffer_data(&rt->glx, GL_ELEMENT_ARRAY_BUFFER, mesh->tris_count
		* sizeof(int) * 3, mesh->tris);
	gl_enable_vertex_attrib_array(&rt->glx, 0);
	vert_attr = (t_gl_vertex_attrib){.size = 3, .type = GL_FLOAT,
		.normalized = GL_FALSE, .stride = 0};
	gl_vertex_attrib_pointer(&rt->glx, 0, vert_attr, 0);
	gl_bind_vertex_array(&rt->glx, 0);
}

void	mesh_draw(t_rt *rt, t_mesh *mesh)
{
	t_draw_elements_settings	sett;

	printf("mesh_draw\n");
	printf("mesh vao: %d\n", mesh->buffer);
	printf("mesh vio: %d\n", mesh->tri_buffer);
	gl_bind_vertex_array(&rt->glx, mesh->buffer);
	gl_bind_buffer(&rt->glx, GL_ELEMENT_ARRAY_BUFFER, mesh->tri_buffer);
	sett = (t_draw_elements_settings){mesh->tris_count * 3, GL_UNSIGNED_INT, 0};
	gl_draw_elements(&rt->glx, GL_TRIANGLES, &sett);
	printf("draw_elements_done\n");
	gl_bind_vertex_array(&rt->glx, 0);
}

void	all_mesh_to_scene(t_rt *rt)
{
	t_uint	i;
	t_uint	j;
	t_mesh	curr_mesh;

	i = 0;
	create_mesh(&rt->all_meshes, MESH_MAX);
	while (i < rt->sc_input.shapes_count)
	{
		make_mesh(rt, &rt->sc_input.shapes[i]);
		curr_mesh = rt->sc_input.shapes[i].shape_mesh;
		rt->all_meshes.verts = realloc(rt->all_meshes.verts,
				(rt->all_meshes.verts_count + curr_mesh.verts_count)
				* sizeof(float) * 3/*, rt->all_meshes.verts_count
					* sizeof(float)
				* 3*/);
		memcpy(&rt->all_meshes.verts[rt->all_meshes.verts_count],
			curr_mesh.verts, curr_mesh.verts_count * sizeof(float) * 3);
		j = 0;
		rt->all_meshes.tris = realloc(rt->all_meshes.tris,
				(rt->all_meshes.tris_count + curr_mesh.tris_count) * sizeof(int)
				* 3 /*, rt->all_meshes.tris_count * sizeof(int) * 3*/);
		while (j < curr_mesh.tris_count * 3)
		{
			rt->all_meshes.tris[rt->all_meshes.tris_count * 3
				+ j] = curr_mesh.tris[j] + rt->all_meshes.verts_count * 3;
			j++;
		}
		rt->all_meshes.verts_count += curr_mesh.verts_count;
		printf("all_meshes verts_count: %d\n", rt->all_meshes.verts_count);
		// mesh_get_normals(&curr_mesh);
		i++;
		printf("all mesh Tableau verts:\n");
		for (t_uint k = 0; k < curr_mesh.tris_count * 3; k += 3)
		{
			printf("c_tri %d: (%d, %d, %d) ", k / 3, curr_mesh.tris[k],
				curr_mesh.tris[k + 1], curr_mesh.tris[k + 2]);
			printf("(%d, %d, %d) %d:a_tri \n", rt->all_meshes.tris[k
				+ rt->all_meshes.tris_count], rt->all_meshes.tris[k + 1
				+ rt->all_meshes.tris_count], rt->all_meshes.tris[k + 2
				+ rt->all_meshes.tris_count], k + rt->all_meshes.tris_count
				/ 3);
		}
		rt->all_meshes.tris_count += curr_mesh.tris_count;
		printf("============================\n");
	}
	mesh_to_scene(rt, &rt->all_meshes);
}

void	draw_all_meshes(t_rt *rt)
{
	// t_uint	i;
	// i = 0;
	// printf("draw_all_meshes\n");
	// printf("rt->sc_input.shapes_count: %ld\n", rt->sc_input.shapes_count);
	// while (i < rt->sc_input.shapes_count)
	// {
	// 	printf("try to draw shape %d\n", rt->sc_input.shapes[i].type);
	// 	mesh_draw(rt, &rt->sc_input.shapes[i].shape_mesh);
	// 	sleep(1);
	// 	i++;
	// }
	mesh_draw(rt, &rt->all_meshes);
}
