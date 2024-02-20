/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 05:54:33 by agaley            #+#    #+#             */
/*   Updated: 2024/02/20 16:00:17 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// TODO : Load dynamically from parsed map
t_sphere	scene_spheres[] = {
    {{0.0, 0.0, -5.0}, 1.0, { {0.1, 0.2, 0.3}, {0.4, 0.5, 0.6}, {0.7, 0.8, 0.9}, 10.0, 1.5 }},
    {{2.0, 1.0, -6.0}, 1.5, { {0.2, 0.3, 0.4}, {0.5, 0.6, 0.7}, {0.8, 0.9, 1.0}, 20.0, 2.5 }}
};

/**
 * Checks for the intersection between a ray and a sphere.
 * 
 * @param ray_origin The origin point of the ray.
 * @param ray_direction The direction vector of the ray.
 * @param sphere The sphere to check for intersection with.
 * @param hit Intersection details will be stored if an intersection occurs.
 * @return True if there is an intersection.
 */
bool	intersect_sphere(const t_vec3 ray_origin, const t_vec3 ray_direction,
			const t_sphere sphere, t_hit *hit) {
	t_vec3	oc;
	t_vec3	v;
	float	discr;
	float	temp;

	oc = sub_vec3s(ray_origin, sphere.center);
	v.x = dot_vec3s(ray_direction, ray_direction);
	v.y = 2.0 * dot_vec3s(oc, ray_direction);
	v.z = dot_vec3s(oc, oc) - sphere.radius * sphere.radius;
	discr = v.y * v.y - 4 * v.x * v.z;
	if (discr > 0)
	{
		temp = (-v.y - sqrt(discr)) / (2.0 * v.x);
		if (temp > 0.001)
		{
			hit->point = add_vec3s(ray_origin,
					mult_vec3_scalar(ray_direction, temp));
			hit->normal = norm_vec3(sub_vec3s(hit->point, sphere.center));
			hit->material = sphere.material;
			return (true);
		}
	}
	return (false);
}

/**
 * Checks for intersections between a ray and objects in the scene.
 * 
 * Checks for an intersection with objects and the given ray.
 * Updates the hit structure with details of the closest intersection.
 * 
 * @param ray_origin The origin point of the ray.
 * @param ray_direction The direction vector of the ray.
 * @param hit Closest intersection details.
 * @return True if there is an intersection with any object in the scene.
 */
bool	intersect_scene(const t_vec3 ray_origin, const t_vec3 ray_direction,
			t_hit *hit) {
	t_hit	h;
	bool	has_hit_anything;
	float	closest_so_far;
	int		num_spheres;
	int		i;

	num_spheres = sizeof(scene_spheres) / sizeof(t_sphere);
	has_hit_anything = false;
	closest_so_far = FLT_MAX;
	i = 0;
	while (i < num_spheres)
	{
		if (intersect_sphere(ray_origin, ray_direction, scene_spheres[i], &h))
		{
			if (h.distance < closest_so_far)
			{
				closest_so_far = h.distance;
				*hit = h;
				has_hit_anything = true;
			}
		}
		i++;
	}
	return (has_hit_anything);
}
