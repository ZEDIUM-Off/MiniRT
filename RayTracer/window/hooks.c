/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:13:25 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/06 15:06:41 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	set_mouse_hooks(t_rt *rt)
{
	mlx_hook(rt->mxv.win, BUTTON_PRESSED_EVT, BUTTON_PRESSED_MASK,
		mouse_pressed, rt);
	mlx_hook(rt->mxv.win, BUTTON_RELEASED_EVT, BUTTON_RELEASED_MASK,
		mouse_released, rt);
	mlx_hook(rt->mxv.win, MOUSE_MOVE_EVT, MOUSE_MOVE_MASK, mouse_move, rt);
	mlx_hook(rt->mxv.win, DESTROY_NOTIFY_EVT, 0, quit_rt, rt);
}

void	set_keyboard_hooks(t_rt *rt)
{
	mlx_hook(rt->mxv.win, KEY_PRESSED_EVT, KEY_PRESSED_MASK, key_pressed, rt);
}

void	set_hooks(t_rt *rt)
{
	set_mouse_hooks(rt);
	set_keyboard_hooks(rt);
	mlx_loop_hook(rt->mxv.mlx, render, rt);
}
