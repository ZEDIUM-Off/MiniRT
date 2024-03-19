/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:27:31 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/19 14:26:28 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	mouse_pressed(int btn, int x, int y, t_rt *rt)
{
	t_ctrl	*ctrl;

	ctrl = (t_ctrl *)&rt->ctrl;
	if (btn == LEFT_CLICK && rt->mode == MODE_VIZ)
	{
		ctrl->rotate = true;
		ctrl->mouse_pos = (t_vec2){x, y};
	}
	if (btn == RIGHT_CLICK && rt->mode == MODE_VIZ)
	{
		ctrl->translate = true;
		ctrl->mouse_pos = (t_vec2){x, y};
	}
	if (btn == SCROLL_UP && rt->mode == MODE_VIZ)
		cam_zoom(rt, 1);
	if (btn == SCROLL_DOWN && rt->mode == MODE_VIZ)
		cam_zoom(rt, -1);
	return (0);
}

int	mouse_released(int btn, int x, int y, t_rt *rt)
{
	t_ctrl	*ctrl;

	(void)x;
	(void)y;
	ctrl = (t_ctrl *)&rt->ctrl;
	if (btn == LEFT_CLICK)
		ctrl->rotate = false;
	if (btn == RIGHT_CLICK)
		ctrl->translate = false;
	return (0);
}

int	mouse_move(int x, int y, t_rt *rt)
{
	t_ctrl	*ctrl;

	ctrl = (t_ctrl *)&rt->ctrl;
	if (ctrl->rotate)
		cam_rotate(rt, x - ctrl->mouse_pos.x, y - ctrl->mouse_pos.y);
	if (ctrl->translate)
		cam_translate(rt, x - ctrl->mouse_pos.x, y - ctrl->mouse_pos.y);
	return (0);
}
