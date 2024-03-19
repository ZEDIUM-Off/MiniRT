/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_ctrl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:48:15 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/19 18:44:42 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	key_pressed(int key, t_rt *rt)
{
	if (key == XK_Escape)
		quit_rt(rt);
	if (key == XK_r)
		switch_mode(rt);
	if (key == XK_c)
		print_cam_properties(rt);
	if (key == XK_e)
		editor_menu(rt);
	if (key == XK_s)
		rt->soft_shadows = !rt->soft_shadows;
	if (key == XK_b)
		change_bumpmap_mode(rt);
	return (0);
}
