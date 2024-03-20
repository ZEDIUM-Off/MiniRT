/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:27:28 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/20 12:31:58 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	set_rt_vars(t_rt *rt)
{
	rt->ctrl.rotate = false;
	rt->ctrl.translate = false;
	rt->loop = 10000;
	rt->err_msg = NULL;
	rt->uniforms.max_depth = 3;
	rt->checker_mode = false;
	rt->checker_scale = 2;
	rt->bump_map_mode = NO_BUMP_MAP;
	rt->mesh_detail = MESH_DETAIL;
	rt->soft_shadow = false;
	rt->nb_samples = 30;
	rt->sqrt_samples = sqrt(rt->nb_samples);
	rt->sc_input.shapes_count = 0;
	rt->sc_input.shapes = NULL;
}

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
	rt->mode = MODE_VIZ;
	init_shader(rt);
	init_shapes(rt);
	set_rt_vars(rt);
	return (CONTINUE);
}
