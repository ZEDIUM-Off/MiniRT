/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:57:52 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/20 11:38:57 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	render(t_rt *rt)
{
	t_draw_elements_settings	settings;

	cam_proj(rt, &rt->uniforms);
	gl_clear(&rt->glx, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	settings = (t_draw_elements_settings){6, GL_UNSIGNED_INT, 0};
	gl_polygon_mode(&rt->glx, GL_FRONT_AND_BACK, GL_FILL);
	gl_draw_elements(&rt->glx, GL_TRIANGLES, &settings);
	mlx_put_image_to_window(rt->mxv.mlx, rt->mxv.win, rt->mxv.img, 0, 0);
	return (0);
}
