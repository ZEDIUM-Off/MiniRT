/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:32:36 by agaley            #+#    #+#             */
/*   Updated: 2024/03/20 03:32:52 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	map_orange_peel(t_hit *hit)
{
	t_vec2	wave;
	t_vec2	frequency;
	t_vec2	amplitude;

	frequency.x = 30.0 + (rand() % 15);
	amplitude.x = 0.15 + ((rand() % 10) / 50.0);
	frequency.y = 5.0 + (rand() % 3);
	amplitude.y = 0.20 + ((rand() % 15) / 100.0);
	wave.x = sin(hit->point.x * frequency.x) * cos(hit->point.z * frequency.x)
		* amplitude.x;
	wave.y = cos(hit->point.x * frequency.y) * sin(hit->point.z * frequency.y)
		* amplitude.y;
	hit->normal.x += wave.x + wave.y;
	hit->normal.z += wave.x + wave.y;
	normalize_vec3(&hit->normal);
}
