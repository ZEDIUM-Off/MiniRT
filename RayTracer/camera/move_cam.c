/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:42:38 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/20 12:52:27 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	cam_rotate(t_rt *rt, float delta_x, float delta_y)
{
	t_cam	*cam;
	float	yaw;
	float	pitch;
	t_vec3	cam2target;
	t_vec3	pos2origin;

	cam = (t_cam *)&rt->cam;
	yaw = cam->speed * delta_x / 5;
	pitch = cam->speed * delta_y / 5;
	cam2target = sub_vec3s(cam->target, cam->pos);
	cam->dir = norm_vec3(cam2target);
	cam->dir = vec3_rotate(cam->dir, pitch, cam->right);
	cam->dir = vec3_rotate(cam->dir, yaw, (t_vec3){0, 1, 0});
	pos2origin = sub_vec3s(cam->pos, cam->target);
	pos2origin = vec3_rotate(pos2origin, yaw, (t_vec3){0, 1, 0});
	pos2origin = vec3_rotate(pos2origin, pitch, cam->right);
	cam->pos = add_vec3s(pos2origin, cam->target);
	cam->right = norm_vec3(cross_product(cam->dir, (t_vec3){0, 1, 0}));
	cam->up = cross_product(cam->right, cam->dir);
}

void	cam_translate(t_rt *rt, int x_offset, int y_offset)
{
	t_cam	*cam;
	t_vec3	translation;

	cam = &rt->cam;
	translation = add_vec3s(scale_vec3s(norm_vec3(cam->right), -x_offset
				* cam->speed * 2), scale_vec3s(norm_vec3(cam->up), y_offset
				* cam->speed * 2));
	cam->pos = add_vec3s(cam->pos, translation);
	cam->target = add_vec3s(cam->target, translation);
}

void	cam_zoom(t_rt *rt, int zoom)
{
	t_cam	*cam;
	t_vec3	translation;

	cam = &rt->cam;
	translation = scale_vec3s(cam->dir, zoom * 2);
	cam->pos = add_vec3s(cam->pos, translation);
	cam->target = add_vec3s(cam->target, translation);
}

void	print_cam_properties(t_rt *rt)
{
	t_cam	*cam;

	cam = &rt->cam;
	printf("Camera:\nC ");
	printf("%f,%f,%f", cam->pos.x, cam->pos.y, cam->pos.z);
	printf(" ");
	printf("%f,%f,%f", cam->dir.x, cam->dir.y, cam->dir.z);
	printf(" %f\n", cam->fov);
}
