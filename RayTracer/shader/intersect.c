/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 05:54:33 by agaley            #+#    #+#             */
/*   Updated: 2024/02/21 19:54:33 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// TODO : Load dynamically from parsed map
// t_sphere	scene_spheres[] = {
// 	{{0.0, 0.0, -5.0}, 1.0, { {0.1, 0.2, 0.3}, {0.4, 0.5, 0.6}, {0.7, 0.8, 0.9}, 10.0, 1.5 }},
// 	{{2.0, 1.0, -6.0}, 1.5, { {0.2, 0.3, 0.4}, {0.5, 0.6, 0.7}, {0.8, 0.9, 1.0}, 20.0, 2.5 }}
// };

/**
 * Implements the Möller-Trumbore intersection algorithm to check for intersection between a ray and a triangle.
 *
 * @param ray_origin The origin point of the ray.
 * @param ray_direction The direction vector of the ray.
 * @param triangle The triangle to check for intersection with.
 * @param hit Intersection details will be stored if an intersection occurs.
 * @return True if there is an intersection.
 */
bool intersect_triangle(const t_vec3 ray_origin, const t_vec3 ray_direction,
	const t_triangle triangle, t_hit* hit) {
	t_vec3 edge1;
	t_vec3 edge2;
	t_vec3 h;
	t_vec3 s;
	t_vec3 q;
	float a;
	float f;
	float u;
	float v;
	float t;

	edge1 = sub_vec3s(triangle.v1, triangle.v0);
	edge2 = sub_vec3s(triangle.v2, triangle.v0);
	h = cross_product(ray_direction, edge2);
	a = dot_vec3s(edge1, h);

	if (-FLT_EPSILON > a && a < FLT_EPSILON)
		return false; // This ray is parallel to this triangle.

	f = 1.0 / a;
	s = sub_vec3s(ray_origin, triangle.v0);
	u = f * dot_vec3s(s, h);

	if (u < 0.0 || u > 1.0)
		return false;

	q = cross_product(s, edge1);
	v = f * dot_vec3s(ray_direction, q);

	// printf("v: %f - u+v: %f\n", v, u + v);

	if (v < 0.0 || u + v > 1.0)
		return false;

	// At this stage we can compute t to find out where the intersection point is on the line.
	t = f * dot_vec3s(edge2, q);

	// printf("t: %f\n", t);

	if (t > FLT_EPSILON) // ray intersection
	{
		hit->distance = t;
		hit->point = add_vec3s(ray_origin, mult_vec3_scalar(ray_direction, t));
		hit->normal = norm_vec3(cross_product(edge1, edge2)); // assuming non-degenerate triangle
		hit->color = triangle.color;
		return true;
	}
	else // This means that there is a line intersection but not a ray intersection.
		return false;
}

bool check_triangles_intersection(const t_vec3 ray_origin, const t_vec3 ray_direction, t_hit* closest_hit, float* closest_so_far, t_uniforms* u) {
	t_hit h;
	bool has_hit = false;
	int num_triangles;
	int i;

	t_triangle scene_triangles[] = {
		{vec4_to_vec3(mult_mat4_vec4(u->mvp_mat, (t_vec4){-0.5, 0, -0.5, 1})), vec4_to_vec3(mult_mat4_vec4(u->mvp_mat, (t_vec4){0.5, 0, -0.5, 1})), vec4_to_vec3(mult_mat4_vec4(u->mvp_mat, (t_vec4){0.5, 0, 0.5, 1})), {1.0, 0, 0}, MATERIAL_LAMBERTIAN},
		{vec4_to_vec3(mult_mat4_vec4(u->mvp_mat, (t_vec4){-0.5, 0, -0.5, 1})), vec4_to_vec3(mult_mat4_vec4(u->mvp_mat, (t_vec4){-0.5, 0, 0.5, 1})), vec4_to_vec3(mult_mat4_vec4(u->mvp_mat, (t_vec4){0.5, 0, 0.5, 1})), {0, 1.0, 0}, MATERIAL_LAMBERTIAN}
	};

	num_triangles = sizeof(scene_triangles) / sizeof(t_triangle);
	for (i = 0; i < num_triangles; i++) {

		if (intersect_triangle(ray_origin, ray_direction, scene_triangles[i], &h)) {
			if (h.distance < *closest_so_far) {
				*closest_so_far = h.distance;
				*closest_hit = h;
				has_hit = true;
			}
		}
	}
	return has_hit;
}

/**
 * Checks for an intersection with objects and the given ray.
 * Updates the hit structure with details of the closest intersection.
 *
 * @param ray_origin The origin point of the ray.
 * @param ray_direction The direction vector of the ray.
 * @param hit Closest intersection details.
 * @return True if there is an intersection with any object in the scene.
 */
bool intersect_scene(const t_vec3 ray_origin, const t_vec3 ray_direction, t_hit* hit, t_uniforms* u) {
	t_hit closest_hit;
	float closest_so_far;

	closest_hit = (t_hit){ 0 };
	closest_so_far = FLT_MAX;

	if (check_triangles_intersection(ray_origin, ray_direction, &closest_hit, &closest_so_far, u)) {
		*hit = closest_hit;
		return(true);
	}
	return (false);
}
// /**
//  * Checks for the intersection between a ray and a sphere.
//  *
//  * @param ray_origin The origin point of the ray.
//  * @param ray_direction The direction vector of the ray.
//  * @param sphere The sphere to check for intersection with.
//  * @param hit Intersection details will be stored if an intersection occurs.
//  * @return True if there is an intersection.
//  */
// bool	intersect_sphere(const t_vec3 ray_origin, const t_vec3 ray_direction,
// 	const t_sphere sphere, t_hit* hit) {
// 	t_vec3	oc;
// 	t_vec3	v;
// 	float	discr;
// 	float	temp;

// 	oc = sub_vec3s(ray_origin, sphere.center);
// 	v.x = dot_vec3s(ray_direction, ray_direction);
// 	v.y = 2.0 * dot_vec3s(oc, ray_direction);
// 	v.z = dot_vec3s(oc, oc) - sphere.radius * sphere.radius;
// 	discr = v.y * v.y - 4 * v.x * v.z;
// 	if (discr > 0)
// 	{
// 		temp = (-v.y - sqrt(discr)) / (2.0 * v.x);
// 		if (temp > 0.001)
// 		{
// 			hit->point = add_vec3s(ray_origin,
// 				mult_vec3_scalar(ray_direction, temp));
// 			hit->normal = norm_vec3(sub_vec3s(hit->point, sphere.center));
// 			hit->material = sphere.material;
// 			return (true);
// 		}
// 	}
// 	return (false);
// }

// bool check_spheres_intersection(const t_vec3 ray_origin, const t_vec3 ray_direction, t_hit* closest_hit, float* closest_so_far) {
// 	t_hit h;
// 	bool has_hit = false;
// 	int num_spheres;
// 	int i;

// 	num_spheres = sizeof(scene_spheres) / sizeof(t_sphere);
// 	i = 0;
// 	while (i < num_spheres) {
// 		if (intersect_sphere(ray_origin, ray_direction, scene_spheres[i], &h)) {
// 			if (h.distance < *closest_so_far) {
// 				*closest_so_far = h.distance;
// 				*closest_hit = h;
// 				has_hit = true;
// 			}
// 		}
// 		i++;
// 	}
// 	return has_hit;
// }
