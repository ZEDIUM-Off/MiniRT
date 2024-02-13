/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 05:54:33 by agaley            #+#    #+#             */
/*   Updated: 2024/02/13 06:25:11 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include <minirt.h>

// TODO : Load dynamically from parsed map
t_sphere scene_spheres[] = {
    {{0.0, 0.0, -5.0}, 1.0, { {0.1, 0.2, 0.3}, {0.4, 0.5, 0.6}, {0.7, 0.8, 0.9}, 10.0, 1.5 }},
    {{2.0, 1.0, -6.0}, 1.5, { {0.2, 0.3, 0.4}, {0.5, 0.6, 0.7}, {0.8, 0.9, 1.0}, 20.0, 2.5 }}
};

/**
 * Checks for the intersection between a ray and a sphere.
 * 
 * @param ray_origin The origin point of the ray.
 * @param ray_direction The direction vector of the ray.
 * @param sphere The sphere to check for intersection with.
 * @param hit Pointer to a structure where intersection details will be stored if an intersection occurs.
 * @return True if there is an intersection, otherwise false. Also updates hit with intersection details if an intersection occurs.
 */
bool intersect_sphere(const t_vec3 ray_origin, const t_vec3 ray_direction, const t_sphere sphere, t_hit *hit) {
    t_vec3 oc;
	
	oc = sub_vec3s(ray_origin, sphere.center);
    float a = dot_vec3s(ray_direction, ray_direction);
    float b = 2.0 * dot_vec3s(oc, ray_direction);
    float c = dot_vec3s(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant)) / (2.0 * a);
        if (temp > 0.001) // Avoids intersections at negative distances and very close to the ray origin
		{
            // Update hit with intersection details
            hit->point = add_vec3s(ray_origin, mult_vec3_scalar(ray_direction, temp));
            hit->normal = norm_vec3(sub_vec3s(hit->point, sphere.center));
            hit->material = sphere.material;
            return true;
        }
    }
    return false;
}

/**
 * Checks for intersections between a ray and all spheres in the scene.
 * 
 * Iterates through each sphere in the scene and checks for an intersection with the given ray.
 * If an intersection occurs, updates the hit structure with details of the closest intersection.
 * 
 * @param ray_origin The origin point of the ray.
 * @param ray_direction The direction vector of the ray.
 * @param hit Pointer to a structure where the closest intersection details will be stored, if any.
 * @return True if there is an intersection with any sphere in the scene, otherwise false.
 */
bool intersect_scene(const t_vec3 ray_origin, const t_vec3 ray_direction, t_hit *hit) {
	t_hit	temp_hit;
    bool	has_hit_anything;
    float	closest_so_far;
	int		num_spheres;

	num_spheres = sizeof(scene_spheres) / sizeof(t_sphere);
	has_hit_anything = false;
	closest_so_far = FLT_MAX;
    for (int i = 0; i < num_spheres; i++) {
        if (intersect_sphere(ray_origin, ray_direction, scene_spheres[i], &temp_hit)) {
            if (temp_hit.distance < closest_so_far) {
                closest_so_far = temp_hit.distance;
                *hit = temp_hit;
                has_hit_anything = true;
            }
        }
    }
    return has_hit_anything;
}