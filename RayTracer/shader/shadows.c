/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:41:48 by agaley            #+#    #+#             */
/*   Updated: 2024/03/20 02:21:52 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	calculate_sample_position(t_s_light *light, int sample_index,
		int sqrt_samples, t_vec2 steps)
{
	int		a;
	int		r;
	t_vec2	pol;
	t_vec3	pos;

	a = sample_index / sqrt_samples;
	r = sample_index % sqrt_samples;
	pol.x = a * steps.x + (rand() / (float)RAND_MAX) * steps.x;
	pol.y = M_PI * (r + (rand() / (float)RAND_MAX)) / sqrt_samples;
	pos.x = light->position.x + steps.y * sin(pol.y) * cos(pol.x);
	pos.y = light->position.y + steps.y * sin(pol.y) * sin(pol.x);
	pos.z = light->position.z + steps.y * cos(pol.y);
	return (pos);
}

static float	get_soft_shadow(t_hit *hit, t_uniforms *u, t_s_light *light)
{
	float	shadow;
	t_hit	shadow_hit;
	t_vec3	sample_pos;
	float	angle_step;
	size_t	i;

	i = u->rt->nb_samples;
	shadow = 0.0;
	angle_step = 2.0 * M_PI / u->rt->sqrt_samples;
	while (i--)
	{
		sample_pos = calculate_sample_position(light, i, u->rt->sqrt_samples,
				(t_vec2){angle_step, light->radius / u->rt->sqrt_samples});
		light->dir = sub_vec3s(sample_pos, hit->point);
		normalize_vec3(&light->dir);
		shadow_hit = (t_hit){0};
		if (!intersect_scene(&(t_ray){add_vec3s(hit->point,
					scale_vec3s(hit->normal, SHADOW_BIAS)), light->dir},
				&shadow_hit, u)
			|| shadow_hit.distance > vec3_lenght(sub_vec3s(sample_pos,
					hit->point)))
			shadow += 1.0;
	}
	return (shadow / u->rt->nb_samples);
}

float	get_shadow(t_hit *hit, t_uniforms *u, t_s_light *light)
{
	t_hit	shadow_hit;

	if (u->rt->soft_shadow)
		return (get_soft_shadow(hit, u, light));
	shadow_hit = (t_hit){0};
	light->dir = sub_vec3s(light->position, hit->point);
	normalize_vec3(&light->dir);
	if (!intersect_scene(&(t_ray){add_vec3s(hit->point, scale_vec3s(hit->normal,
					SHADOW_BIAS)), light->dir}, &shadow_hit, u)
		|| shadow_hit.distance > light->distance)
		return (1.0);
	return (0.0);
}
