/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:00:11 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/13 11:24:57 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	cam_proj(t_rt *rt, t_uniforms *u)
{
	t_cam	*cam;

	cam = (t_cam *)&rt->cam;
	make_perspective_matrix(u->proj,
		radians(cam->fov), WIDTH / HEIGHT, (float [2]){0.1, 100.0});
	look_at(u->view, cam->pos, cam->target, (t_vec3){0, 1, 0});
}
