/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:26:29 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/04 14:52:01 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	scene_init(t_rt* rt)
{
	// t_mesh	plane;
	t_mesh	sphere;
	// t_plane_params	params;
	t_sphere_params	s_params;

	rt->scene.meshes = NULL;
	rt->scene.mesh_count = 0;
	create_mesh(&sphere, MESH_PLANE);
	printf("plane created...\n");
	s_params = (t_sphere_params){ &sphere,1.0, 30, 15, (t_vec3) { 0, 2 , 0 } };
	// params = (t_plane_params){ &plane, (t_vec3) { -2, -2, 0 }, (t_vec3) { 1, 0, 0 }, (t_vec3) { 0, 0, 1 }, 2, 6, false };
	// make_plane(&plane, &params);
	make_sphere(&sphere, &s_params);
	// printf("plane made...\n");
	printf("sphere made... with %d verts and %d tris\n", sphere.verts_count, sphere.tris_count);
	for (t_uint i = 0; i < sphere.tris_count; i++)
	{
		printf("tri %d: %d %d %d\n", i, sphere.tris[i * 3], sphere.tris[i * 3 + 1], sphere.tris[i * 3 + 2]);
	}
	mesh_to_scene(rt, &sphere);
	printf("plane to scene...\n");
}
