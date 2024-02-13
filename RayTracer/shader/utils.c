/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:45:23 by agaley            #+#    #+#             */
/*   Updated: 2024/02/13 06:40:15 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3 reflect_vector(t_vec3 incident, t_vec3 normal) {
    float   dot;
    t_vec3  result;

    dot = dot_vec3s(normal, incident);
    result.x = incident.x - 2.0 * dot * normal.x;
    result.y = incident.y - 2.0 * dot * normal.y;
    result.z = incident.z - 2.0 * dot * normal.z;
    return result;
}

t_vec3 mix_color(t_vec3 color1, t_vec3 color2, float ratio) {
    t_vec3  mixedColor;

    mixedColor.x = color1.x * (1 - ratio) + color2.x * ratio;
    mixedColor.y = color1.y * (1 - ratio) + color2.y * ratio;
    mixedColor.z = color1.z * (1 - ratio) + color2.z * ratio;
    return mixedColor;
}
