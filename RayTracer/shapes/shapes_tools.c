/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:25:02 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/07 15:50:59 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	expand_mesh(t_mesh *mesh)
{
	t_uint	i;

	i = 0;
	while (i < mesh->tris_count)
	{
		mesh->draw_verts = ft_realloc(mesh->draw_verts, (mesh->draw_count + 1)
				* sizeof(float) * 3, mesh->draw_count * sizeof(float) * 3);
		vec3_to_array(&(t_vec3){mesh->verts[mesh->tris[i * 3] * 3],
			mesh->verts[mesh->tris[i * 3] * 3 + 1], mesh->verts[mesh->tris[i
			* 3] * 3 + 2]}, mesh->draw_verts, mesh->draw_count++);
		i++;
	}
}

void	make_mesh(t_rt *rt, t_shape *shape)
{
	if (shape->type == SPHERE)
		new_sphere(rt, shape);
	else if (shape->type == PLANE)
		new_plane(rt, shape);
	else if (shape->type == CYLINDER)
		new_cylinder(rt, shape);
	else if (shape->type == CONE)
		new_cone(rt, shape);
}

void	mesh_get_normals(t_mesh *mesh)
{
	t_uint	i;
	t_vec3	v1;
	t_vec3	v2;
	t_vec3	normal;

	i = 0;
	while (i < mesh->tris_count)
	{
		v1 = (t_vec3){mesh->verts[mesh->tris[i * 3] * 3],
			mesh->verts[mesh->tris[i * 3] * 3 + 1], mesh->verts[mesh->tris[i
			* 3] * 3 + 2]};
		v2 = (t_vec3){mesh->verts[mesh->tris[i * 3 + 1] * 3],
			mesh->verts[mesh->tris[i * 3 + 1] * 3 + 1], mesh->verts[mesh->tris[i
			* 3 + 1] * 3 + 2]};
		mesh->normals = ft_realloc(mesh->normals, (mesh->normals_count + 1)
				* sizeof(float) * 3, mesh->normals_count * sizeof(float) * 3);
		normal = norm_vec3(cross_product(v1, v2));
		vec3_to_array(&normal, mesh->normals, mesh->normals_count++);
		i++;
	}
}
