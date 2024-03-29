/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_planes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:55:31 by agaley            #+#    #+#             */
/*   Updated: 2024/03/08 22:47:15 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Checks for the intersection between a ray and a plane->
 *
 * @param ray The ray to check for intersection.
 * @param plane The plane to check for intersection with.
 * @param hit Intersection details will be stored if an intersection occurs.
 * @return True if there is an intersection.
 */
bool	intersect_plane(t_ray *ray, t_shape *plane, t_hit *hit)
{
	float			denom;
	t_vec3			p0l0;
	float			t;
	t_plane_props	*props;

	props = plane->properties;
	denom = dot_vec3s(props->normal, ray->dir);
	if (fabs(denom) > EPSILON)
	{
		p0l0 = sub_vec3s(plane->position, ray->ori);
		t = dot_vec3s(p0l0, props->normal) / denom;
		if (t > 0)
		{
			hit->distance = t;
			hit->point = add_vec3s(ray->ori, mult_vec3_scalar(ray->dir, t));
			hit->normal = props->normal;
			hit->color = plane->color;
			return (true);
		}
	}
	return (false);
}
