/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:57:52 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/07 18:03:39 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	new_frame(t_rt *rt)
{
	cam_proj(rt, &rt->uniforms);
	gl_clear(&rt->glx, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mesh_draw(rt, &rt->all_meshes);
	mlx_put_image_to_window(rt->mxv.mlx, rt->mxv.win, rt->mxv.img, 0, 0);
	rt->loop = 0;
}

void	vizualize(t_rt *rt)
{
	rt->loop++;
	gl_polygon_mode(&rt->glx, GL_FRONT, GL_FILL);
	gl_polygon_mode(&rt->glx, GL_BACK, GL_LINE);
	if (rt->loop >= 100)
		new_frame(rt);
}

void	render_raytraced(t_rt *rt)
{
	gl_clear(&rt->glx, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	lgl_draw_frame(&rt->glx);
	mlx_put_image_to_window(rt->mxv.mlx, rt->mxv.win, rt->mxv.img, 0, 0);
	while (rt->mode == MODE_RENDER)
		rt->loop++;
}

int	render(t_rt *rt)
{
	rt->loop++;
	if (rt->mode == MODE_RENDER)
		render_raytraced(rt);
	else
		vizualize(rt);
	return (0);
}
