/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:26:29 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/21 16:59:16 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	scene_init(t_rt* rt)
{
	t_mesh	plane;
	t_plane_params	params;

	rt->scene.meshes = NULL;
	rt->scene.mesh_count = 0;
	create_mesh(&plane, MESH_PLANE);
	printf("plane created...\n");
	params = (t_plane_params){ &plane, (t_vec3) { -2, -2, 0 }, (t_vec3) { 1, 0, 0 }, (t_vec3) { 0, 0, 1 }, 2, 6, false };
	make_plane(&plane, &params);
	printf("plane made...\n");
	mesh_to_scene(rt, &plane);
	printf("plane to scene...\n");
}