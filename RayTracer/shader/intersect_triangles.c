/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_triangles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 05:04:57 by agaley            #+#    #+#             */
/*   Updated: 2024/03/06 05:06:05 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Möller-Trumbore intersection algorithm to check ray-triangle intersection
 *
 * @param ray_origin The origin point of the ray.
 * @param ray_direction The direction vector of the ray.
 * @param triangle The triangle to check for intersection with.
 * @param hit Intersection details will be stored if an intersection occurs.
 * @return True if there is an intersection.
 */
bool	intersect_triangle(const t_vec3 ray_origin, const t_vec3 ray_direction,
		const t_triangle triangle, t_hit *hit)
{
	t_vec3	edge1;
	t_vec3	edge2;
	t_vec3	h;
	t_vec3	s;
	t_vec3	q;
	float	a;
	float	f;
	float	u;
	float	v;
	float	t;

	edge1 = sub_vec3s(triangle.v1, triangle.v0);
	edge2 = sub_vec3s(triangle.v2, triangle.v0);
	h = cross_product(ray_direction, edge2);
	a = dot_vec3s(edge1, h);
	if (-FLT_EPSILON > a && a < FLT_EPSILON)
		return (false); // This ray is parallel to this triangle.
	f = 1.0 / a;
	s = sub_vec3s(ray_origin, triangle.v0);
	u = f * dot_vec3s(s, h);
	if (u < 0.0 || u > 1.0)
		return (false);
	q = cross_product(s, edge1);
	v = f * dot_vec3s(ray_direction, q);
	// printf("v: %f - u+v: %f\n", v, u + v);
	if (v < 0.0 || u + v > 1.0)
		return (false);
	// At this stage we can compute t to find out where the intersection point is on the line.
	t = f * dot_vec3s(edge2, q);
	// printf("t: %f\n", t);
	if (t > FLT_EPSILON) // ray intersection
	{
		hit->distance = t;
		hit->point = add_vec3s(ray_origin, mult_vec3_scalar(ray_direction, t));
		hit->normal = norm_vec3(cross_product(edge1, edge2));
		// assuming non-degenerate triangle
		hit->color = triangle.color;
		return (true);
	}
	else
		// This means that there is a line intersection but not a ray intersection.
		return (false);
}

bool	check_triangles_intersection(const t_vec3 ray_origin,
		const t_vec3 ray_direction, t_hit *closest_hit, float *closest_so_far,
		t_uniforms *u)
{
	t_hit		h;
	bool		has_hit;
	int			num_triangles;
	int			i;
	t_triangle	scene_triangles[] = {{vec4_to_vec3(mult_mat4_vec4(u->mvp_mat,
					(t_vec4){-0.5, 0, -0.5, 1})),
			vec4_to_vec3(mult_mat4_vec4(u->mvp_mat, (t_vec4){0.5, 0, -0.5, 1})),
			vec4_to_vec3(mult_mat4_vec4(u->mvp_mat, (t_vec4){0.5, 0, 0.5, 1})),
			{1.0, 0, 0}, MATERIAL_LAMBERTIAN},
			{vec4_to_vec3(mult_mat4_vec4(u->mvp_mat, (t_vec4){-0.5, 0, -0.5,
					1})), vec4_to_vec3(mult_mat4_vec4(u->mvp_mat, (t_vec4){-0.5,
					0, 0.5, 1})), vec4_to_vec3(mult_mat4_vec4(u->mvp_mat,
					(t_vec4){0.5, 0, 0.5, 1})), {0, 1.0, 0},
			MATERIAL_LAMBERTIAN}};

	has_hit = false;
	num_triangles = sizeof(scene_triangles) / sizeof(t_triangle);
	for (i = 0; i < num_triangles; i++)
	{
		if (intersect_triangle(ray_origin, ray_direction, scene_triangles[i],
				&h))
		{
			if (h.distance < *closest_so_far)
			{
				*closest_so_far = h.distance;
				*closest_hit = h;
				has_hit = true;
			}
		}
	}
	return (has_hit);
}
