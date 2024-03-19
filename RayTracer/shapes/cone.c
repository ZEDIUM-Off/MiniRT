/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:15:36 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 18:29:57 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	init_vars(t_mesh *mesh, t_cone_vars *vars, t_cone_params *params)
{
	vars->segments = params->detail;
	vars->radius = tanf(params->angle) * params->height;
	vars->base = add_vec3s(params->center, scale_vec3s(params->axis,
				params->height));
	vars->verts_start = mesh->verts_count;
}

static void	push_verts(t_mesh *mesh, t_cone_params *params, t_cone_vars *vars)
{
	int		i;
	t_vec3	point;

	mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + 2)
			* sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
	vec3_to_array(&vars->base, mesh->verts, mesh->verts_count++);
	vec3_to_array(&params->center, mesh->verts, mesh->verts_count++);
	i = 0;
	while (i < vars->segments)
	{
		vars->theta = 2.0f * M_PI * (float)i++ / (float)vars->segments;
		point = make_vec3(vars->radius * cos(vars->theta), 0, vars->radius
				* sin(vars->theta));
		point = vec3_rotate(point, angle_between_vec3(make_vec3(0, 1, 0),
					params->axis), cross_product(make_vec3(0, 1, 0),
					params->axis));
		point = add_vec3s(vars->base, point);
		mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + 1)
				* sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
		vec3_to_array(&point, mesh->verts, mesh->verts_count++);
	}
}

static void	push_tris(t_mesh *mesh, t_cone_vars *vars)
{
	int	i;
	int	next;

	i = 2;
	while (i <= vars->segments + 1)
	{
		next = i % vars->segments + 1;
		if (next == 1)
			next = vars->segments + 1;
		mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 2) * sizeof(int)
				* 3, mesh->tris_count * sizeof(int) * 3);
		ivec3_to_array(&(t_ivec3){1 + vars->verts_start, next
			+ vars->verts_start, i + vars->verts_start}, mesh->tris,
			mesh->tris_count++);
		ivec3_to_array(&(t_ivec3){0 + vars->verts_start, i + vars->verts_start,
			next + vars->verts_start}, mesh->tris, mesh->tris_count++);
		i++;
	}
}

static void	push_color(t_mesh *mesh, t_cone_vars *vars, t_cone_params *params)
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

void	make_cone(t_mesh *mesh, t_cone_params *params)
{
	t_cone_vars	vars;

	init_vars(mesh, &vars, params);
	push_verts(mesh, params, &vars);
	push_tris(mesh, &vars);
	push_color(mesh, &vars, params);
}
