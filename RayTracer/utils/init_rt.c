/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:27:28 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/08 05:59:23 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_uint	init_rt(t_rt *rt)
{
	t_uint	status;

	status = init_window(rt);
	if (status != CONTINUE)
		return (status);
	status = setup_gl_context(rt);
	if (status != CONTINUE)
		return (status);
	init_cam(rt);
	set_hooks(rt);
	rt->sc_input.shapes_count = 0;
	rt->sc_input.shapes = NULL;
	rt->mode = MODE_VIZ;
	init_shader(rt);
	rt->ctrl.rotate = false;
	rt->ctrl.translate = false;
	rt->loop = 10000;
	rt->err_msg = NULL;
	rt->uniforms.max_depth = 3;
	return (CONTINUE);
}
