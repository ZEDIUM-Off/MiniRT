/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 05:54:33 by agaley            #+#    #+#             */
/*   Updated: 2024/03/07 05:06:45 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

/**
 * Checks for an intersection with objects and the given ray.
 * Updates the hit structure with details of the closest intersection.
 *
 * @param ray_origin The origin point of the ray.
 * @param ray_direction The direction vector of the ray.
 * @param hit Closest intersection details.
 * @return True if there is an intersection with any object in the scene.
 */
bool	intersect_scene(const t_ray *ray, t_hit *hit, t_uniforms *u)
{
	t_hit	temp_hit;
	float	closest_so_far;
	bool	intersected;

	intersected = false;
	hit->distance = FLT_MAX;
	closest_so_far = FLT_MAX;
	if (check_planes_intersection(ray, &temp_hit, &closest_so_far, u->rt))
	{
		intersected = true;
		if (temp_hit.distance < hit->distance)
			*hit = temp_hit;
	}
	if (check_spheres_intersection(ray, &temp_hit, &closest_so_far, u->rt))
	{
		intersected = true;
		if (temp_hit.distance < hit->distance)
			*hit = temp_hit;
	}
	if (check_cylinders_intersection(ray, &temp_hit, &closest_so_far, u->rt))
	{
		intersected = true;
		if (temp_hit.distance < hit->distance)
			*hit = temp_hit;
	}
	if (check_cones_intersection(ray, &temp_hit, &closest_so_far, u->rt))
	{
		intersected = true;
		if (temp_hit.distance < hit->distance)
			*hit = temp_hit;
	}
	return (intersected);
}
