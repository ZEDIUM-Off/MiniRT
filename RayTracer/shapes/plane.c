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

static void	init_vars(t_mesh *mesh, t_plane_params *params, t_plane_vars *vars)
{
	vars->verts_start = mesh->verts_count;
	vars->right = cross_product(params->normal, (t_vec3){0.0f, 1.0f, 0.0f});
	if (vec3_lenght(vars->right) == 0)
		vars->right = cross_product(params->normal, (t_vec3){0.0f, 0.0f, 1.0f});
	vars->right = norm_vec3(vars->right);
	vars->up = cross_product(params->normal, vars->right);
	vars->up = norm_vec3(vars->up);
	vars->halph = PLANE_SIZE / 2.0f;
}
static void	push_verts(t_mesh *mesh, t_plane_params *params, t_plane_vars *vars)
{
	t_vec3	vertices[4];
	int		i;

	vertices[0] = sub_vec3s(sub_vec3s(params->center, scale_vec3s(vars->right,
					vars->halph)), scale_vec3s(vars->up, vars->halph));
	vertices[1] = add_vec3s(sub_vec3s(params->center, scale_vec3s(vars->right,
					vars->halph)), scale_vec3s(vars->up, vars->halph));
	vertices[2] = add_vec3s(add_vec3s(params->center, scale_vec3s(vars->right,
					vars->halph)), scale_vec3s(vars->up, vars->halph));
	vertices[3] = sub_vec3s(add_vec3s(params->center, scale_vec3s(vars->right,
					vars->halph)), scale_vec3s(vars->up, vars->halph));
	// Ajouter les sommets au maillage
	mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + 4)
			* sizeof(float) * 3, (mesh->verts_count) * sizeof(float) * 3);
	i = 0;
	while (i < 4)
		vec3_to_array(&vertices[i++], mesh->verts, mesh->verts_count++);
}

static void	push_tris(t_mesh *mesh, t_plane_vars *vars)
{
	mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 2) * sizeof(float)
			* 3, (mesh->tris_count) * sizeof(float) * 3);
	ivec3_to_array(&(t_ivec3){0 + vars->verts_start, 2 + vars->verts_start, 1
		+ vars->verts_start}, mesh->tris, mesh->tris_count++);
	ivec3_to_array(&(t_ivec3){0 + vars->verts_start, 3 + vars->verts_start, 2
		+ vars->verts_start}, mesh->tris, mesh->tris_count++);
}

void	make_plane(t_mesh *mesh, t_plane_params *params)
{
	t_plane_vars	vars;

	init_vars(mesh, params, &vars);
	push_verts(mesh, params, &vars);
	push_tris(mesh, &vars);
}
