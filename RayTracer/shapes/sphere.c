/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:48:13 by  mchenava         #+#    #+#             */
/*   Updated: 2024/02/21 17:56:41 by  mchenava        ###   ########.fr       */
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
	vars->point = (t_vec3){ 0, 0, params->radius };
}

static void	push_verts(t_mesh* mesh, t_shpere_vars* vars, t_sphere_params* params)
{
	t_uint	i;
	t_uint	j;
	mesh->verts = ft_realloc(mesh->verts, (mesh->vert_count + 1) * sizeof(float) * 3, mesh->vert_count * sizeof(float) * 3);
	vec3_to_array(&vars->point, mesh->verts, mesh->vert_count++);
	i = 1;
	while (i < params->stacks)
	{
		j = 1;
		vars->point = mult_mat3_vec3(vars->rotaround, vars->point);
		mesh->verts = ft_realloc(mesh->verts, (mesh->vert_count + 1) * sizeof(float) * 3, mesh->vert_count * sizeof(float) * 3);
		vec3_to_array(&vars->point, mesh->verts, mesh->vert_count++);
		vars->tmp = vars->point;
		while (j < params->slices)
		{
			vars->point = rotate_vec3(vars->point, vars->rotaround);
			mesh->verts = ft_realloc(mesh->verts, (mesh->vert_count + 1) * sizeof(float) * 3, mesh->vert_count * sizeof(float) * 3);
			vec3_to_array(&vars->point, mesh->verts, mesh->vert_count++);
			j++;
		}
		vars->point = vars->tmp;
		i++;
	}
	mesh->verts = ft_realloc(mesh->verts, (mesh->vert_count + 1) * sizeof(float) * 3, mesh->vert_count * sizeof(float) * 3);
	vec3_to_array(&(t_vec3) { 0, 0, -params->radius }, mesh->verts, mesh->vert_count++);
}

void	make_sphere(t_mesh* mesh, t_sphere_params* params)
{
	t_shpere_vars	vars;
	init_sphere_vars(mesh, &vars, params);
	push_verts(mesh, &vars, params);
	push_top_tris(mesh, &vars, params);
}
