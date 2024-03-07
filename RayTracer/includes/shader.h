/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:43:04 by agaley            #+#    #+#             */
/*   Updated: 2024/03/07 03:44:37 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# include "materials.h"
# include <stdlib.h>

# define MAX_DEPTH 100

# define COLOR_BLACK        \
	(t_color)              \
	{                      \
		0.0, 0.0, 0.0, 1.0 \
	}
# define COLOR_DGRAY        \
	(t_color)              \
	{                      \
		0.1, 0.1, 0.1, 1.0 \
	}

# define COLOR_BG COLOR_DGRAY

typedef struct s_fresnel
{
	float		cosi;
	float		etai;
	float		etat;
	float		sint;
	float		cost;
	float		rs;
	float		rp;
}				t_fresnel;

typedef struct s_triangle
{
	t_vec3		v0;
	t_vec3		v1;
	t_vec3		v2;
	t_color		color;
	t_material	material;
}				t_triangle;

typedef struct s_hit
{
	// t_material	material;
	t_color		color;
	t_vec3		point;
	t_vec3		normal;
	float		distance;
}				t_hit;

t_vec3			reflect_vector(t_vec3 incident, t_vec3 normal);
t_color			mix_color(t_color color1, t_color color2, float ratio);

float			fresnel_effect(t_vec3 incident, t_vec3 normal,
					float refraction_index);
float			schlick_approx(float cosine, float ref_index);

bool			check_planes_intersection(const t_ray *ray, t_hit *closest_hit,
					float *closest_so_far, t_rt *rt);

bool			check_spheres_intersection(const t_ray *ray, t_hit *closest_hit,
					float *closest_so_far, t_rt *rt);

bool			intersect_scene(const t_ray *ray, t_hit *hit, t_uniforms *u);

t_color			trace_ray(t_ray *ray, int depth, t_uniforms *u);

void			rt_frag_shader(float *fs_input, t_shader_builtins *builtins,
					void *uni);

#endif
