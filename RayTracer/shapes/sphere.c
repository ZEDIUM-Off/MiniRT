/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:48:13 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/04 14:51:19 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	init_sphere_vars(t_mesh *mesh, t_shpere_vars *vars,
		t_sphere_params *params)
{
	vars->tot_verts = (params->stacks - 1) * params->slices + 2;
	vars->vert_start = mesh->verts_count;
	vars->tri_start = mesh->tris_count;
	vars->pole_top = vars->vert_start;
	vars->pole_bot = vars->vert_start + (params->stacks - 1) * params->slices
		+ 1;
	vars->offset = 0;
}

static void	push_verts(t_mesh *mesh, t_shpere_vars *vars,
		t_sphere_params *params)
{
	t_uint	i;
	t_uint	j;

	mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + vars->tot_verts)
			* sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
	vec3_to_array(&(t_vec3){params->center.x, params->center.y + params->radius,
		params->center.z}, mesh->verts, mesh->verts_count++);
	i = 1;
	while (i < params->stacks)
	{
		vars->phi = M_PI * i++ / params->stacks;
		j = 0;
		while (j < params->slices)
		{
			vars->theta = 2 * M_PI * j++ / params->slices;
			vec3_to_array(&(t_vec3){params->center.x + params->radius
				* sinf(vars->phi) * cosf(vars->theta), params->center.y
				+ params->radius * cosf(vars->phi), params->center.z
				+ params->radius * sinf(vars->phi) * sinf(vars->theta)},
				mesh->verts, mesh->verts_count++);
		}
	}
	vec3_to_array(&(t_vec3){params->center.x, params->center.y - params->radius,
		params->center.z}, mesh->verts, mesh->verts_count++);
}

void	make_sphere(t_mesh *mesh, t_sphere_params *params)
{
	t_shpere_vars	vars;

	init_sphere_vars(mesh, &vars, params);
	push_verts(mesh, &vars, params);
	printf("verts pushed\n");
	sphere_push_tris(mesh, &vars, params);
	printf("tris pushed\n");
	expand_mesh(mesh);
}
