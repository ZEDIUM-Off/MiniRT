/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cones.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 03:52:33 by agaley            #+#    #+#             */
/*   Updated: 2024/03/07 13:49:20 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	calculate_discriminant(const t_ray *ray, const t_cone cone,
		float *a, float *b, float *c)
{
	t_vec3	co_to_ray_origin;
	t_vec3	cone_axis_normalized;
	float	cos_theta_squared;
	float	angle_radians;

	angle_radians = cone.angle * (3.1416 / 180.0);
	cos_theta_squared = cos(angle_radians) * cos(angle_radians);
	cone_axis_normalized = norm_vec3(cone.axis);
	co_to_ray_origin = sub_vec3s(ray->ori, cone.position);
	*a = dot_vec3s(ray->dir, cone_axis_normalized) * dot_vec3s(ray->dir,
			cone_axis_normalized) - cos_theta_squared;
	*b = 2 * (dot_vec3s(ray->dir, cone_axis_normalized)
			* dot_vec3s(co_to_ray_origin, cone_axis_normalized)
			- dot_vec3s(ray->dir, co_to_ray_origin) * cos_theta_squared);
	*c = dot_vec3s(co_to_ray_origin, cone_axis_normalized)
		* dot_vec3s(co_to_ray_origin, cone_axis_normalized)
		- dot_vec3s(co_to_ray_origin, co_to_ray_origin) * cos_theta_squared;
	return ((*b) * (*b) - 4 * (*a) * (*c));
}

static t_vec3	calculate_cone_normal(const t_cone cone, t_vec3 hit_point)
{
	float	hit_to_axis_projection;
	t_vec3	base_point;
	t_vec3	cone_axis_normalized;
	t_vec3	hit_to_cone_base;
	t_vec3	normal;

	cone_axis_normalized = norm_vec3(cone.axis);
	hit_to_cone_base = sub_vec3s(hit_point, cone.position);
	hit_to_axis_projection = dot_vec3s(hit_to_cone_base, cone_axis_normalized);
	base_point = add_vec3s(cone.position, mult_vec3_scalar(cone_axis_normalized,
				hit_to_axis_projection));
	normal = sub_vec3s(hit_point, base_point);
	normal = norm_vec3(normal);
	return (normal);
}

static bool	intersect_cone(const t_ray *ray, const t_cone cone, t_hit *hit)
{
	float	hit_to_axis_projection;
	float	t;

	float a, b, c, discriminant, t1, t2;
	t_vec3 hit_point, cone_to_hit_point;
	discriminant = calculate_discriminant(ray, cone, &a, &b, &c);
	if (discriminant < 0)
		return (false); // No intersection
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	// Check both potential intersection points
	for (int i = 0; i < 2; i++)
	{
		t = (i == 0) ? t1 : t2;
		if (t <= EPSILON)
			continue ; // Ignore intersections behind the ray origin
		hit_point = add_vec3s(ray->ori, mult_vec3_scalar(ray->dir, t));
		cone_to_hit_point = sub_vec3s(hit_point, cone.position);
		hit_to_axis_projection = dot_vec3s(cone_to_hit_point,
				norm_vec3(cone.axis));
		// Ensure the hit point is within the cone's height
		if (hit_to_axis_projection >= 0
			&& hit_to_axis_projection <= cone.height)
		{
			hit->distance = t;
			hit->point = hit_point;
			hit->normal = calculate_cone_normal(cone, hit->point);
			hit->color = cone.color;
			return (true); // Valid intersection found
		}
	}
	return (false); // No valid intersection within the cone's height
}

bool	check_cones_intersection(const t_ray *ray, t_hit *closest_hit,
		float *closest_so_far, t_rt *rt)
{
	t_hit	hit;
	bool	has_hit;
	size_t	i;

	has_hit = false;
	i = 0;
	while (i < rt->sc_input.shapes.co_count)
	{
		hit.distance = FLT_MAX;
		if (intersect_cone(ray, rt->sc_input.shapes.cones[i], &hit))
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
