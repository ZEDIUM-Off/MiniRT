/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_spheres.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 05:12:05 by agaley            #+#    #+#             */
/*   Updated: 2024/03/07 15:58:31 by agaley           ###   ########lyon.fr   */
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
bool	intersect_sphere(t_ray *ray, t_shape *sphere, t_hit *hit)
{
	t_vec3			sp_c_ray_o;
	t_vec3			coeff;
	float			discr;
	t_sphere_props	*props;

	props = sphere->properties;
	sp_c_ray_o = sub_vec3s(ray->ori, sphere->position);
	coeff.x = dot_vec3s(ray->dir, ray->dir);
	coeff.y = 2.0 * dot_vec3s(sp_c_ray_o, ray->dir);
	coeff.z = dot_vec3s(sp_c_ray_o, sp_c_ray_o) - (props->diameter / 2)
		* (props->diameter / 2);
	discr = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (discr > 0)
	{
		hit->distance = (-coeff.y - sqrt(discr)) / (2.0 * coeff.x);
		if (hit->distance > 0.001)
		{
			hit->point = add_vec3s(ray->ori, mult_vec3_scalar(ray->dir,
						hit->distance));
			hit->normal = norm_vec3(sub_vec3s(hit->point, sphere->position));
			hit->color = sphere->color;
			// hit->material = sphere->material;
			return (true);
		}
	}
	return (false);
}
