/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:27:52 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/20 01:55:12 by  mchenava        ###   ########.fr       */
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

void	switch_checkerboard(t_rt *rt)
{
	rt->checker_mode = !rt->checker_mode;
	if (rt->mode == MODE_RENDER)
		render_raytraced(rt, true);
}

void	switch_soft_shadow(t_rt *rt)
{
	rt->soft_shadow = !rt->soft_shadow;
	if (rt->mode == MODE_RENDER)
		render_raytraced(rt, true);
}

void	switch_mandatory(t_rt *rt)
{
	rt->is_mandatory = !rt->is_mandatory;
	if (rt->mode == MODE_RENDER)
			render_raytraced(rt, true);
}
