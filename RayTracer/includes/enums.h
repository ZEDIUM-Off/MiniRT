/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:10:25 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/07 14:14:35 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

enum e_rt_err
{
	CONTINUE,
	EXIT,
	MLX_INIT_ERR,
	GLX_INIT_ERR,
};

enum
{
	KEY_PRESSED_EVT = 02,
	KEY_RELEASED_EVT = 03,
	BUTTON_PRESSED_EVT = 04,
	BUTTON_RELEASED_EVT = 05,
	MOUSE_MOVE_EVT = 06,
	DESTROY_NOTIFY_EVT = 17,
};

enum
{
	KEY_PRESSED_MASK = (1L << 0),
	KEY_RELEASED_MASK = (1L << 1),
	BUTTON_PRESSED_MASK = (1L << 2),
	BUTTON_RELEASED_MASK = (1L << 3),
	MOUSE_MOVE_MASK = (1L << 6),
};

enum
{
	LEFT_CLICK = 1,
	RIGHT_CLICK = 3,
	MIDDLE_CLICK = 2,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5,
};

#endif //ENUMS_H