/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:55:13 by agaley            #+#    #+#             */
/*   Updated: 2024/03/09 17:10:28 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	is_vec3_normalized(t_vec3 vec)
{
	float	magnitude;

	magnitude = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (fabs(magnitude - 1.0) < 0.001);
}
