/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:27:52 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/07 10:38:51 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	switch_mode(t_rt *rt)
{
	if (rt->mode == MODE_RENDER)
		rt->mode = MODE_VIZ;
	else
		rt->mode = MODE_RENDER;
	gl_use_program(&rt->glx, rt->shaders[rt->mode]);
}
