/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_ctrl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:48:15 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/20 11:47:38 by mchenava         ###   ########.fr       */
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
		switch_checkerboard(rt);
	if (key == XK_s)
		switch_soft_shadow(rt);
	if (key == XK_b)
		switch_bumpmap_mode(rt);
	if (key == XK_m)
		switch_mandatory(rt);
	return (0);
}
