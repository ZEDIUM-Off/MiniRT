/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_ctrl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:48:15 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/20 00:34:53 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	key_pressed(int key, t_rt *rt)
{
	if (key == XK_Escape)
		quit_rt(rt);
	if (key == XK_r)
		switch_mode(rt);
	if (key == XK_p)
		print_cam_properties(rt);
	if (key == XK_e)
		editor_menu(rt);
	if (key == XK_c)
	{
		rt->checker_mode = !rt->checker_mode;
		if (rt->mode == MODE_RENDER)
			render_raytraced(rt, true);
	}
	if (key == XK_s)
	{
		rt->soft_shadow = !rt->soft_shadow;
		if (rt->mode == MODE_RENDER)
			render_raytraced(rt, true);
	}
	if (key == XK_b)
		switch_bumpmap_mode(rt);
	return (0);
}
