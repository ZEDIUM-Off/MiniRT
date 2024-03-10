/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_lighting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:48:21 by agaley            #+#    #+#             */
/*   Updated: 2024/03/10 23:05:54 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_spot_color(t_hit *hit, t_uniforms *u)
{
	t_vec3	light_dir;
	float	light_distance;
	float	dot_nl;
	float	attenuation;
	t_color	spot_light_color;

	spot_light_color = (t_color){0, 0, 0, 255};
	light_dir = sub_vec3s(u->rt->sc_input.s_lights[0].position, hit->point);
	normalize_vec3(&light_dir);
	dot_nl = dot_vec3s(hit->normal, light_dir);
	if (dot_nl > 0)
	{
		light_distance = vec3_lenght(light_dir);
		attenuation = 1.0 / (light_distance * light_distance);
		spot_light_color = mult_color_scalar(u->rt->sc_input.s_lights[0].color,
				u->rt->sc_input.s_lights[0].brightness_ratio * dot_nl
				* attenuation);
	}
	return (spot_light_color);
}

t_color	calculate_specular(t_hit *hit, t_uniforms *u, t_vec3 light_dir)
{
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	float	spec;
	t_color	specular_color;

	float specular_strength = 0.5; // Dans les materials quand implémentés
	int shininess = 32;            // Pareil, sinon, à définir comme prop de rt
	view_dir = sub_vec3s(u->rt->cam.pos, hit->point);
	normalize_vec3(&view_dir);
	reflect_dir = reflect_vector(sub_vec3s((t_vec3){0, 0, 0}, light_dir),
			hit->normal);
	normalize_vec3(&reflect_dir);
	spec = pow(fmax(dot_vec3s(view_dir, reflect_dir), 0.0), shininess);
	specular_color = mult_color_scalar(u->rt->sc_input.s_lights[0].color,
			specular_strength * spec);
	return (specular_color);
}

t_color	get_checkerboard_color(t_hit *hit, t_uniforms *u)
{
	int		pattern;
	float	scale;

	scale = u->rt->checker_scale;
	pattern = (int)(floor(hit->point.x / scale) + floor(hit->point.z / scale))
		% 2;
	if (pattern == 0)
		return (hit->color);
	else
		return (COLOR_BLACK);
}

t_color	calculate_lighting(t_hit *hit, t_uniforms *u, float light_distance)
{
	t_color	color;
	t_vec3	light_dir;
	t_ray	shadow_ray;
	t_hit	shadow_hit;

	color = mult_color_scalar(u->rt->sc_input.a_light.color,
			u->rt->sc_input.a_light.ratio);
	if (u->rt->sc_input.s_lights_count == 0)
		return (color);
	if (u->rt->checker_mode && u->rt->checker_scale > 0)
		hit->color = get_checkerboard_color(hit, u);
	light_dir = sub_vec3s(u->rt->sc_input.s_lights[0].position, hit->point);
	normalize_vec3(&light_dir);
	shadow_ray = (t_ray){add_vec3s(hit->point, scale_vec3s(hit->normal,
				SHADOW_BIAS)), light_dir};
	shadow_hit = (t_hit){0};
	if (!intersect_scene(&shadow_ray, &shadow_hit, u)
		|| shadow_hit.distance > light_distance)
	{
		color = blend_colors(color, get_spot_color(hit, u));
		if (!u->rt->is_mandatory)
			color = blend_colors(color, calculate_specular(hit, u, light_dir));
	}
	return (color);
}
