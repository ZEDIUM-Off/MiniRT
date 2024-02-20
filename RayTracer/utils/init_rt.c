/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:27:28 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/20 16:47:43 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_uint	init_rt(t_rt *rt)
{
	t_uint	status;

	printf("init RT...\n");
	status = init_window(rt);
	if (status != CONTINUE)
		return (status);
	printf("window inited\n");
	status = setup_gl_context(rt);
	if (status != CONTINUE)
		return (status);
	printf("gl inited\n");
	init_cam(rt);
	printf("cam inited\n");
	set_hooks(rt);
	printf("hooks inited\n");
	scene_init(rt);
	printf("grid inited\n");
	init_shader(rt);
	printf("shaders inited\n");
	rt->ctrl.rotate = false;
	rt->ctrl.translate = false;
	return (CONTINUE);
}
