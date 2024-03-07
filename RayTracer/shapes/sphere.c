/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:48:13 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/07 17:15:33 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	init_sphere_vars(t_shpere_vars *vars, t_sphere_params *params)
{
	vars->stack_step = M_PI / params->stacks;
	vars->slice_step = 2 * M_PI / params->slices;
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
		ivec3_to_array(&(t_ivec3){vars->k1, vars->k2, vars->k1 + 1}, mesh->tris,
			mesh->tris_count++);
	}
	if (i != (params->stacks - 1))
	{
		mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 1) * sizeof(int)
				* 3, mesh->tris_count * sizeof(int) * 3);
		ivec3_to_array(&(t_ivec3){vars->k1 + 1, vars->k2, vars->k2 + 1},
			mesh->tris, mesh->tris_count++);
	}
}

static void	sphere_push_tris(t_mesh *mesh, t_shpere_vars *vars,
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

	init_sphere_vars(&vars, params);
	push_verts(mesh, &vars, params);
	sphere_push_tris(mesh, &vars, params);
	expand_mesh(mesh);
}
