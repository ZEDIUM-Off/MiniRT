/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:27:28 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 13:40:26 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_uint	init_rt(t_rt *rt)
{
	t_uint	status;

	rt->is_mandatory = MANDATORY;
	status = init_window(rt);
	if (status != CONTINUE)
		return (status);
	status = setup_gl_context(rt);
	if (status != CONTINUE)
		return (status);
	set_hooks(rt);
	rt->sc_input.shapes_count = 0;
	rt->sc_input.shapes = NULL;
	rt->mode = MODE_VIZ;
	init_shader(rt);
	init_shapes(rt);
	rt->ctrl.rotate = false;
	rt->ctrl.translate = false;
	rt->loop = 10000;
	rt->err_msg = NULL;
	rt->uniforms.max_depth = 3;
	rt->checker_mode = false;
	rt->checker_scale = 2;
	rt->bump_map_mode = NO_BUMP_MAP;
	return (CONTINUE);
}
