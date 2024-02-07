/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_glx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:17:58 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/07 13:25:44 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_uint	setup_gl_context(t_rt *rt)
{
	t_mlx_env			*mxv;
	t_gl_context		*c;
	t_context_settings	settings;

	mxv = &rt->mxv;
	c = &rt->glx;
	settings.back = (t_u32 **)&mxv->img->data;
	settings.w = WIDTH;
	settings.h = HEIGHT;
	settings.bitdepth = 32;
	settings.r_mask = RED_MASK;
	settings.g_mask = GREEN_MASK;
	settings.b_mask = BLUE_MASK;
	settings.a_mask = ALPHA_MASK;
	if (!init_gl_context(c, settings))
		return (GLX_INIT_ERR);
	gl_clear_color(c, BLACK_VEC);
	gl_enable(&fdf->glx, GL_DEPTH_TEST);
	return (CONTINUE);
}
