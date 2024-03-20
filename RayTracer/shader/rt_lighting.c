/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_lighting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:48:21 by agaley            #+#    #+#             */
/*   Updated: 2024/03/20 03:35:17 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	get_spot_color(t_hit *hit, t_uniforms *u, t_s_light *light)
{
	float	dot_nl;
	float	attenuation;
	t_color	spot_light_color;

	spot_light_color = (t_color){0, 0, 0, 255};
	dot_nl = dot_vec3s(hit->normal, light->dir);
	if (dot_nl > 0)
	{
		light->distance = vec3_lenght(light->dir);
		attenuation = get_shadow(hit, u, light) / (light->distance
				* light->distance);
		spot_light_color = mult_color_scalar(light->color,
				light->brightness_ratio * dot_nl * attenuation);
	}
	return (spot_light_color);
}

static t_color	calculate_specular(t_hit *hit, t_uniforms *u, t_s_light *light)
{
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	float	spec;
	t_color	specular_color;

	view_dir = sub_vec3s(u->rt->cam.pos, hit->point);
	normalize_vec3(&view_dir);
	reflect_dir = reflect_vector(sub_vec3s((t_vec3){0, 0, 0}, light->dir),
			hit->normal);
	normalize_vec3(&reflect_dir);
	spec = pow(fmax(dot_vec3s(view_dir, reflect_dir), 0.0), SHININESS);
	specular_color = mult_color_scalar(u->rt->sc_input.s_lights[0].color,
			SPECULAR_STRENGTH * spec);
	return (specular_color);
}

static t_color	get_checkerboard_color(t_hit *hit, t_uniforms *u)
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

static t_color	init_lighting(t_hit *hit, t_uniforms *u)
{
	if (u->rt->bump_map_mode == ORANGE_PEEL)
		map_orange_peel(hit);
	if (u->rt->checker_mode && u->rt->checker_scale > 0)
		hit->color = get_checkerboard_color(hit, u);
	return (mult_color_scalar(u->rt->sc_input.a_light.color,
			u->rt->sc_input.a_light.ratio));
}

t_color	calculate_lighting(t_hit *hit, t_uniforms *u)
{
	t_hit		shadow_hit;
	size_t		i;
	t_color		color;
	t_s_light	*light;

	color = init_lighting(hit, u);
	i = 0;
	while (i < u->rt->sc_input.s_lights_count)
	{
		light = &u->rt->sc_input.s_lights[i++];
		light->dir = norm_vec3(sub_vec3s(light->position, hit->point));
		light->distance = vec3_lenght(sub_vec3s(light->position, hit->point));
		shadow_hit = (t_hit){0};
		if (u->rt->soft_shadow || (!u->rt->soft_shadow
				&& (!intersect_scene(&(t_ray){add_vec3s(hit->point,
							scale_vec3s(hit->normal, SHADOW_BIAS)), light->dir},
					&shadow_hit, u)
				|| shadow_hit.distance > light->distance)))
		{
			color = blend_colors(color, get_spot_color(hit, u, light));
			if (!u->rt->is_mandatory)
				color = blend_colors(color, calculate_specular(hit, u, light));
		}
	}
	return (color);
}
