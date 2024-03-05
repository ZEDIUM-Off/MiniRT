/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_vs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:08:11 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/14 16:38:49 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	unproject_point(t_vec3 point, t_mat4 mat)
{
	t_mat4	inv;
	t_vec4	unprojected;

	mat4_inverse(inv, mat);
	unprojected = mult_mat4_vec4(inv, (t_vec4){point.x, point.y, point.z, 1});
	return (scale_vec3s((t_vec3){unprojected.x, unprojected.y, unprojected.z},
		1 / unprojected.w));
}

void	grid_vs(float *vs_output, void *vertex_attribs,
	t_shader_builtins *builtins, void *uniforms)
{
	t_uniforms	*u;
	t_vec2		*pos;
	t_vec3		point;

	u = (t_uniforms *)uniforms;
	pos = (t_vec2 *)vertex_attribs;
	u->near_point = unproject_point((t_vec3){pos->x, pos->y, -1}, u->mvp_mat);
	u->far_point = unproject_point((t_vec3){pos->x, pos->y, 1}, u->mvp_mat);
	// builtins->gl_position = mult_mat4_vec4(u->mvp_mat, (t_vec4){pos->x, pos->y, 0, 1});
	builtins->gl_position = (t_vec4){pos->x, pos->y, 0, 1};
	point = (t_vec3){pos->x, pos->y, 0};
	vs_output[0] = point.x;
	vs_output[1] = point.y;
	vs_output[2] = point.z;
}
