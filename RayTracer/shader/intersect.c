/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 05:54:33 by agaley            #+#    #+#             */
/*   Updated: 2024/03/06 06:43:36 by agaley           ###   ########lyon.fr   */
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
	t_hit	closest_hit;
	float	closest_so_far;

	closest_hit = (t_hit){0};
	closest_so_far = FLT_MAX;
	if (check_spheres_intersection(ray, &closest_hit, &closest_so_far, u->rt))
	{
		*hit = closest_hit;
		return (true);
	}
	return (false);
}
