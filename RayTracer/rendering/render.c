/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:57:52 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/06 14:44:18 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	render(t_rt *rt)
{
	rt->loop++;
	gl_polygon_mode(&rt->glx, GL_FRONT, GL_LINE);
	gl_polygon_mode(&rt->glx, GL_BACK, GL_LINE);
	if (rt->loop >= 100)
		new_frame(rt);
	return (0);
}

void	new_frame(t_rt *rt)
{
	cam_proj(rt, &rt->uniforms);
	gl_clear(&rt->glx, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mesh_draw(rt, &rt->scene.meshes[0]);
	mlx_put_image_to_window(rt->mxv.mlx, rt->mxv.win, rt->mxv.img, 0, 0);
	rt->loop = 0;
}
