/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scattering.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:51:04 by agaley            #+#    #+#             */
/*   Updated: 2024/02/13 06:26:07 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include <minirt.h>

float fresnel_effect(t_vec3 incident, t_vec3 normal, float refraction_index) {
    float cosi = clamp(-1.0, 1.0, dot_vec3s(incident, normal));
    float etai = 1.0, etat = refraction_index;
    if (cosi > 0) { 
        float temp = etai;
        etai = etat;
        etat = temp; 
    }
    // Snell's law
    float sint = etai / etat * sqrt(fmax(0.0, 1.0 - cosi * cosi));
    // Total internal reflection
    if (sint >= 1.0) {
        return 1.0;
    } else {
        float cost = sqrt(fmax(0.0, 1.0 - sint * sint));
        cosi = fabs(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        return (Rs * Rs + Rp * Rp) / 2.0;
    }
}

// Schlick's approximation of the Fresnel effect
float schlick_approximation(float cosine, float ref_index) {
    float r0 = (1.0 - ref_index) / (1.0 + ref_index);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * pow((1.0 - cosine), 5.0);
}