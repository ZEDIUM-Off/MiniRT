/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:28:29 by agaley            #+#    #+#             */
/*   Updated: 2024/03/19 14:29:53 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

# define MATERIAL_LAMBERTIAN \
(t_material) \
{ \
	.type = MATERIAL_TYPE_LAMBERTIAN, \
	.ambient = (t_vec3){0.1, 0.1, 0.1}, \
	.diffuse = (t_vec3){0.7, 0.7, 0.7}, \
	.specular = (t_vec3){0.0, 0.0, 0.0}, \
	.shininess = 0.0, .refraction_index = 0.0 \
}

# define MATERIAL_GLASS \
(t_material) \
{ \
	.type = MATERIAL_TYPE_GLASS, \
	.ambient = (t_vec3){0.0, 0.0, 0.0}, \
	.diffuse = (t_vec3){0.588235, 0.670588, 0.729412}, \
	.specular = (t_vec3){0.9, 0.9, 0.9}, \
	.shininess = 0.25 * 128.0, .refraction_index = 1 \
}

# define MATERIAL_GOLD \
(t_material) \
{ \
	.type = MATERIAL_TYPE_GOLD, \
	.ambient = (t_vec3){0.24725, 0.1995, 0.0745}, \
	.diffuse = (t_vec3){0.75164, 0.60648, 0.22648}, \
	.specular = (t_vec3){0.628281, 0.555802, 0.366065}, \
	.shininess = 0.4 * 128.0, .refraction_index = 0.47 \
}

# define MATERIAL_SILVER  \
(t_material) \
{ \
	.type = MATERIAL_TYPE_SILVER, \
	.ambient = (t_vec3){0.19225, 0.19225, 0.19225}, \
	.diffuse = (t_vec3){0.50754, 0.50754, 0.50754}, \
	.specular = (t_vec3){0.508273, 0.508273, 0.508273}, \
	.shininess = 0.4 * 128.0, .refraction_index = 0.0 \
}

#endif
