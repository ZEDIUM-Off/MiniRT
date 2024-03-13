/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:26:29 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/14 00:17:57 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	update_scene(t_rt *rt)
{
	free(rt->all_meshes.verts);
	free(rt->all_meshes.tris);
	free(rt->all_meshes.normals);
	rt->all_meshes.verts_count = 0;
	rt->all_meshes.tris_count = 0;
	rt->all_meshes.normals_count = 0;
	all_mesh_to_scene(rt);
}

void	scene_init(t_rt *rt)
{
	all_mesh_to_scene(rt);
}
