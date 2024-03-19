/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:48:13 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/19 13:51:55 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	init_vars(t_mesh *mesh, t_shpere_vars *vars,
		t_sphere_params *params)
{
	vars->stack_step = M_PI / params->stacks;
	vars->slice_step = 2 * M_PI / params->slices;
	vars->verts_start = mesh->verts_count;
}

static void	push_verts(t_mesh *mesh, t_shpere_vars *vars,
		t_sphere_params *params)
{
	t_uint	i;
	t_uint	j;
	t_vec3	vert_pos;
	float	x;
	float	y;

	i = 0;
	while (i <= params->stacks)
	{
		vars->phi = M_PI / 2 - i * vars->stack_step;
		j = 0;
		while (j <= params->slices)
		{
			vars->theta = vars->slice_step * j++;
			x = params->radius * cosf(vars->phi) * cosf(vars->theta);
			y = params->radius * cosf(vars->phi) * sinf(vars->theta);
			vert_pos = (t_vec3){x + params->center.x, y + params->center.y,
				params->radius * sinf(vars->phi) + params->center.z};
			mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + 1)
					* sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
			vec3_to_array(&vert_pos, mesh->verts, mesh->verts_count++);
		}
		i++;
	}
}

static void	add_tri(t_mesh *mesh, t_sphere_params *params, size_t i,
		t_shpere_vars *vars)
{
	if (i != 0)
	{
		mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 1) * sizeof(int)
				* 3, mesh->tris_count * sizeof(int) * 3);
		ivec3_to_array(&(t_ivec3){vars->k1 + vars->verts_start, vars->k2
			+ vars->verts_start, vars->k1 + vars->verts_start + 1}, mesh->tris,
			mesh->tris_count++);
	}
	if (i != (params->stacks - 1))
	{
		mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 1) * sizeof(int)
				* 3, mesh->tris_count * sizeof(int) * 3);
		ivec3_to_array(&(t_ivec3){vars->k1 + vars->verts_start + 1, vars->k2
			+ vars->verts_start, vars->k2 + 1 + vars->verts_start}, mesh->tris,
			mesh->tris_count++);
	}
}

static void	push_tris(t_mesh *mesh, t_shpere_vars *vars,
		t_sphere_params *params)
{
	t_uint	i;
	t_uint	j;

	i = 0;
	while (i < params->stacks)
	{
		vars->k1 = i * (params->slices + 1);
		vars->k2 = vars->k1 + params->slices + 1;
		j = 0;
		while (j < params->slices)
		{
			add_tri(mesh, params, i, vars);
			j++;
			vars->k1++;
			vars->k2++;
		}
		i++;
	}
}

void	make_sphere(t_mesh *mesh, t_sphere_params *params)
{
	t_shpere_vars	vars;
	t_uint			i;

	init_vars(mesh, &vars, params);
	push_verts(mesh, &vars, params);
	push_tris(mesh, &vars, params);
	i = 0;
	while (i < mesh->verts_count - vars.verts_start)
	{
		mesh->colors = ft_realloc(mesh->colors, (mesh->colors_count + 1)
				* sizeof(float) * 3, mesh->colors_count * sizeof(float) * 3);
		vec3_to_array(&params->color, mesh->colors, mesh->colors_count++);
		i++;
	}
}
