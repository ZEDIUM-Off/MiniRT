/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:03:20 by agaley            #+#    #+#             */
/*   Updated: 2024/03/10 21:19:49 by agaley           ###   ########lyon.fr   */
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

t_color	calculate_reflection(t_ray *ray, t_hit *hit, size_t depth,
		t_uniforms *u)
{
	t_ray	reflected_ray;
	t_vec3	reflect_dir;
	t_color	reflect_color;

	reflect_dir = reflect_vector(ray->dir, hit->normal);
	reflected_ray = (t_ray){hit->point, reflect_dir};
	reflect_color = trace_ray(&reflected_ray, depth - 1, u);
	return (reflect_color);
}

t_color	trace_ray(t_ray *ray, size_t depth, t_uniforms *u)
{
	t_hit	hit;
	float	light_dist;
	float	reflectance;
	t_color	color;
	t_color	reflect_color;

	if (depth == 0)
		return (u->rt->sc_input.a_light.color);
	hit = (t_hit){0};
	if (!intersect_scene(ray, &hit, u))
		return (COLOR_BG);
	if (u->rt->sc_input.s_lights_count != 0)
		light_dist = vec3_lenght(sub_vec3s(u->rt->sc_input.s_lights[0].position,
					hit.point));
	color = calculate_lighting(&hit, u, light_dist);
	color = mult_colors(color, hit.color);
	if (depth > 1)
	{
		reflect_color = calculate_reflection(ray, &hit, depth, u);
		reflectance = fresnel_effect(ray->dir, hit.normal, 1);
		color = mix_color(color, reflect_color, reflectance);
	}
	return (color);
}

void	rt_frag_shader(float *fs_input, t_shader_builtins *builtins, void *uni)
{
	t_uniforms	*uniforms;
	t_cam		*cam;
	t_ray		ray;
	float		scale;
	t_vec2		pixel_ndc;
	t_vec2		pixel_screen;
	t_vec2		pixel_camera;
	t_vec3		ray_dir;
	float		aspect_ratio;
	t_color		color;

	(void)fs_input;
	uniforms = (t_uniforms *)uni;
	cam = &uniforms->rt->cam;
	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	scale = tan(cam->fov * 0.5 * 3.1416 / 180);
	pixel_ndc.x = (builtins->gl_frag_coord.x + 0.5) / WIDTH;
	pixel_ndc.y = (builtins->gl_frag_coord.y + 0.5) / HEIGHT;
	pixel_screen.x = 2 * pixel_ndc.x - 1;
	pixel_screen.y = 2 * pixel_ndc.y - 1;
	pixel_camera.x = pixel_screen.x * aspect_ratio * scale;
	pixel_camera.y = pixel_screen.y * scale;
	ray_dir = add_vec3s(add_vec3s(cam->dir, scale_vec3s(cam->right,
					pixel_camera.x)), scale_vec3s(cam->up, pixel_camera.y));
	normalize_vec3(&ray_dir);
	ray.ori = cam->pos;
	ray.dir = ray_dir;
	color = trace_ray(&ray, uniforms->max_depth, uniforms);
	// printf("pix_x %f - pix_y %f : r: %d, g: %d, b: %d\n", pixel_screen.x,
	// 	pixel_screen.y, color.r, color.g, color.b);
	builtins->gl_frag_color = color_to_vec4(color);
}
