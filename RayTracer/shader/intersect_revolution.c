/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_revolution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 03:52:33 by agaley            #+#    #+#             */
/*   Updated: 2024/03/19 18:50:37 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	calculate_cone_discriminant(t_ray *ray, t_shape *cone,
		t_vec3 *coeff)
{
	t_vec3			co_to_ray_origin;
	t_vec3			cone_axis_normalized;
	float			cos_theta_squared;
	float			angle_radians;
	t_cone_props	*props;

	props = cone->properties;
	angle_radians = props->angle * (M_PI / 180.0);
	cos_theta_squared = cos(angle_radians) * cos(angle_radians);
	cone_axis_normalized = norm_vec3(props->axis);
	co_to_ray_origin = sub_vec3s(ray->ori, cone->position);
	coeff->x = dot_vec3s(ray->dir, cone_axis_normalized) * dot_vec3s(ray->dir,
			cone_axis_normalized) - cos_theta_squared;
	coeff->y = 2 * (dot_vec3s(ray->dir, cone_axis_normalized)
			* dot_vec3s(co_to_ray_origin, cone_axis_normalized)
			- dot_vec3s(ray->dir, co_to_ray_origin) * cos_theta_squared);
	coeff->z = dot_vec3s(co_to_ray_origin, cone_axis_normalized)
		* dot_vec3s(co_to_ray_origin, cone_axis_normalized)
		- dot_vec3s(co_to_ray_origin, co_to_ray_origin) * cos_theta_squared;
	return ((coeff->y) * (coeff->y) - 4 * (coeff->x) * (coeff->z));
}

static float	calculate_cy_discriminant(t_ray *ray, t_shape *cy,
		t_vec3 *coeff)
{
	t_vec3				oc;
	t_vec3				coeff;
	float				discriminant;
	t_vec2				t;
	t_cylinder_props	*props;

	props = cy->properties;
	oc = sub_vec3s(ray->ori, cy->position);
	coeff->x = dot_vec3s(ray->dir, ray->dir) - pow(dot_vec3s(ray->dir,
				props->axis), 2);
	coeff->y = 2 * (dot_vec3s(ray->dir, oc) - (dot_vec3s(ray->dir, props->axis)
				* dot_vec3s(oc, props->axis)));
	coeff->z = dot_vec3s(oc, oc) - pow(dot_vec3s(oc, props->axis), 2)
		- pow(props->diameter / 2, 2);
	return (coeff->y * coeff->y - 4 * coeff->x * coeff->z);
}

static bool	check_intersection_conditions(float t, t_ray *ray, t_shape *revol,
		t_hit *hit, float *closest_t)
{
	float	hit_to_axis_projection;
	t_vec3	hit_point;
	t_vec3	revol_to_hit_point;

	hit_point = add_vec3s(ray->ori, mult_vec3_scalar(ray->dir, t));
	revol_to_hit_point = sub_vec3s(hit_point, revol->position);
	hit_to_axis_projection = dot_vec3s(revol_to_hit_point,
			revol->properties->axis);
	if (fabs(hit_to_axis_projection) <= revol->properties->height / 2)
	{
		if (t < *closest_t)
		{
			*closest_t = t;
			hit->distance = t;
			hit->point = hit_point;
			hit->normal = norm_vec3(sub_vec3s(revol_to_hit_point,
						mult_vec3_scalar(revol->properties->axis,
							hit_to_axis_projection)));
			hit->color = revol->color;
			return (true);
		}
	}
	return (false);
}

static bool	find_intersections(t_ray *ray, t_shape *cone, t_hit *hit, t_vec2 t)
{
	float	closest_t;
	bool	found_intersection;

	closest_t = INFINITY;
	found_intersection = false;
	if (t.x >= EPSILON && check_intersection_conditions(t.x, ray, cone, hit,
			&closest_t))
		found_intersection = true;
	if (t.y >= EPSILON && check_intersection_conditions(t.y, ray, cone, hit,
			&closest_t))
		found_intersection = true;
	return (found_intersection);
}

bool	intersect_revolution(t_ray *ray, t_shape *revol, t_hit *hit)
{
	t_vec2	t;
	t_vec3	coeff;
	float	discriminant;

	if (revol->type == CYLINDER)
		discriminant = calculate_cy_discriminant(ray, revol, &coeff);
	else if (revol->type == CONE)
		discriminant = calculate_cone_discriminant(ray, revol, &coeff);
	if (discriminant < 0)
		return (false);
	t.x = -(sqrt(discriminant) + coeff.y) / (2 * coeff.x);
	t.y = (sqrt(discriminant) - coeff.y) / (2 * coeff.x);
	return (find_intersections(ray, revol, hit, t));
}
