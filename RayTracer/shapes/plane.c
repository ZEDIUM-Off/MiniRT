/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zorin <zorin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:31:04 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/08 04:09:29 by zorin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	push_verts(t_mesh *mesh, t_plane_params *params)
{
	size_t	i;
	size_t	j;
	t_vec3	vert_pos;

	i = 0;
	while (i <= params->dim_v2)
	{
		j = 0;
		while (j <= params->dim_v1)
		{
			vert_pos = add_vec3s(params->corner,
					add_vec3s(scale_vec3s(params->v2, (float)i),
						scale_vec3s(params->v1, (float)j)));
			mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + 1)
					* sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
			vec3_to_array(&vert_pos, mesh->verts, mesh->verts_count++);
			j++;
		}
		i++;
	}
}

// static void	push_tex(t_mesh *mesh, t_plane_params *params, int i, int j)
// {
// 	mesh->tex = ft_realloc(mesh->tex, (mesh->tex_count + 6) * sizeof(float) * 2,
// 			mesh->tex_count * sizeof(float) * 2);
// 	if (!params->tile)
// 	{
// 		vec2_to_array(&(t_vec2){(float)(i % params->dim_v1) / params->dim_v1,
// 			(float)j / params->dim_v2}, mesh->tex, mesh->tex_count++);
// 		vec2_to_array(&(t_vec2){(float)(i % params->dim_v1) / params->dim_v1,
// 			(float)(j + 1) / params->dim_v2}, mesh->tex, mesh->tex_count++);
// 		vec2_to_array(&(t_vec2){
// 			(float)(i % params->dim_v1 + 1) / params->dim_v1,
// 			(float)(j + 1) / params->dim_v2}, mesh->tex, mesh->tex_count++);
// 		vec2_to_array(&(t_vec2){(float)(i % params->dim_v1) / params->dim_v1,
// 			(float)j / params->dim_v2}, mesh->tex, mesh->tex_count++);
// 		vec2_to_array(&(t_vec2){
// 			(float)(i % params->dim_v1 + 1) / params->dim_v1,
// 			(float)(j + 1) / params->dim_v2}, mesh->tex, mesh->tex_count++);
// 		vec2_to_array(&(t_vec2){
// 			(float)(i % params->dim_v1 + 1) / params->dim_v1,
// 			(float)j / params->dim_v2}, mesh->tex, mesh->tex_count++);
// 	}
// 	else
// 	{
// 		vec2_to_array(&(t_vec2){(float)(i % params->dim_v1), j},
// 			mesh->tex, mesh->tex_count++);
// 		vec2_to_array(&(t_vec2){(float)(i % params->dim_v1), (j + 1)},
// 			mesh->tex, mesh->tex_count++);
// 		vec2_to_array(&(t_vec2){(float)(i % params->dim_v1 + 1), (j + 1)},
// 			mesh->tex, mesh->tex_count++);
// 		vec2_to_array(&(t_vec2){(float)(i % params->dim_v1), j}, mesh->tex,
// 			mesh->tex_count++);
// 		vec2_to_array(&(t_vec2){(float)(i % params->dim_v1 + 1), (j + 1)},
// 			mesh->tex, mesh->tex_count++);
// 		vec2_to_array(&(t_vec2){(float)(i % params->dim_v1 + 1), j},
// 			mesh->tex, mesh->tex_count++);
// 	}
// }

static void	push_tris(t_mesh *mesh, t_plane_params *params, int vert_start,
		t_uint tri_start)
{
	size_t	i;
	int		j;

	i = 0;
	j = -1;
	while (i < params->dim_v1 * params->dim_v2)
	{
		if (i % params->dim_v1 == 0)
			j++;
		mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 2) * sizeof(int)
				* 3, mesh->tris_count * sizeof(int) * 3);
		ivec3_to_array(&(t_ivec3){i + j, i + j + params->dim_v1 + 1, i + j
			+ params->dim_v1 + 2}, mesh->tris, mesh->tris_count++);
		ivec3_to_array(&(t_ivec3){i + j, i + j + params->dim_v1 + 2, i + j + 1},
			mesh->tris, mesh->tris_count++);
		i++;
	}
	while (tri_start < mesh->tris_count)
	{
		ivec3_to_array(&(t_ivec3){mesh->tris[tri_start * 3] + vert_start,
			mesh->tris[tri_start * 3 + 1] + vert_start, mesh->tris[tri_start * 3
			+ 2] + vert_start}, mesh->tris, tri_start);
		tri_start++;
	}
}

void	make_plane(t_mesh *mesh, t_plane_params *params)
{
	int	vert_start;
	int	tri_start;

	vert_start = mesh->verts_count;
	tri_start = mesh->tris_count;
	push_verts(mesh, params);
	push_tris(mesh, params, vert_start, tri_start);
}
