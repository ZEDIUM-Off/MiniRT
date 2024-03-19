/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:28:29 by agaley            #+#    #+#             */
/*   Updated: 2024/03/19 12:09:18 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

typedef enum e_material_type
{
	MATERIAL_TYPE_LAMBERTIAN,
	MATERIAL_TYPE_GOLD,
}					t_material_type;

typedef struct s_material
{
	t_material_type	type;
	t_vec3			ambient;
	t_vec3			diffuse;
	t_vec3			specular;
	float			shininess;
	float			refraction_index;
}					t_material;

# define MATERIAL_LAMBERTIAN \
(t_material){MATERIAL_TYPE_LAMBERTIAN,(t_vec3){0.1, 0.1, 0.1},\
(t_vec3){0.7, 0.7, 0.7},(t_vec3){0.0, 0.0, 0.0},0.0, 0.0}

# define MATERIAL_GOLD \
(t_material){MATERIAL_TYPE_GOLD, (t_vec3){0.24725, 0.1995,0.0745},\
(t_vec3){0.75164, 0.60648, 0.22648},(t_vec3){0.628281,0.555802, 0.366065}\
, 0.4 * 128.0,0.47}

# define MATERIAL_GLASS \
(t_material){MATERIAL_TYPE_GLASS, (t_vec3){0.0, 0.0, 0.0}, \
(t_vec3){0.588235, 0.670588, 0.729412},(t_vec3){0.9,0.9, 0.9}\
, 0.25 * 128.0,1.52}

# define MATERIAL_SILVER \
(t_material){MATERIAL_TYPE_SILVER, (t_vec3){0.19225, 0.19225,0.19225}\
, (t_vec3){0.50754, 0.50754, 0.50754},(t_vec3){0.508273,0.508273, 0.508273}\
, 0.4 * 128.0,0.0}

#endif
