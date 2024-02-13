/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:01:30 by  mchenava         #+#    #+#             */
/*   Updated: 2024/02/13 11:21:08 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	init_cam(t_rt	*rt)
{
	t_cam	*cam;

	cam = (t_cam *)&rt->cam;
	cam->pos = (t_vec3){3.0, 3.0, 3.0};
	cam->target = (t_vec3){0.0, 0.0, 0.0};
	cam->dir = norm_vec3(sub_vec3s(cam->pos, cam->target));
	cam->right = norm_vec3(cross_product((t_vec3){0.0, 1.0, 0.0}, cam->dir));
	cam->up = cross_product(cam->dir, cam->right);
	cam->fov = 45.0f;
	cam->speed = 0.0005f;
}
