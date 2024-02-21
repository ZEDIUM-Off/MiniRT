/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:28:29 by agaley            #+#    #+#             */
/*   Updated: 2024/02/21 15:31:50 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

# define MATERIAL_LAMBERTIAN (t_material){ \
    .ambient = (t_vec3){0.1, 0.1, 0.1}, \
    .diffuse = (t_vec3){0.7, 0.7, 0.7}, \
    .specular = (t_vec3){0.0, 0.0, 0.0}, \
    .shininess = 0.0, \
    .refraction_index = 0.0 \
}

# define MATERIAL_GOLD (t_material){ \
    .ambient = (t_vec3){0.24725, 0.1995, 0.0745}, \
    .diffuse = (t_vec3){0.75164, 0.60648, 0.22648}, \
    .specular = (t_vec3){0.628281, 0.555802, 0.366065}, \
    .shininess = 0.4 * 128.0, \
    .refraction_index = 0.47 \
}

#endif
