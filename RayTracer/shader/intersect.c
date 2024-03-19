/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 05:54:33 by agaley            #+#    #+#             */
/*   Updated: 2024/03/19 17:18:02 by agaley           ###   ########lyon.fr   */
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
bool	intersect_scene(t_ray *ray, t_hit *hit, t_uniforms *u)
{
	float	closest_so_far;
	bool	intersected;
	size_t	i;
	t_hit	temp_hit;

	intersected = false;
	closest_so_far = FLT_MAX;
	i = 0;
	while (i < u->rt->sc_input.shapes_count)
	{
		temp_hit.distance = FLT_MAX;
		if (u->rt->intersect_shape[u->rt->sc_input.shapes[i].type](ray,
			&u->rt->sc_input.shapes[i], &temp_hit))
		{
			if (temp_hit.distance < closest_so_far)
			{
				*hit = temp_hit;
				intersected = true;
				closest_so_far = temp_hit.distance;
			}
		}
		i++;
	}
	return (intersected);
}
