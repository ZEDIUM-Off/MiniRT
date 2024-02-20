/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:03:20 by agaley            #+#    #+#             */
/*   Updated: 2024/02/20 16:09:11 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	trace_ray(t_vec3 origin, t_vec3 direction, int depth)
{
	t_hit	hit;
	t_vec3	reflect_dir;
	t_vec3	reflect_color;
	float	fresnel_effect;
	t_vec3	color;

	if (depth <= 0)
	{
		return (COLOR_BLACK);
	}
	if (intersect_scene(origin, direction, &hit))
	{
		reflect_dir = reflect_vector(direction, hit.normal);
		reflect_color = trace_ray(hit.point, reflect_dir, depth - 1);
		fresnel_effect = schlick_approximation(dot_vec3s(direction, hit.normal),
			hit.material.refraction_index);
		color = mix_color(hit.material.diffuse, reflect_color, fresnel_effect);
		return (color);
	}
	return (COLOR_BG);
}

void	rt_frag_shader(float *fs_input, t_shader_builtins *builtins, void *uni)
{
	t_vec3		color;
	t_uniforms	*u;

	(void)fs_input;
	u = (t_uniforms *)uni;
	color = trace_ray(u->cam->pos, norm_vec3(u->cam->dir), MAX_DEPTH);
	builtins->gl_frag_color = (t_vec4){color.x, color.y, color.z, 1.0};
}
