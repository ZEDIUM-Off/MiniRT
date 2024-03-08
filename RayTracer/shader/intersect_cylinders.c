/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 04:52:23 by agaley            #+#    #+#             */
/*   Updated: 2024/03/07 17:19:11 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersect_cylinder(t_ray *ray, t_shape *cy, t_hit *hit)
{
	t_vec3				oc;
	t_vec3				coeff;
	float				discriminant;
	float				t1;
	float				t2;
	float				t;
	t_vec3				hit_point;
	t_vec3				cy_to_hit_point;
	float				hit_to_axis_projection;
	t_cylinder_props	*props;
	int					i;

	props = cy->properties;
	oc = sub_vec3s(ray->ori, cy->position);
	coeff.x = dot_vec3s(ray->dir, ray->dir) - pow(dot_vec3s(ray->dir,
				props->axis), 2);
	coeff.y = 2 * (dot_vec3s(ray->dir, oc) - (dot_vec3s(ray->dir, props->axis)
				* dot_vec3s(oc, props->axis)));
	coeff.z = dot_vec3s(oc, oc) - pow(dot_vec3s(oc, props->axis), 2)
		- pow(props->diameter / 2, 2);
	discriminant = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (discriminant < 0)
		return (false);
	t1 = (sqrt(discriminant) - coeff.y) / (2 * coeff.x);
	t2 = (sqrt(discriminant) - coeff.y) / (2 * coeff.x);
	i = 0;
	while (i < 2)
	{
		if (i == 0 && t1 > EPSILON)
			t = t1;
		else if (i == 1 && t2 > EPSILON)
			t = t2;
		else
			return (false);
		hit_point = add_vec3s(ray->ori, mult_vec3_scalar(ray->dir, t));
		cy_to_hit_point = sub_vec3s(hit_point, cy->position);
		hit_to_axis_projection = dot_vec3s(cy_to_hit_point, props->axis);
		if (fabs(hit_to_axis_projection) <= props->height / 2)
		{
			hit->distance = t;
			hit->point = hit_point;
			hit->normal = norm_vec3(sub_vec3s(cy_to_hit_point,
						mult_vec3_scalar(props->axis, hit_to_axis_projection)));
			hit->color = cy->color;
			return (true);
		}
		i++;
	}
	return (false);
}
