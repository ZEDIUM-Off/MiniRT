/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:31:04 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/19 13:54:29 by mchenava         ###   ########.fr       */
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
	float	step;
	t_vec3	point;
	int		divisions;
	int		x;
	int		y;

	divisions = PLANE_DIV;
	step = PLANE_SIZE / (float)divisions;
	x = 0;
	while (x <= divisions)
	{
		y = 0;
		while (y <= divisions)
		{
			point = add_vec3s(params->center, add_vec3s(scale_vec3s(vars->right,
							(x - divisions / 2.0) * step), scale_vec3s(vars->up,
							(y - divisions / 2.0) * step)));
			mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + 1)
					* sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
			vec3_to_array(&point, mesh->verts, mesh->verts_count++);
			y++;
		}
		x++;
	}
}

static void	push_tris(t_mesh *mesh, t_plane_vars *vars)
{
	int	divisions;
	int	bott_l;
	int	bott_r;
	int	top_l;
	int	top_r;

	divisions = PLANE_DIV;
	for (int x = 0; x < divisions; x++)
	{
		for (int y = 0; y < divisions; y++)
		{
			bott_l = x * (divisions + 1) + y + vars->verts_start;
			bott_r = bott_l + 1;
			top_l = bott_l + (divisions + 1);
			top_r = top_l + 1;
			mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 2)
					* sizeof(int) * 3, mesh->tris_count * sizeof(int) * 3);
			ivec3_to_array(&(t_ivec3){bott_l, top_l, bott_r}, mesh->tris,
				mesh->tris_count++);
			ivec3_to_array(&(t_ivec3){bott_r, top_l, top_r}, mesh->tris,
				mesh->tris_count++);
		}
	}
}

static void	push_color(t_mesh *mesh, t_plane_vars *vars, t_plane_params *params)
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

void	make_plane(t_mesh *mesh, t_plane_params *params)
{
	t_plane_vars	vars;

	init_vars(mesh, params, &vars);
	push_verts(mesh, params, &vars);
	push_tris(mesh, &vars);
	push_color(mesh, &vars, params);
}
