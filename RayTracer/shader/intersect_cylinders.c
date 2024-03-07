/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 04:52:23 by agaley            #+#    #+#             */
/*   Updated: 2024/03/07 13:49:26 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	intersect_cylinder(const t_ray *ray, const t_cylinder cylinder,
		t_hit *hit)
{
	t_vec3	oc;
	t_vec3	coeff;
	float	discriminant;
	float	t1;
	float	t2;
	float	t;
	t_vec3	hit_point;
	t_vec3	cylinder_to_hit_point;
	float	hit_to_axis_projection;

	oc = sub_vec3s(ray->ori, cylinder.position);
	coeff.x = dot_vec3s(ray->dir, ray->dir) - pow(dot_vec3s(ray->dir,
				cylinder.axis), 2);
	coeff.y = 2 * (dot_vec3s(ray->dir, oc) - (dot_vec3s(ray->dir, cylinder.axis)
				* dot_vec3s(oc, cylinder.axis)));
	coeff.z = dot_vec3s(oc, oc) - pow(dot_vec3s(oc, cylinder.axis), 2)
		- pow(cylinder.diameter / 2, 2);
	discriminant = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (discriminant < 0)
		return (false);
	t1 = (-coeff.y - sqrt(discriminant)) / (2 * coeff.x);
	t2 = (-coeff.y + sqrt(discriminant)) / (2 * coeff.x);
	for (int i = 0; i < 2; i++)
	{
		t = (i == 0) ? t1 : t2;
		if (t <= EPSILON)
			continue ;
		hit_point = add_vec3s(ray->ori, mult_vec3_scalar(ray->dir, t));
		cylinder_to_hit_point = sub_vec3s(hit_point, cylinder.position);
		hit_to_axis_projection = dot_vec3s(cylinder_to_hit_point,
				cylinder.axis);
		if (fabs(hit_to_axis_projection) <= cylinder.height / 2)
		{
			hit->distance = t;
			hit->point = hit_point;
			hit->normal = norm_vec3(sub_vec3s(cylinder_to_hit_point,
						mult_vec3_scalar(cylinder.axis,
							hit_to_axis_projection)));
			hit->color = cylinder.color;
			return (true);
		}
	}
	return (false);
}

bool	check_cylinders_intersection(const t_ray *ray, t_hit *closest_hit,
		float *closest_so_far, t_rt *rt)
{
	t_hit	hit;
	bool	has_hit;
	size_t	i;

	has_hit = false;
	i = 0;
	while (i < rt->sc_input.shapes.cy_count)
	{
		hit.distance = FLT_MAX;
		if (intersect_cylinder(ray, rt->sc_input.shapes.cylinders[i], &hit))
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
