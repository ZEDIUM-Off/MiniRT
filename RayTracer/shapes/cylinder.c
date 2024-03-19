/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:07:08 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 11:38:32 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	init_vars(t_mesh *mesh, t_cylinder_params *params,
		t_cylinder_vars *vars)
{
	vars->axis_normalized = norm_vec3(params->axis);
	vars->perp_axis = cross_product(vars->axis_normalized, make_vec3(0, 1, 0));
	if (vec3_lenght(vars->perp_axis) < 0.0001)
		vars->perp_axis = cross_product(vars->axis_normalized, make_vec3(1, 0,
					0));
	vars->perp_axis = norm_vec3(vars->perp_axis);
	vars->perp_axis2 = cross_product(vars->axis_normalized, vars->perp_axis);
	vars->perp_axis2 = norm_vec3(vars->perp_axis2);
	vars->radius = params->diameter / 2.0;
	vars->segments = MESH_DETAIL;
	vars->verts_start = mesh->verts_count;
	vars->tris_start = mesh->tris_count;
}

// static void	disks_verts(t_mesh *mesh, t_cylinder_params *params,
// 		t_cylinder_vars *vars)
// {
// 	mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + 2)
// 			* sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
// 	vec3_to_array(&params->center, mesh->verts, mesh->verts_count++);
// 	vars->bottom_center_index = mesh->verts_count - 1;
// 	vars->top_center = add_vec3s(params->center,
// 			scale_vec3s(vars->axis_normalized, params->height));
// 	vec3_to_array(&vars->top_center, mesh->verts, mesh->verts_count++);
// 	vars->top_center_index = mesh->verts_count - 1;
// }

static void	push_verts(t_mesh *mesh, t_cylinder_params *params,
		t_cylinder_vars *vars)
{
	int		i;
	t_vec3	bottom_point;
	t_vec3	top_point;
	t_vec3	center_offset;

	i = 0;
	center_offset = scale_vec3s(vars->axis_normalized, -params->height / 2.0);
	while (i < vars->segments)
	{
		vars->theta = ((float)i / (float)vars->segments) * 2.0 * M_PI;
		bottom_point = add_vec3s(add_vec3s(params->center, center_offset),
				add_vec3s(scale_vec3s(vars->perp_axis, cos(vars->theta)
						* vars->radius), scale_vec3s(vars->perp_axis2,
						sin(vars->theta) * vars->radius)));
		mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + 2)
				* sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
		vec3_to_array(&bottom_point, mesh->verts, mesh->verts_count++);
		top_point = add_vec3s(bottom_point, scale_vec3s(vars->axis_normalized,
					params->height));
		vec3_to_array(&top_point, mesh->verts, mesh->verts_count++);
		i++;
	}
}

// ivec3_to_array(&(t_ivec3){vars->bottom_center_index
// + vars->verts_start,
// 	next_base_idx + vars->verts_start, base_idx + vars->verts_start},
// 	mesh->tris, mesh->tris_count++);
// ivec3_to_array(&(t_ivec3){vars->top_center_index + vars->verts_start,
// 	top_idx + vars->verts_start, next_top_idx + vars->verts_start},
// 	mesh->tris, mesh->tris_count++);
static void	push_tris(t_mesh *mesh, t_cylinder_vars *vars)
{
	int	i;
	int	base_idx;
	int	top_idx;
	int	next_base_idx;
	int	next_top_idx;

	i = 0;
	while (i < vars->segments)
	{
		base_idx = i * 2;
		top_idx = base_idx + 1;
		next_base_idx = ((i + 1) % vars->segments) * 2;
		next_top_idx = next_base_idx + 1;
		mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 2) * sizeof(int)
				* 3, mesh->tris_count * sizeof(int) * 3);
		ivec3_to_array(&(t_ivec3){base_idx + vars->verts_start, next_base_idx
			+ vars->verts_start, top_idx + vars->verts_start}, mesh->tris,
			mesh->tris_count++);
		ivec3_to_array(&(t_ivec3){top_idx + vars->verts_start, next_base_idx
			+ vars->verts_start, next_top_idx + vars->verts_start}, mesh->tris,
			mesh->tris_count++);
		i++;
	}
}

static void	push_color(t_mesh *mesh, t_cylinder_vars *vars,
		t_cylinder_params *params)
{
	t_uint	i;

	i = 0;
	while (i < mesh->verts_count - vars->verts_start)
	{
		mesh->colors = ft_realloc(mesh->colors, (mesh->colors_count + 1)
				* sizeof(float) * 3, mesh->colors_count * sizeof(float) * 3);
		vec3_to_array(&params->color, mesh->colors, mesh->colors_count++);
		i++;
	}
}

void	make_cylinder(t_mesh *mesh, t_cylinder_params *params)
{
	t_cylinder_vars	vars;

	init_vars(mesh, params, &vars);
	push_verts(mesh, params, &vars);
	push_tris(mesh, &vars);
	push_color(mesh, &vars, params);
}
