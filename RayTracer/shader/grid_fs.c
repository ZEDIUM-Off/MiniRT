/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_fs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:11:53 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/14 16:41:46 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec4	grid_shading(t_vec3 point, bool is_axis)
{
	t_vec4	color;

	if (-1 < point.x && point.x < 0.1 && is_axis)
		color = (t_vec4){0.427, 0.792, 0.909, 0.5};
	if (-1 < point.z && point.z < 0.1 && is_axis)
		color = (t_vec4){0.984, 0.380, 0.490, 0.5};
	return (color);
}

float	compute_depth(t_vec3 point, t_uniforms *u)
{
	t_vec4	clip;
	float	depth;
	t_mat4	temp;

	mult_mat4_mat4(temp, u->proj, u->view);
	clip = mult_mat4_vec4(temp, (t_vec4){point.x, point.y, point.z, 1});
	depth = clip.z / clip.w;
	return ((((clampf_01(1000) - clampf_01(0.1)) * depth) + clampf_01(0.1)
			+ clampf_01(1000)) / 2);
}

float	compute_fade(t_vec3 point, t_uniforms *u)
{
	t_vec4	clip;
	float	depth;
	float	linear_depth;
	t_mat4	temp;

	mult_mat4_mat4(temp, u->proj, u->view);
	clip = mult_mat4_vec4(temp, (t_vec4){point.x, point.y, point.z, 1});
	depth = (clip.z / clip.w);
	linear_depth = (2 * 0.1 * 1000) / (1000 + 0.1 - depth * (1000 - 0.1));
	return (linear_depth / 1000);
}

void	grid_fs(float *fs_input, t_shader_builtins *builtins, void *uniforms)
{
	float		c;
	float		t;
	t_uniforms	*u;
	t_vec4		color;
	t_vec3		r;

	// t_vec3		point;
	u = (t_uniforms *)uniforms;
	(void)fs_input;
	// point = (t_vec3){fs_input[0], fs_input[1], fs_input[2]};
	t = (-u->near_point.y) / (u->far_point.y - u->near_point.y);
	r = add_vec3s(u->near_point, scale_vec3s(sub_vec3s(u->far_point,
					u->near_point), t));
	c = ((int)(round(r.x * 5.0)) + (int)(round(r.y * 5.0))) % 2;
	color = (t_vec4){c / 2.0 + 0.3, c / 2.0 + 0.3, c / 2.0 + 0.3, 1};
	builtins->gl_frag_color = scale_vec4s(color, (float)(t > 0));
}
