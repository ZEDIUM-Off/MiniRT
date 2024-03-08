/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:03:20 by agaley            #+#    #+#             */
/*   Updated: 2024/03/08 16:09:26 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_color	mult_color_scalar(t_color c, float s)
{
	return ((t_color){c.r * s, c.g * s, c.b * s, c.a});
}

t_vec4	mult_color_vec4_scalar(t_vec4 c, float s)
{
	return ((t_vec4){c.x * s, c.y * s, c.z * s, c.w});
}

t_color	mult_colors(t_color c1, t_color c2)
{
	float	avg_a;

	avg_a = (c1.a + c2.a) / 2.0f;
	return ((t_color){(c1.r * c2.r) / 255, (c1.g * c2.g) / 255, (c1.b * c2.b)
		/ 255, avg_a});
}

t_vec4	add_colors_vec4(t_vec4 c1, t_vec4 c2)
{
	float	avg_a;

	avg_a = (c1.w + c2.w) / 2.0f;
	return ((t_vec4){c1.x + c2.x, c1.y + c2.y, c1.z + c2.z, avg_a});
}

t_color	blend_colors(t_color c1, t_color c2)
{
	return ((t_color){fmin(c1.r + c2.r, 255), fmin(c1.g + c2.g, 255), fmin(c1.b
			+ c2.b, 255), (c1.a + c2.a) / 2.0f});
}

t_color	get_spot_color(t_hit *hit, t_uniforms *u)
{
	t_vec3	light_dir;
	float	light_distance;
	float	dot_nl;
	float	attenuation;
	t_color	spot_light_color;

	spot_light_color = (t_color){0, 0, 0, 255};
	light_dir = sub_vec3s(u->rt->sc_input.s_light.position, hit->point);
	normalize_vec3(&light_dir);
	dot_nl = dot_vec3s(hit->normal, light_dir);
	if (dot_nl > 0)
	{
		light_distance = vec3_lenght(light_dir);
		attenuation = 1.0 / (light_distance * light_distance);
		spot_light_color = mult_color_scalar(u->rt->sc_input.s_light.color,
				u->rt->sc_input.s_light.brightness_ratio * dot_nl
				* attenuation);
	}
	return (spot_light_color);
}

t_color	trace_ray(t_ray *ray, size_t depth, t_uniforms *u)
{
	t_hit	hit;
	t_ray	reflected_ray;
	float	reflectance;
	t_vec3	reflect_dir;
	t_color	color;
	t_color	reflect_color;

	if (depth == 0)
		return (u->rt->sc_input.a_light.color);
	hit = (t_hit){0};
	if (!intersect_scene(ray, &hit, u))
		return (COLOR_BG);
	color = mult_color_scalar(u->rt->sc_input.a_light.color,
			u->rt->sc_input.a_light.ratio);
	color = blend_colors(color, get_spot_color(&hit, u));
	color = mult_colors(color, hit.color);
	if (depth > 1)
	{
		reflect_dir = reflect_vector(ray->dir, hit.normal);
		reflected_ray = (t_ray){hit.point, reflect_dir};
		reflect_color = trace_ray(&reflected_ray, depth - 1, u);
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
	pixel_screen.y = 1 - 2 * pixel_ndc.y;
	pixel_camera.x = pixel_screen.x * aspect_ratio * scale;
	pixel_camera.y = pixel_screen.y * scale;
	ray_dir = add_vec3s(add_vec3s(mult_vec3_scalar(cam->dir, 1.0f),
				mult_vec3_scalar(cam->right, pixel_camera.x)),
			mult_vec3_scalar(cam->up, pixel_camera.y));
	normalize_vec3(&ray_dir);
	ray.ori = cam->pos;
	ray.dir = ray_dir;
	color = trace_ray(&ray, uniforms->max_depth, uniforms);
	// printf("pix_x %f - pix_y %f : r: %d, g: %d, b: %d\n", pixel_screen.x,
	// 	pixel_screen.y, color.r, color.g, color.b);
	builtins->gl_frag_color = color_to_vec4(color);
}
