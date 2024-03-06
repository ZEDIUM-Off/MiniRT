/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:03:20 by agaley            #+#    #+#             */
/*   Updated: 2024/03/06 06:42:10 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	trace_ray(const t_ray *ray, int depth, t_uniforms *u)
{
	t_hit	hit;
	t_vec3	reflect_dir;
	t_vec3	reflect_color;
	float	fresnel_effect;
	t_vec3	color;

	hit = (t_hit){0};
	reflect_dir = (t_vec3){0};
	reflect_color = (t_vec3){0};
	fresnel_effect = 0.0f;
	if (depth <= 0)
	{
		printf("black\n");
		return (COLOR_BLACK);
	}
	if (intersect_scene(ray, &hit, u))
	{
		printf("hit point: %f %f %f\n", hit.point.x, hit.point.y, hit.point.z);
		reflect_dir = reflect_vector(ray->dir, hit.normal);
		printf("reflect_dir: %f %f %f\n", reflect_dir.x, reflect_dir.y,
			reflect_dir.z);
		reflect_color = trace_ray(ray, depth - 1, u);
		printf("reflect_color: %f %f %f\n", reflect_color.x, reflect_color.y,
			reflect_color.z);
		fresnel_effect = schlick_approximation(dot_vec3s(ray->dir, hit.normal),
				hit.material.refraction_index);
		printf("fresnel_effect: %f\n", fresnel_effect);
		color = mix_color(hit.color, reflect_color, 0.1);
		printf("color before mix: %f %f %f\n", hit.color.x, hit.color.y,
			hit.color.z);
		printf("color after mix: %f %f %f\n", color.x, color.y, color.z);
		return (color);
	}
	return (COLOR_BG);
}

void	rt_frag_shader(float *fs_input, t_shader_builtins *builtins, void *uni)
{
	t_uniforms	*u;
	t_vec3		frag_coord;
	t_vec3		ray_direction;
	t_vec3		color;
	float		aspect_ratio;
	float		fov;
	float		vph;
	float		vpw;
	t_vec3		horizon;
	t_vec3		vertical;
	t_vec3		horizon_scaled;
	t_vec3		vertical_scaled;
	t_vec3		lowleft;
	t_ray		ray;

	u = NULL;
	frag_coord = (t_vec3){0};
	ray_direction = (t_vec3){0};
	color = (t_vec3){0};
	aspect_ratio = 0.0f;
	fov = 0.0f;
	(void)fs_input;
	u = (t_uniforms *)uni;
	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	fov = tanf(u->rt->cam.fov * (3.1416 / 180.0) / 2);
	// Convert FOV from degrees to radians and calculate tan
	printf("there is a fragment at %f %f\n", builtins->gl_frag_coord.x,
		builtins->gl_frag_coord.y);
	printf("there is a fragment at %f %f on screen space\n",
		builtins->gl_frag_coord.x / WIDTH, builtins->gl_frag_coord.y / HEIGHT);
	vph = 2 * fov;
	vpw = aspect_ratio * vph;
	horizon = scale_vec3s(u->rt->cam.dir, vpw);
	vertical = scale_vec3s(u->rt->cam.up, vph);
	horizon_scaled = scale_vec3s(horizon, builtins->gl_frag_coord.x / WIDTH);
	vertical_scaled = scale_vec3s(vertical, builtins->gl_frag_coord.y / HEIGHT);
	lowleft = sub_vec3s(sub_vec3s(sub_vec3s(u->rt->cam.pos, scale_vec3s(horizon,
						0.5)), scale_vec3s(vertical, 0.5)), u->rt->cam.dir);
	ray = (t_ray){add_vec3s(u->rt->cam.up, u->rt->cam.pos), add_vec3s(lowleft,
			add_vec3s(horizon_scaled, sub_vec3s(vertical_scaled,
					sub_vec3s(u->rt->cam.up, u->rt->cam.pos))))};
	// Calculate fragment's position in camera space
	frag_coord.x = ((builtins->gl_frag_coord.x) - 0.5) * aspect_ratio * fov;
	frag_coord.y = ((builtins->gl_frag_coord.y) - 0.5) * fov;
	printf("there is a fragment\n");
	frag_coord.z = -1.0;
	// Calculate ray direction from camera position to fragment position
	ray.dir = sub_vec3s(frag_coord, u->rt->cam.pos);
	ray.dir = norm_vec3(ray_direction); // Normalize the direction
	color = trace_ray(&ray, MAX_DEPTH, u);
	builtins->gl_frag_color = (t_vec4){color.x, color.y, color.z, 1.0f};
}
