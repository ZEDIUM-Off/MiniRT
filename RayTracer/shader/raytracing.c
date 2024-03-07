/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:03:20 by agaley            #+#    #+#             */
/*   Updated: 2024/03/07 03:50:34 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_color	mult_color_scalar(t_color c, float s)
{
	return ((t_color){c.r * s, c.g * s, c.b * s, c.a});
}

t_color	add_colors(t_color c1, t_color c2)
{
	float	avg_a;

	avg_a = (c1.a + c2.a) / 2.0f;
	return ((t_color){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, avg_a});
}

static t_color	calculate_reflection(t_color color, t_hit hit, t_ray *ray,
		int depth, t_uniforms *u)
{
	t_ray	reflected_ray;
	t_color	reflect_color;
	float	reflectance;
	t_vec3	reflect_dir;

	if (depth > 1)
	{
		reflect_dir = reflect_vector(ray->dir, hit.normal);
		reflected_ray = (t_ray){hit.point, reflect_dir};
		reflect_color = trace_ray(&reflected_ray, depth - 1, u);
		reflectance = schlick_approx(dot_vec3s(ray->dir, hit.normal), 1);
		color = mix_color(color, reflect_color, reflectance);
	}
	return (color);
}

static t_color	calculate_lighting(t_hit hit, t_uniforms *u, t_ray *ray,
		int depth)
{
	t_color	color;
	t_color	spot_light_color;
	t_vec3	light_dir;
	float	light_distance;
	float	dot_nl;
	float	attenuation;

	spot_light_color = (t_color){0, 0, 0, 255};
	color = mult_color_scalar(u->rt->sc_input.a_light.color,
			u->rt->sc_input.a_light.ratio);
	light_dir = sub_vec3s(u->rt->sc_input.s_light.position, hit.point);
	normalize_vec3(&light_dir);
	dot_nl = dot_vec3s(hit.normal, light_dir);
	if (dot_nl > 0)
	{
		light_distance = vec3_lenght(light_dir);
		attenuation = 1.0 / (light_distance * light_distance);
		spot_light_color = mult_color_scalar(u->rt->sc_input.s_light.color,
				u->rt->sc_input.s_light.brightness_ratio * dot_nl
				* attenuation);
	}
	color = add_colors(color, spot_light_color);
	return (calculate_reflection(color, hit, ray, depth, u));
}

t_color	trace_ray(t_ray *ray, int depth, t_uniforms *u)
{
	t_hit	hit;

	if (depth <= 0)
		return (COLOR_BLACK);
	hit = (t_hit){0};
	if (intersect_scene(ray, &hit, u))
	{
		return (calculate_lighting(hit, u, ray, depth));
	}
	return (COLOR_BG);
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
	pixel_screen.y = 1 - 2 * pixel_ndc.y;
	pixel_camera.x = pixel_screen.x * aspect_ratio * scale;
	pixel_camera.y = pixel_screen.y * scale;
	ray_dir = add_vec3s(add_vec3s(mult_vec3_scalar(cam->dir, 1.0f),
				mult_vec3_scalar(cam->right, pixel_camera.x)),
			mult_vec3_scalar(cam->up, pixel_camera.y));
	normalize_vec3(&ray_dir);
	ray.ori = cam->pos;
	ray.dir = ray_dir;
	color = trace_ray(&ray, MAX_DEPTH, uniforms);
	builtins->gl_frag_color = color_to_vec4(color);
}
