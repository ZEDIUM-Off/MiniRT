/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scattering.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:51:04 by agaley            #+#    #+#             */
/*   Updated: 2024/03/07 03:30:23 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

float	fresnel_effect(t_vec3 incident, t_vec3 normal, float refraction_index)
{
	t_fresnel	f;
	t_vec2		swp;

	f.cosi = clamp(-1.0, 1.0, dot_vec3s(incident, normal));
	f.etai = 1.0;
	f.etat = refraction_index;
	if (f.cosi > 0)
	{
		swp.x = f.etai;
		f.etai = f.etat;
		f.etat = swp.x;
	}
	f.sint = f.etai / f.etat * sqrtf(fmax(0.0, 1.0 - f.cosi * f.cosi));
	if (f.sint >= 1.0)
		return (1.0);
	else
	{
		f.cost = sqrtf(fmax(0.0, 1.0 - f.sint * f.sint));
		f.cosi = fabs(f.cosi);
		f.rs = ((f.etat * f.cosi) - (f.etai * f.cost)) / ((f.etat * f.cosi)
				+ (f.etai * f.cost));
		f.rp = ((f.etai * f.cosi) - (f.etat * f.cost)) / ((f.etai * f.cosi)
				+ (f.etat * f.cost));
		return ((f.rs * f.rs + f.rp * f.rp) / 2.0);
	}
}

// Schlick's approximation of the Fresnel effect
float	schlick_approx(float cosine, float ref_index)
{
	float	r0;

	r0 = (1.0 - ref_index) / (1.0 + ref_index);
	r0 = r0 * r0;
	return (r0 + (1.0 - r0) * powf((1.0 - fabs(cosine)), 5.0));
}
