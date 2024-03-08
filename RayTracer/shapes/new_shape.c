/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zorin <zorin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:03:08 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/08 03:30:04 by zorin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	new_sphere(t_rt *rt, t_shape *shape)
{
	t_sphere_props	*props;
	t_sphere_params	params;

	props = (t_sphere_props *)(shape->properties);
	params = (t_sphere_params){&shape->shape_mesh, props->diameter / 2,
		MESH_DETAIL, MESH_DETAIL, shape->position};
	make_sphere(&rt->all_meshes, &params);
}

void	new_plane(t_rt *rt, t_shape *shape)
{
	t_plane_props	*props;
	t_plane_params	params;

	props = (t_plane_props *)(shape->properties);
	params = (t_plane_params){&shape->shape_mesh, shape->position,
		props->normal};
	make_plane(&rt->all_meshes, &params);
}

void	new_cylinder(t_rt *rt, t_shape *shape)
{
	t_cylinder_props	*props;
	t_cylinder_params	params;

	props = (t_cylinder_props *)(shape->properties);
	params = (t_cylinder_params){&shape->shape_mesh, props->diameter,
		props->height, props->axis, shape->position};
	make_cylinder(&rt->all_meshes, &params);
}

void	new_cone(t_rt *rt, t_shape *shape)
{
	t_cone_props	*props;
	t_cone_params	params;

	props = (t_cone_props *)(shape->properties);
	params = (t_cone_params){&shape->shape_mesh, radians(props->angle),
		props->height, props->axis, shape->position};
	make_cone(&rt->all_meshes, &params);
}
