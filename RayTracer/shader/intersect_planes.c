/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_planes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:55:31 by agaley            #+#    #+#             */
/*   Updated: 2024/03/07 00:57:29 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Checks for the intersection between a ray and a plane.
 *
 * @param ray The ray to check for intersection.
 * @param plane The plane to check for intersection with.
 * @param hit Intersection details will be stored if an intersection occurs.
 * @return True if there is an intersection.
 */
static bool	intersect_plane(const t_ray *ray, const t_plan plane, t_hit *hit)
{
	t_vec3	plane_norm;
	float	denom;
	t_vec3	p0l0;
	float	t;

	plane_norm = plane.normal;
	denom = dot_vec3s(plane_norm, ray->dir);
	if (fabs(denom) > EPSILON) // Ensure the denominator is not too close to 0
	{
		p0l0 = sub_vec3s(plane.point, ray->ori);
		t = dot_vec3s(p0l0, plane_norm) / denom;
		if (t >= 0) // Check if the plane is in front of the ray
		{
			hit->distance = t;
			hit->point = add_vec3s(ray->ori, mult_vec3_scalar(ray->dir, t));
			hit->normal = plane_norm;
			hit->color = plane.color;
			return (true);
		}
	}
	return (false);
}

bool	check_planes_intersection(const t_ray *ray, t_hit *closest_hit,
		float *closest_so_far, t_rt *rt)
{
	t_hit	h;
	bool	has_hit;
	int		num_planes;

	has_hit = false;
	num_planes = rt->sc_input.shapes.pl_count;
	for (int i = 0; i < num_planes; i++)
	{
		h.distance = FLT_MAX;
		if (intersect_plane(ray, rt->sc_input.shapes.planes[i], &h))
		{
			if (h.distance < *closest_so_far)
			{
				*closest_so_far = h.distance;
				*closest_hit = h;
				has_hit = true;
			}
		}
	}
	return (has_hit);
}
