/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:03:20 by agaley            #+#    #+#             */
/*   Updated: 2024/03/19 13:50:26 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_vec3	calculate_ray_direction(t_cam *cam, float aspect_ratio, float scale,
		t_shader_builtins *builtins)
{
	t_vec3	ray_dir;
	t_vec2	pixel_ndc;
	t_vec2	pixel_screen;
	t_vec2	pixel_camera;

	pixel_ndc.x = (builtins->gl_frag_coord.x + 0.5) / WIDTH;
	pixel_ndc.y = (builtins->gl_frag_coord.y + 0.5) / HEIGHT;
	pixel_screen.x = 2 * pixel_ndc.x - 1;
	pixel_screen.y = 2 * pixel_ndc.y - 1;
	pixel_camera.x = pixel_screen.x * aspect_ratio * scale;
	pixel_camera.y = pixel_screen.y * scale;
	ray_dir = add_vec3s(add_vec3s(cam->dir, scale_vec3s(cam->right,
					pixel_camera.x)), scale_vec3s(cam->up, pixel_camera.y));
	normalize_vec3(&ray_dir);
	return (ray_dir);
}

void	rt_frag_shader(float *fs_input, t_shader_builtins *builtins, void *uni)
{
	t_uniforms	*u;
	t_cam		*cam;
	t_ray		ray;
	float		scale;
	float		aspect_ratio;

	(void)fs_input;
	u = (t_uniforms *)uni;
	cam = &u->rt->cam;
	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	scale = tan(cam->fov * 0.5 * M_PI / 180);
	ray.ori = cam->pos;
	ray.dir = calculate_ray_direction(cam, aspect_ratio, scale, builtins);
	builtins->gl_frag_color = color_to_vec4(trace_ray(&ray, u->max_depth, u));
}
