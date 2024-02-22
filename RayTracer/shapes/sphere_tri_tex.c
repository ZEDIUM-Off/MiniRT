/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_tri_tex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:56:10 by  mchenava         #+#    #+#             */
/*   Updated: 2024/02/22 16:08:36 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	push_top_tris_part1(t_mesh* mesh, t_shpere_vars* vars, t_sphere_params* params)
{
	t_uint	i;

	i = 1;
	(void)vars;
	while (i < params->slices)
	{
		mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 1) * sizeof(int) * 3, mesh->tris_count * sizeof(int) * 3);
		ivec3_to_array(&(t_ivec3) { 0, i, i + 1 }, mesh->tris, mesh->tris_count++);
		mesh->tex = ft_realloc(mesh->tex, (mesh->tex_count + 3) * sizeof(float) * 2, mesh->tex_count * sizeof(float) * 2);
		vec2_to_array(&(t_vec2) { (i - 1) / params->slices, 1 }, mesh->tex, mesh->tex_count++);
		vec2_to_array(&(t_vec2) { (i - 1) / params->slices, (params->stacks - 1) / params->stacks }, mesh->tex, mesh->tex_count++);
		vec2_to_array(&(t_vec2) { i / params->slices, (params->stacks - 1) / params->stacks }, mesh->tex, mesh->tex_count++);
		i++;
	}
	mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 1) * sizeof(int) * 3, mesh->tris_count * sizeof(int) * 3);
	ivec3_to_array(&(t_ivec3) { 0, i, 1 }, mesh->tris, mesh->tris_count++);
	mesh->tex = ft_realloc(mesh->tex, (mesh->tex_count + 3) * sizeof(float) * 2, mesh->tex_count * sizeof(float) * 2);
	vec2_to_array(&(t_vec2) { (i - 1) / params->slices, 1 }, mesh->tex, mesh->tex_count++);
	vec2_to_array(&(t_vec2) { (i - 1) / params->slices, (params->stacks - 1) / params->stacks }, mesh->tex, mesh->tex_count++);
	vec2_to_array(&(t_vec2) { 1, (params->stacks - 1) / params->stacks }, mesh->tex, mesh->tex_count++);
}

static void process_slice_for_stack(t_mesh* mesh, t_shpere_vars* vars, t_sphere_params* params, t_uint i, t_uint j)
{
	int		corner;

	corner = vars->vert_start + i * params->slices + j;
	mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 2) * sizeof(int) * 3, mesh->tris_count * sizeof(int) * 3);
	ivec3_to_array(&(t_ivec3) { corner, corner + 1, corner - params->slices }, mesh->tris, mesh->tris_count++);
	ivec3_to_array(&(t_ivec3) { corner + 1, (corner + 1) - params->slices, corner - params->slices }, mesh->tris, mesh->tris_count++);
	mesh->tex = ft_realloc(mesh->tex, (mesh->tex_count + 6) * sizeof(float) * 2, mesh->tex_count * sizeof(float) * 2);
	vec2_to_array(&(t_vec2) { (float)j / params->slices, (params->stacks - i - 1) / params->stacks }, mesh->tex, mesh->tex_count++);
	vec2_to_array(&(t_vec2) { (float)(j + 1) / params->slices, (params->stacks - i - 1) / params->stacks }, mesh->tex, mesh->tex_count++);
	vec2_to_array(&(t_vec2) { (float)(j) / params->slices, (params->stacks - i) / params->stacks }, mesh->tex, mesh->tex_count++);
	vec2_to_array(&(t_vec2) { (float)(j + 1) / params->slices, (params->stacks - i - 1) / params->stacks }, mesh->tex, mesh->tex_count++);
	vec2_to_array(&(t_vec2) { (float)(j + 1) / params->slices, (params->stacks - i) / params->stacks }, mesh->tex, mesh->tex_count++);
	vec2_to_array(&(t_vec2) { (float)(j) / params->slices, (params->stacks - i) / params->stacks }, mesh->tex, mesh->tex_count++);
}

void	push_top_tris_part2(t_mesh* mesh, t_shpere_vars* vars, t_sphere_params* params)
{
	t_uint	i;
	t_uint	j;
	int		corner;

	i = 1;
	while (i < params->stacks - 1)
	{
		j = 0;
		while (j < params->slices - 1)
			process_slice_for_stack(mesh, vars, params, i, j++);
		corner = vars->vert_start + i * params->slices + j;
		mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 2) * sizeof(int) * 3, mesh->tris_count * sizeof(int) * 3);
		ivec3_to_array(&(t_ivec3) { corner, i* params->slices + 1, corner - params->slices }, mesh->tris, mesh->tris_count++);
		ivec3_to_array(&(t_ivec3) { i* params->slices + 1, (i - 1)* params->slices + 1, corner - params->slices }, mesh->tris, mesh->tris_count++);
		mesh->tex = ft_realloc(mesh->tex, (mesh->tex_count + 6) * sizeof(float) * 2, mesh->tex_count * sizeof(float) * 2);
		vec2_to_array(&(t_vec2) { (float)j / params->slices, (params->stacks - i - 1) / params->stacks }, mesh->tex, mesh->tex_count++);
		vec2_to_array(&(t_vec2) { 1, (params->stacks - i - 1) / params->stacks }, mesh->tex, mesh->tex_count++);
		vec2_to_array(&(t_vec2) { (float)(j) / params->slices, (params->stacks - i) / params->stacks }, mesh->tex, mesh->tex_count++);
		vec2_to_array(&(t_vec2) { 1, (params->stacks - i - 1) / params->stacks }, mesh->tex, mesh->tex_count++);
		vec2_to_array(&(t_vec2) { 1, (params->stacks - i) / params->stacks }, mesh->tex, mesh->tex_count++);
		vec2_to_array(&(t_vec2) { (float)(j) / params->slices, (params->stacks - i) / params->stacks }, mesh->tex, mesh->tex_count++);
		i++;
	}
}

void add_bottom_cap(t_mesh* mesh, t_shpere_vars* vars, t_sphere_params* params)
{
	int bottom;
	t_uint i;

	bottom = mesh->verts_count - vars->vert_start - 1;
	mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 1) * sizeof(int) * 3, mesh->tris_count * sizeof(int) * 3);
	ivec3_to_array(&(t_ivec3) { bottom, bottom - params->slices, bottom - 1 }, mesh->tris, mesh->tris_count++);
	mesh->tex = ft_realloc(mesh->tex, (mesh->tex_count + 3) * sizeof(float) * 2, mesh->tex_count * sizeof(float) * 2);
	vec2_to_array(&(t_vec2) { 1, 0 }, mesh->tex, mesh->tex_count++);
	vec2_to_array(&(t_vec2) { 1, 1.0f / params->stacks }, mesh->tex, mesh->tex_count++);
	vec2_to_array(&(t_vec2) { (float)(params->slices - 1) / params->slices, 1.0f / params->stacks }, mesh->tex, mesh->tex_count++);
	i = 1;
	while (i < params->slices)
	{
		mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 1) * sizeof(int) * 3, mesh->tris_count * sizeof(int) * 3);
		ivec3_to_array(&(t_ivec3) { bottom, bottom - i, bottom - i - 1 }, mesh->tris, mesh->tris_count++);
		mesh->tex = ft_realloc(mesh->tex, (mesh->tex_count + 3) * sizeof(float) * 2, mesh->tex_count * sizeof(float) * 2);
		vec2_to_array(&(t_vec2) { (float)(params->slices - i) / params->slices, 0 }, mesh->tex, mesh->tex_count++);
		vec2_to_array(&(t_vec2) { (float)(params->slices - i) / params->slices, 1.0f / params->stacks }, mesh->tex, mesh->tex_count++);
		vec2_to_array(&(t_vec2) { (float)(params->slices - i - 1) / params->slices, 1.0f / params->stacks }, mesh->tex, mesh->tex_count++);
		i++;
	}
	i = vars->tri_start;
	while (i < mesh->tris_count)
	{
		ivec3_to_array(&(t_ivec3) { mesh->tris[i * 3] + vars->vert_start, mesh->tris[i * 3 + 1] + vars->vert_start, mesh->tris[i * 3 + 2] + vars->vert_start }, mesh->tris, i);
		i++;
	}
}

