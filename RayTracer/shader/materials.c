/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:45:17 by agaley            #+#    #+#             */
/*   Updated: 2024/02/20 16:46:27 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_material	material_set_gold(void)
{
	t_material	material_gold;

	material_gold.ambient = (t_vec3){0.24725, 0.1995, 0.0745};
	material_gold.diffuse = (t_vec3){0.75164, 0.60648, 0.22648};
	material_gold.specular = (t_vec3){0.628281, 0.555802, 0.366065};
	material_gold.shininess = 0.4 * 128.0;
	material_gold.refraction_index = 0.47;
	return (material_gold);
}
