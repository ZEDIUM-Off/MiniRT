/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:15:36 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/20 00:17:33 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	init_vars(t_mesh *mesh, t_cone_vars *vars, t_cone_params *params)
{
	vars->segments = params->detail;
	vars->radius = tanf(params->angle) * params->height / 2.0;
	vars->verts_start = mesh->verts_count;
	vars->perp_axis = cross_product(norm_vec3(params->axis), make_vec3(0, 1, 0));
    if (vec3_lenght(vars->perp_axis) < 0.0001)
	{
        vars->perp_axis = cross_product(norm_vec3(params->axis), make_vec3(1, 0, 0));
	}
	vars->perp_axis2 = cross_product(norm_vec3(params->axis), vars->perp_axis);
}

static void	push_verts(t_mesh *mesh, t_cone_params *params, t_cone_vars *vars)
{
    int i;
    t_vec3 point_base, point_top;
    mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + vars->segments * 2 + 1) * sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
    vec3_to_array(&params->center, mesh->verts, mesh->verts_count++);
	i = 0;
   	while(i < vars->segments)
    {
        vars->theta = ((float)i++ / (float)vars->segments) * 2.0 * M_PI;
        point_base = add_vec3s(params->center, add_vec3s(scale_vec3s(vars->perp_axis, cos(vars->theta) * vars->radius), scale_vec3s(vars->perp_axis2, sin(vars->theta) * vars->radius)));
        point_top = add_vec3s(point_base, scale_vec3s(norm_vec3(params->axis), params->height / 2.0));
        point_base = add_vec3s(point_base, scale_vec3s(norm_vec3(params->axis), -params->height / 2.0));
        vec3_to_array(&point_base, mesh->verts, mesh->verts_count++);
        vec3_to_array(&point_top, mesh->verts, mesh->verts_count++);
    }
}

static void	push_tris(t_mesh *mesh, t_cone_vars *vars)
{
    int i;
    int base_index, next_base_index, top_index, next_top_index;
    for (i = 0; i < vars->segments; i++)
    {
        base_index = vars->verts_start + 1 + i * 2;
        top_index = base_index + 1;
        next_base_index = vars->verts_start + 1 + ((i + 1) % vars->segments) * 2;
        next_top_index = next_base_index + 1;
        mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 2) * sizeof(int) * 3, mesh->tris_count * sizeof(int) * 3);
        ivec3_to_array(&(t_ivec3){vars->verts_start, base_index, next_base_index}, mesh->tris, mesh->tris_count++);
        mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 2) * sizeof(int) * 3, mesh->tris_count * sizeof(int) * 3);
        ivec3_to_array(&(t_ivec3){vars->verts_start, next_top_index, top_index}, mesh->tris, mesh->tris_count++);
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
