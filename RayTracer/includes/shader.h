/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:43:04 by agaley            #+#    #+#             */
/*   Updated: 2024/03/09 01:40:50 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# include "materials.h"
# include <stdlib.h>

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

# define SHADOW_BIAS 1e-3

typedef struct s_ray	t_ray;
typedef struct s_shape	t_shape;
typedef struct s_hit	t_hit;

typedef struct s_fresnel
{
	float				cosi;
	float				etai;
	float				etat;
	float				sint;
	float				cost;
	float				rs;
	float				rp;
}						t_fresnel;

typedef struct s_triangle
{
	t_vec3				v0;
	t_vec3				v1;
	t_vec3				v2;
	t_color				color;
	t_material			material;
}						t_triangle;

struct					s_hit
{
	// t_material	material;
	t_color				color;
	t_vec3				point;
	t_vec3				normal;
	float				distance;
};

t_vec3					reflect_vector(t_vec3 incident, t_vec3 normal);
t_color					mix_color(t_color color1, t_color color2, float ratio);

float					fresnel_effect(t_vec3 incident, t_vec3 normal,
							float refraction_index);
float					schlick_approx(float cosine, float ref_index);

// Intersections

typedef bool			(*t_intersect_func)(t_ray *, t_shape *, t_hit *);

bool					check_shapes_intersection(t_ray *ray,
							t_hit *closest_hit, float *closest_so_far,
							t_rt *rt);

bool					intersect_plane(t_ray *ray, t_shape *plane, t_hit *hit);
bool					intersect_sphere(t_ray *ray, t_shape *sphere,
							t_hit *hit);
bool					intersect_cylinder(t_ray *ray, t_shape *cy, t_hit *hit);
bool					intersect_cone(t_ray *ray, t_shape *cone, t_hit *hit);
bool					intersect_scene(t_ray *ray, t_hit *hit, t_uniforms *u);

// Color utils
t_color					blend_colors(t_color c1, t_color c2);
t_color					mult_color_scalar(t_color c, float s);
t_color					mult_colors(t_color c1, t_color c2);
t_vec4					mult_color_vec4_scalar(t_vec4 c, float s);
t_vec4					add_colors_vec4(t_vec4 c1, t_vec4 c2);

// Main ray tracing
t_color					trace_ray(t_ray *ray, size_t depth, t_uniforms *u);
void					rt_frag_shader(float *fs_input,
							t_shader_builtins *builtins, void *uni);

#endif
