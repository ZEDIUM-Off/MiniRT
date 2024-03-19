/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 04:52:23 by agaley            #+#    #+#             */
/*   Updated: 2024/03/19 18:51:32 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	check_intersection_conditions(float t, t_ray *ray, t_shape *cy,
		t_hit *hit, float *closest_t)
{
	t_vec3				hit_point;
	t_vec3				cy_to_hit_point;
	float				hit_to_axis_projection;
	t_cylinder_props	*props;

	props = cy->properties;
	hit_point = add_vec3s(ray->ori, mult_vec3_scalar(ray->dir, t));
	cy_to_hit_point = sub_vec3s(hit_point, cy->position);
	hit_to_axis_projection = dot_vec3s(cy_to_hit_point, props->axis);
	if (fabs(hit_to_axis_projection) <= props->height / 2)
	{
		if (t < *closest_t)
		{
			*closest_t = t;
			hit->distance = t;
			hit->point = hit_point;
			hit->normal = norm_vec3(sub_vec3s(cy_to_hit_point,
						mult_vec3_scalar(props->axis, hit_to_axis_projection)));
			hit->color = cy->color;
			return (true);
		}
	}
	return (false);
}

static bool	find_intersections(t_ray *ray, t_shape *cy, t_hit *hit, t_vec2 t)
{
	float	closest_t;
	bool	found_intersection;

	closest_t = INFINITY;
	found_intersection = false;
	if (t.x >= EPSILON && check_intersection_conditions(t.x, ray, cy, hit,
			&closest_t))
		found_intersection = true;
	if (t.y >= EPSILON && check_intersection_conditions(t.y, ray, cy, hit,
			&closest_t))
		found_intersection = true;
	return (found_intersection);
}

bool	intersect_cylinder(t_ray *ray, t_shape *cy, t_hit *hit)
{
	t_vec3	coeff;
	float	discriminant;
	t_vec2	t;

	discriminant = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (discriminant < 0)
		return (false);
	t.x = (sqrt(discriminant) - coeff.y) / (2 * coeff.x);
	t.y = -(sqrt(discriminant) + coeff.y) / (2 * coeff.x);
	return (find_intersections(ray, cy, hit, t));
}
