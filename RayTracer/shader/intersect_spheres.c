/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_spheres.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 05:12:05 by agaley            #+#    #+#             */
/*   Updated: 2024/03/06 06:59:11 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Checks for the intersection between a ray and a sphere.
 *
 * @param ray_origin The origin point of the ray.
 * @param ray_direction The direction vector of the ray.
 * @param sphere The sphere to check for intersection with.
 * @param hit Intersection details will be stored if an intersection occurs.
 * @return True if there is an intersection.
 */
static bool	intersect_sphere(const t_ray *ray, const t_sphere sphere,
		t_hit *hit)
{
	t_vec3	oc;
	t_vec3	v;
	float	discr;
	float	temp;

	oc = sub_vec3s(ray->ori, sphere.center);
	v.x = dot_vec3s(ray->dir, ray->dir);
	v.y = 2.0 * dot_vec3s(oc, ray->dir);
	v.z = dot_vec3s(oc, oc) - sphere.radius * sphere.radius;
	discr = v.y * v.y - 4 * v.x * v.z;
	if (discr > 0)
	{
		temp = (-v.y - sqrt(discr)) / (2.0 * v.x);
		if (temp > 0.001)
		{
			hit->point = add_vec3s(ray->ori, mult_vec3_scalar(ray->dir, temp));
			hit->normal = norm_vec3(sub_vec3s(hit->point, sphere.center));
			// hit->material = sphere.material;
			return (true);
		}
	}
	return (false);
}

bool	check_spheres_intersection(const t_ray *ray, t_hit *closest_hit,
		float *closest_so_far, t_rt *rt)
{
	t_hit	h;
	bool	has_hit;
	int		num_spheres;
	int		i;

	has_hit = false;
	num_spheres = rt->sc_input.shapes.sp_count;
	i = 0;
	while (i < num_spheres)
	{
		if (intersect_sphere(ray, rt->sc_input.shapes.spheres[i], &h))
		{
			if (h.distance < *closest_so_far)
			{
				*closest_so_far = h.distance;
				*closest_hit = h;
				has_hit = true;
			}
		}
		i++;
	}
	return (has_hit);
}
