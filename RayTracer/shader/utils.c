/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:45:23 by agaley            #+#    #+#             */
/*   Updated: 2024/03/07 03:07:50 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	reflect_vector(t_vec3 incident, t_vec3 normal)
{
	float	dot;
	t_vec3	result;

	dot = dot_vec3s(normal, incident);
	result.x = incident.x - 2.0 * dot * normal.x;
	result.y = incident.y - 2.0 * dot * normal.y;
	result.z = incident.z - 2.0 * dot * normal.z;
	return (result);
}

t_color	mix_color(t_color color1, t_color color2, float ratio)
{
	t_color	color_mix;

	color_mix.r = color1.r * (1 - ratio) + color2.r * ratio;
	color_mix.g = color1.g * (1 - ratio) + color2.g * ratio;
	color_mix.b = color1.b * (1 - ratio) + color2.b * ratio;
	color_mix.a = (color1.a + color2.a) / 2;
	return (color_mix);
}
