/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_spheres.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 05:12:05 by agaley            #+#    #+#             */
/*   Updated: 2024/03/07 02:57:26 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Checks for the intersection between a ray and a sphere.
 *
 * @param ray The ray beeing checked for intersection with.
 * @param sphere The sphere to check for intersection with.
 * @param hit Intersection details will be stored if an intersection occurs.
 * @return True if there is an intersection.
 */
static bool	intersect_sphere(const t_ray *ray, const t_sphere sphere,
		t_hit *hit)
{
	t_vec3	sp_c_ray_o;
	t_vec3	coeff;
	float	discr;

	sp_c_ray_o = sub_vec3s(ray->ori, sphere.center);
	coeff.x = dot_vec3s(ray->dir, ray->dir);
	coeff.y = 2.0 * dot_vec3s(sp_c_ray_o, ray->dir);
	coeff.z = dot_vec3s(sp_c_ray_o, sp_c_ray_o) - sphere.radius * sphere.radius;
	discr = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (discr > 0)
	{
		hit->distance = (-coeff.y - sqrt(discr)) / (2.0 * coeff.x);
		if (hit->distance > 0.001)
		{
			hit->point = add_vec3s(ray->ori, mult_vec3_scalar(ray->dir,
						hit->distance));
			hit->normal = norm_vec3(sub_vec3s(hit->point, sphere.center));
			hit->color = sphere.color;
			// hit->material = sphere.material;
			return (true);
		}
	}
	return (false);
}

bool	check_spheres_intersection(const t_ray *ray, t_hit *closest_hit,
		float *closest_so_far, t_rt *rt)
{
	t_hit	hit;
	bool	has_hit;
	size_t	i;

	has_hit = false;
	i = 0;
	while (i < rt->sc_input.shapes.sp_count)
	{
		hit.distance = FLT_MAX;
		if (intersect_sphere(ray, rt->sc_input.shapes.spheres[i], &hit))
		{
			if (hit.distance < *closest_so_far)
			{
				*closest_so_far = hit.distance;
				*closest_hit = hit;
				has_hit = true;
			}
		}
		i++;
	}
	return (has_hit);
}
