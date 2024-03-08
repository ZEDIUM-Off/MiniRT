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

t_vec3	calculate_triangle_normal(t_vec3 p1, t_vec3 p2, t_vec3 p3)
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	normal;
	float	length;

	u = (t_vec3){p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
	v = (t_vec3){p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};
	normal = (t_vec3){u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y
		- u.y * v.x};
	// Normalisation de la normale
	length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z
			* normal.z);
	normal.x /= length;
	normal.y /= length;
	normal.z /= length;
	return (normal);
}

void	mesh_get_normals(t_mesh *mesh)
{
	int		index0;
	int		index1;
	int		index2;
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	p3;
	t_vec3	normal;
	float	nx;
	float	ny;
	float	nz;
	float	length;

	// Allocation de l'espace pour les normales, une pour chaque sommet
	mesh->normals = malloc(sizeof(float) * mesh->verts_count * 3);
	memset(mesh->normals, 0, sizeof(float) * mesh->verts_count * 3);
	// Calcul des normales pour chaque triangle et ajout à chaque sommet du triangle
	for (t_uint i = 0; i < mesh->tris_count; i++)
	{
		index0 = mesh->tris[i * 3];
		index1 = mesh->tris[i * 3 + 1];
		index2 = mesh->tris[i * 3 + 2];
		p1 = (t_vec3){mesh->verts[index0 * 3], mesh->verts[index0 * 3 + 1],
			mesh->verts[index0 * 3 + 2]};
		p2 = (t_vec3){mesh->verts[index1 * 3], mesh->verts[index1 * 3 + 1],
			mesh->verts[index1 * 3 + 2]};
		p3 = (t_vec3){mesh->verts[index2 * 3], mesh->verts[index2 * 3 + 1],
			mesh->verts[index2 * 3 + 2]};
		normal = calculate_triangle_normal(p1, p2, p3);
		// Ajout de la normale à chaque sommet du triangle
		for (int j = 0; j < 3; j++)
		{
			mesh->normals[index0 * 3 + j] += normal.x;
			mesh->normals[index1 * 3 + j] += normal.y;
			mesh->normals[index2 * 3 + j] += normal.z;
		}
	}
	// Normalisation des normales pour chaque sommet
	for (t_uint i = 0; i < mesh->verts_count; i++)
	{
		nx = mesh->normals[i * 3];
		ny = mesh->normals[i * 3 + 1];
		nz = mesh->normals[i * 3 + 2];
		length = sqrt(nx * nx + ny * ny + nz * nz);
		mesh->normals[i * 3] /= length;
		mesh->normals[i * 3 + 1] /= length;
		mesh->normals[i * 3 + 2] /= length;
	}
	mesh->normals_count = mesh->verts_count;
}
