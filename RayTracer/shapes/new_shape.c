/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:03:08 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/07 18:33:37 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	new_sphere(t_rt *rt, t_shape *shape)
{
	t_sphere_props	*props;
	t_sphere_params	params;

	(void)rt;
	props = (t_sphere_props *)(shape->properties);
	params = (t_sphere_params){&shape->shape_mesh, props->diameter / 2,
		MESH_DETAIL, MESH_DETAIL, shape->position};
	create_mesh(&shape->shape_mesh, MESH_SPHERE);
	make_sphere(&shape->shape_mesh, &params);
	// mesh_to_scene(rt, &shape->shape_mesh);
}

void	new_plane(t_rt *rt, t_shape *shape)
{
	t_plane_props	*props;
	t_plane_params	params;
	t_vec3			corner;
	t_vec3			v1;
	t_vec3			v2;

	(void)rt;
	props = (t_plane_props *)(shape->properties);
	v1 = (t_vec3){props->normal.y, -props->normal.x, 0};
	if (props->normal.x == 0 && props->normal.y == 0)
		v1.x = 1;
	v2 = cross_product(props->normal, v1);
	v1 = norm_vec3(v1);
	v2 = norm_vec3(v2);
	v1 = scale_vec3s(v1, PLANE_SIZE / 2.0);
	v2 = scale_vec3s(v2, PLANE_SIZE / 2.0);
	corner = sub_vec3s(sub_vec3s(shape->position, v1), v2);
	params = (t_plane_params){.curr_mesh = &shape->shape_mesh, .corner = corner,
		.v1 = v1, .v2 = v2, .dim_v1 = PLANE_SIZE, .dim_v2 = PLANE_SIZE,
		.tile = false};
	create_mesh(&shape->shape_mesh, MESH_PLANE);
	make_plane(&shape->shape_mesh, &params);
	// mesh_to_scene(rt, &shape->shape_mesh);
}

void	new_cylinder(t_rt *rt, t_shape *shape)
{
	t_cylinder_props	*props;
	t_cylinder_params	params;

	(void)rt;
	props = (t_cylinder_props *)(shape->properties);
	params = (t_cylinder_params){&shape->shape_mesh, props->diameter,
		props->height, props->axis, shape->position};
	create_mesh(&shape->shape_mesh, MESH_CYLINDER);
	make_cylinder(&shape->shape_mesh, &params);
	// mesh_to_scene(rt, &shape->shape_mesh);
}

void	new_cone(t_rt *rt, t_shape *shape)
{
	t_cone_props	*props;
	t_cone_params	params;

	(void)rt;
	props = (t_cone_props *)(shape->properties);
	params = (t_cone_params){&shape->shape_mesh, radians(props->angle),
		props->height, props->axis, shape->position};
	create_mesh(&shape->shape_mesh, MESH_CONE);
	make_cone(&shape->shape_mesh, &params);
	// mesh_to_scene(rt, &shape->shape_mesh);
}
