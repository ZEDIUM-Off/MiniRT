/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 01:37:44 by agaley            #+#    #+#             */
/*   Updated: 2024/03/09 01:37:48 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_color	blend_colors(t_color c1, t_color c2)
{
	return ((t_color){fmin(c1.r + c2.r, 255), fmin(c1.g + c2.g, 255), fmin(c1.b
			+ c2.b, 255), (c1.a + c2.a) / 2.0f});
}

t_color	mult_color_scalar(t_color c, float s)
{
	return ((t_color){c.r * s, c.g * s, c.b * s, c.a});
}

t_color	mult_colors(t_color c1, t_color c2)
{
	float	avg_a;

	avg_a = (c1.a + c2.a) / 2.0f;
	return ((t_color){(c1.r * c2.r) / 255, (c1.g * c2.g) / 255, (c1.b * c2.b)
		/ 255, avg_a});
}

t_vec4	mult_color_vec4_scalar(t_vec4 c, float s)
{
	return ((t_vec4){c.x * s, c.y * s, c.z * s, c.w});
}

t_vec4	add_colors_vec4(t_vec4 c1, t_vec4 c2)
{
	float	avg_a;

	avg_a = (c1.w + c2.w) / 2.0f;
	return ((t_vec4){c1.x + c2.x, c1.y + c2.y, c1.z + c2.z, avg_a});
}
