/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:27:52 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/20 00:31:04 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	switch_bumpmap_mode(t_rt *rt)
{
	if (rt->bump_map_mode == NO_BUMP_MAP)
		rt->bump_map_mode = ORANGE_PEEL;
	else
		rt->bump_map_mode = NO_BUMP_MAP;
	if (rt->mode == MODE_RENDER)
		render_raytraced(rt, true);
}

void	switch_mode(t_rt *rt)
{
	if (rt->mode == MODE_RENDER)
		rt->mode = MODE_VIZ;
	else
		rt->mode = MODE_RENDER;
	gl_use_program(&rt->glx, rt->shaders[rt->mode]);
	lgl_set_uniform(&rt->glx, &rt->uniforms);
	if (rt->mode == MODE_RENDER)
		render_raytraced(rt, false);
}
