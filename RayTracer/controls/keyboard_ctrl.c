/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_ctrl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:48:15 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/11 18:29:17 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	key_pressed(int key, t_rt *rt)
{
	if (key == XK_Escape)
		quit_rt(rt);
	if (key == XK_r)
		switch_mode(rt);
	if (key == XK_s)
		print_cam_properties(rt);
	// if (key == XK_m)
	// 	use_material(rt);
	if (key == XK_e)
		editor_menu(rt);
	return (0);
}
