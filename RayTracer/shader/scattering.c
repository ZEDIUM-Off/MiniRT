/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scattering.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:51:04 by agaley            #+#    #+#             */
/*   Updated: 2024/03/19 15:50:05 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

float	fresnel_effect(t_vec3 incident, t_hit *hit)
{
	t_fresnel	f;
	t_vec2		swp;

	f.cosi = clamp(-1.0, 1.0, dot_vec3s(incident, hit->normal));
	f.etai = 1.0;
	f.etat = 1.0;
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
float	schlick_approx(t_vec3 incident, t_hit *hit)
{
	float	r0;
	float	cosine;

	cosine = dot_vec3s(incident, hit->normal);
	r0 = (1.0 - hit->material.refraction_index) / (1.0
			+ hit->material.refraction_index);
	r0 = r0 * r0;
	return (r0 + (1.0 - r0) * powf((1.0 - fabs(cosine)), 5.0));
}
