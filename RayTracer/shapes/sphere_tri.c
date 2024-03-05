/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_tri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:56:10 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/04 15:11:26 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	top_pole(t_mesh *mesh, t_sphere_params *params, t_shpere_vars *vars)
{
	size_t	i;
	int		next_i;

	i = 0;
	while (i < params->slices)
	{
		next_i = (i + 1) % params->slices;
		mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 1) * sizeof(int)
				* 3, mesh->tris_count * sizeof(int) * 3);
		ivec3_to_array(&(t_ivec3){vars->pole_top, vars->vert_start + 1 + i,
			vars->vert_start + 1 + next_i}, mesh->tris, mesh->tris_count++);
		i++;
	}
}

static void	sphere_corpus(t_mesh *mesh, t_sphere_params *params,
		t_shpere_vars *vars)
{
	size_t	i;
	size_t	j;
	int		cur;
	int		next;

	j = 0;
	while (j < params->stacks - 2)
	{
		i = 0;
		while (i < params->slices)
		{
			vars->offset = 0;
			if (i == params->slices - 1)
				vars->offset = params->slices;
			cur = vars->vert_start + 1 + j * params->slices + i;
			next = vars->vert_start + 1 + (j + 1) * params->slices + i++;
			mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 2)
					* sizeof(int) * 3, mesh->tris_count * sizeof(int) * 3);
			ivec3_to_array(&(t_ivec3){cur, cur + 1 - vars->offset, next
				+ params->slices}, mesh->tris, mesh->tris_count++);
			ivec3_to_array(&(t_ivec3){next, cur + 1 - vars->offset, next + 1
				- vars->offset}, mesh->tris, mesh->tris_count++);
		}
		j++;
	}
}

static void	bot_pole(t_mesh *mesh, t_sphere_params *params, t_shpere_vars *vars)
{
	size_t	i;
	int		next_i;
	int		bot_start;

	i = 0;
	bot_start = vars->pole_bot - params->slices;
	while (i < params->slices)
	{
		next_i = (i + 1) % params->slices;
		mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 1) * sizeof(int)
				* 3, mesh->tris_count * sizeof(int) * 3);
		ivec3_to_array(&(t_ivec3){vars->pole_bot, bot_start + next_i, bot_start
			+ i}, mesh->tris, mesh->tris_count++);
		i++;
	}
}

void	sphere_push_tris(t_mesh *mesh, t_shpere_vars *vars,
		t_sphere_params *params)
{
	// vars->tot_tris = (params->stacks - 1) * params->slices * 2;
	// mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + vars->tot_tris)
	// 		* sizeof(int) * 3, mesh->tris_count * sizeof(int) * 3);
	top_pole(mesh, params, vars);
	sphere_corpus(mesh, params, vars);
	bot_pole(mesh, params, vars);
}
