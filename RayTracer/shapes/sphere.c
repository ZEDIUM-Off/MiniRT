/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:48:13 by  mchenava         #+#    #+#             */
/*   Updated: 2024/02/22 16:23:51 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	init_sphere_vars(t_mesh* mesh, t_shpere_vars* vars, t_sphere_params* params)
{
	vars->down = M_PI / (float)params->stacks;
	vars->around = 2 * M_PI / (float)params->slices;
	load_rotation_mat3(vars->rotdown, (t_vec3) { 0, 1, 0 }, vars->down);
	load_rotation_mat3(vars->rotaround, (t_vec3) { 0, 0, 1 }, vars->around);
	vars->vert_start = mesh->verts_count;
	vars->tri_start = mesh->tris_count;
	vars->point = (t_vec3){ params->center.x, params->center.y + params->radius, params->center.z }; // Utilisation du centre
}

static void	push_verts(t_mesh* mesh, t_shpere_vars* vars, t_sphere_params* params)
{
	t_uint	i;
	t_uint	j;
	mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + 1) * sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
	vec3_to_array(&vars->point, mesh->verts, mesh->verts_count++);
	i = 1;
	while (i < params->stacks)
	{
		j = 1;
		vars->point = mult_mat3_vec3(vars->rotdown, vars->point);
		mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + 1) * sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
		vec3_to_array(&vars->point, mesh->verts, mesh->verts_count++);
		vars->tmp = vars->point;
		while (j < params->slices)
		{
			vars->point = mult_mat3_vec3(vars->rotaround, vars->point);
			mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + 1) * sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
			vec3_to_array(&vars->point, mesh->verts, mesh->verts_count++);
			j++;
		}
		vars->point = vars->tmp;
		i++;
	}
	mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + 1) * sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
	vec3_to_array(&(t_vec3) { params->center.x, params->center.y - params->radius, params->center.z }, mesh->verts, mesh->verts_count++);
}

void	make_sphere(t_mesh* mesh, t_sphere_params* params)
{
	t_shpere_vars	vars;
	init_sphere_vars(mesh, &vars, params);
	push_verts(mesh, &vars, params);
	push_top_tris_part1(mesh, &vars, params);
	push_top_tris_part2(mesh, &vars, params);
	add_bottom_cap(mesh, &vars, params);
}

