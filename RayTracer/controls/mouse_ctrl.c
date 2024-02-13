/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:27:31 by  mchenava         #+#    #+#             */
/*   Updated: 2024/02/12 16:58:10 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	mouse_pressed(int btn, int x, int y, t_rt *rt)
{
	t_ctrl	*ctrl;
	t_cam	*cam;

	ctrl = (t_ctrl *)&rt->ctrl;
	cam = (t_cam *)&rt->cam;
	if (btn == LEFT_CLICK)
	{
		ctrl->rotate = true;
		ctrl->mouse_pos = (t_vec2){x, y};
	}
	if (btn == RIGHT_CLICK)
	{
		ctrl->translate = true;
		ctrl->mouse_pos = (t_vec2){x, y};
	}
	if (btn == SCROLL_UP)
		cam->fov -= 0.5;
	if (btn == SCROLL_DOWN)
		cam->fov += 0.5;
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
