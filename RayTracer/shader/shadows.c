/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:41:48 by agaley            #+#    #+#             */
/*   Updated: 2024/03/19 11:56:22 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Stratified Sampling

// t_vec3	calculate_sample_position(t_vec3 light_pos, int sample_index,
// 		int sqrt_samples, float angle_step, float radius_step)
// {
// 	int a, r;
// 	float azimuth, inclination, radius;
// 	float x, y, z;
// 	a = sample_index / sqrt_samples;
// 	// For azimuth
// 	r = sample_index % sqrt_samples;
// 	// For radius and inclination
// 	azimuth = a * angle_step + (rand() / (float)RAND_MAX) * angle_step;
// 	// Azimuthal angle
// 	inclination = M_PI * (r + (rand() / (float)RAND_MAX)) / sqrt_samples;
// 	// Polar angle, spread from 0 to PI for full sphere
// 	radius = radius_step;
// 	// Assuming constant radius for simplicity, can be adjusted if needed
// 	x = light_pos.x + radius * sin(inclination) * cos(azimuth);
// 	y = light_pos.y + radius * sin(inclination) * sin(azimuth);
// 	z = light_pos.z + radius * cos(inclination);
// 	// cos(inclination) for vertical spread
// 	return ((t_vec3){x, y, z});
// }

t_vec3	calculate_sample_position(t_vec3 light_pos, int sample_index,
		int sqrt_samples, float angle_step, float radius_step)
{
	int a, r;
	float azimuth, inclination, radius;
	float x, y, z;
	a = sample_index / sqrt_samples;
	// For azimuth
	r = sample_index % sqrt_samples;
	// For radius and inclination
	azimuth = a * angle_step + (rand() / (float)RAND_MAX) * angle_step;
	// Azimuthal angle
	inclination = M_PI * (r + (rand() / (float)RAND_MAX)) / sqrt_samples;
	// Polar angle, spread from 0 to PI for full sphere
	radius = radius_step;
	// Assuming constant radius for simplicity, can be adjusted if needed
	x = light_pos.x + radius * sin(inclination) * cos(azimuth);
	y = light_pos.y + radius * sin(inclination) * sin(azimuth);
	z = light_pos.z + radius * cos(inclination);
	// cos(inclination) for vertical spread
	return ((t_vec3){x, y, z});
}

float	get_soft_shadow(t_hit *hit, t_uniforms *u, t_vec3 light_pos,
		int num_samples, float light_radius)
{
	float	shadow;
	t_hit	shadow_hit;
	t_vec3	sample_pos;
	t_vec3	light_dir;
	float	angle_step;
	float	radius_step;
	int		sqrt_samples;

	shadow = 0.0;
	sqrt_samples = (int)sqrt(num_samples);
	// Assuming num_samples is a perfect square for simplicity
	angle_step = 2.0 * M_PI / sqrt_samples;
	radius_step = light_radius / sqrt_samples;
	for (int i = 0; i < num_samples; ++i)
	{
		sample_pos = calculate_sample_position(light_pos, i, sqrt_samples,
				angle_step, radius_step);
		light_dir = sub_vec3s(sample_pos, hit->point);
		normalize_vec3(&light_dir);
		shadow_hit = (t_hit){0};
		if (!intersect_scene(&(t_ray){add_vec3s(hit->point,
					scale_vec3s(hit->normal, SHADOW_BIAS)), light_dir},
				&shadow_hit, u)
			|| shadow_hit.distance > vec3_lenght(sub_vec3s(sample_pos,
					hit->point)))
		{
			shadow += 1.0;
		}
	}
	return (shadow / num_samples);
}

// static float	get_soft_shadow(t_hit *hit, t_uniforms *u, t_vec3 light_pos,
// 		int num_samples, float light_radius)
// {
// 	float	shadow;
// 	t_hit	shadow_hit;
// 	t_vec3	sample_pos;
// 	t_vec3	light_dir;
// 	int		i;

// 	shadow = 0.0;
// 	float angle, distance;
// 	for (i = 0; i < num_samples; ++i)
// 	{
// 		// Generate random angle and distance within the light radius
// 		angle = 2.0 * M_PI * (rand() / (float)RAND_MAX);
// 		distance = light_radius * sqrt(rand() / (float)RAND_MAX);
// 		// Calculate sample position on the light disc
// 		sample_pos.x = light_pos.x + distance * cos(angle);
// 		sample_pos.y = light_pos.y + distance * sin(angle);
// 		sample_pos.z = light_pos.z; // Assuming light source is flat
// 		light_dir = sub_vec3s(sample_pos, hit->point);
// 		normalize_vec3(&light_dir);
// 		shadow_hit = (t_hit){0};
// 		if (!intersect_scene(&(t_ray){add_vec3s(hit->point,
// 					scale_vec3s(hit->normal, SHADOW_BIAS)), light_dir},
// 				&shadow_hit, u)
// 			|| shadow_hit.distance > vec3_lenght(sub_vec3s(sample_pos,
// 					hit->point)))
// 			shadow += 1.0;
// 	}
// 	return (shadow / num_samples);
// }

float	get_shadow(t_hit *hit, t_uniforms *u, t_vec3 light_pos,
		float light_distance)
{
	t_hit	shadow_hit;
	t_vec3	light_dir;
	float	light_radius;
	int		num_samples;

	if (u->rt->soft_shadow)
	{
		num_samples = 50;
		light_radius = 7;
		return (get_soft_shadow(hit, u, light_pos, num_samples, light_radius));
	}
	shadow_hit = (t_hit){0};
	light_dir = sub_vec3s(light_pos, hit->point);
	normalize_vec3(&light_dir);
	if (!intersect_scene(&(t_ray){add_vec3s(hit->point, scale_vec3s(hit->normal,
					SHADOW_BIAS)), light_dir}, &shadow_hit, u)
		|| shadow_hit.distance > light_distance)
		return (1.0);
	return (0.0);
}
