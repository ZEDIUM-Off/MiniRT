/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:45:23 by agaley            #+#    #+#             */
/*   Updated: 2024/03/19 15:58:14 by agaley           ###   ########lyon.fr   */
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

void	associate_materials(t_rt *rt)
{
	size_t		i;
	t_material	materials[4];
	size_t		j;

	materials[0] = MATERIAL_LAMBERTIAN;
	materials[1] = MATERIAL_GLASS;
	materials[2] = MATERIAL_SILVER;
	materials[3] = MATERIAL_GOLD;
	i = 0;
	while (i < rt->sc_input.shapes_count)
	{
		j = rand() / (RAND_MAX / 4);
		rt->sc_input.shapes[i++].material = materials[j];
	}
}
