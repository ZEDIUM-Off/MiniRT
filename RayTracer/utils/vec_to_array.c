/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:59:34 by  mchenava         #+#    #+#             */
/*   Updated: 2024/02/21 17:31:14 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	vec3_to_array(t_vec3* vec, float* arr, t_uint start)
{
	arr[start * 3] = vec->x;
	arr[start * 3 + 1] = vec->y;
	arr[start * 3 + 2] = vec->z;
}

void	ivec3_to_array(t_ivec3* vec, int* arr, t_uint start)
{
	arr[start * 3] = vec->x;
	arr[start * 3 + 1] = vec->y;
	arr[start * 3 + 2] = vec->z;
}

void	vec2_to_array(t_vec2* vec, float* arr, t_uint start)
{
	arr[start * 2] = vec->x;
	arr[start * 2 + 1] = vec->y;
}
