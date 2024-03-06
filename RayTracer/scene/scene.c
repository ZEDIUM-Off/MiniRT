/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:26:29 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/06 14:29:30 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	scene_init(t_rt* rt)
{
	// t_mesh	plane;
	// t_mesh	sphere;
	// t_plane_params	params;
	// t_sphere_params	s_params;
	// t_cylinder_params	c_params;
	// t_mesh		cylinder;
	t_mesh		cone;
	t_cone_params	c_params;

	rt->scene.meshes = NULL;
	rt->scene.mesh_count = 0;
	create_mesh(&cone, MESH_PLANE);
	printf("plane created...\n");
	c_params = (t_cone_params){ &cone,radians(30), 3, (t_vec3){0,1,0}, (t_vec3){0,0,0}};
	// params = (t_plane_params){ &plane, (t_vec3) { -2, -2, 0 }, (t_vec3) { 1, 0, 0 }, (t_vec3) { 0, 0, 1 }, 2, 6, false };
	// make_plane(&plane, &params);
	make_cone(&cone, &c_params);
	// printf("plane made...\n");
	// printf("sphere made... with %d verts and %d tris\n", sphere.verts_count, sphere.tris_count);

	mesh_to_scene(rt, &cone);
	printf("plane to scene...\n");
}
