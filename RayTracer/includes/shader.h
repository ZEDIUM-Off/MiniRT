/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:43:04 by agaley            #+#    #+#             */
/*   Updated: 2024/03/20 12:44:48 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# include <stdlib.h>

# define COLOR_BLACK (t_color){0.0, 0.0, 0.0, 1.0}
# define COLOR_DGRAY (t_color){0.1, 0.1, 0.1, 1.0}
# define COLOR_BG COLOR_DGRAY

# define SHADOW_BIAS 1e-3
# define SPECULAR_STRENGTH 0.5
# define SHININESS 32

t_vec3			reflect_vector(t_vec3 incident, t_vec3 normal);
t_color			mix_color(t_color color1, t_color color2, float ratio);

float			fresnel_effect(t_vec3 incident, t_vec3 normal,
					float refraction_index);
float			schlick_approx(float cosine, float ref_index);

// Intersections
typedef bool	(*t_intersect_func)(t_ray *, t_shape *, t_hit *);

bool			intersect_plane(t_ray *ray, t_shape *plane, t_hit *hit);
bool			intersect_sphere(t_ray *ray, t_shape *sphere, t_hit *hit);
bool			intersect_revolution(t_ray *ray, t_shape *cy, t_hit *hit);
bool			intersect_scene(t_ray *ray, t_hit *hit, t_uniforms *u);

// Color utils
t_color			blend_colors(t_color c1, t_color c2);
t_color			mult_color_scalar(t_color c, float s);
t_color			mult_colors(t_color c1, t_color c2);
t_vec4			mult_color_vec4_scalar(t_vec4 c, float s);
t_vec4			add_colors_vec4(t_vec4 c1, t_vec4 c2);

// Main ray tracing
void			map_orange_peel(t_hit *hit);
t_color			calculate_lighting(t_hit *hit, t_uniforms *u);
float			get_shadow(t_hit *hit, t_uniforms *u, t_s_light *light);
t_color			trace_ray(t_ray *ray, size_t depth, t_uniforms *u);
void			rt_frag_shader(float *fs_input, t_shader_builtins *builtins,
					void *uni);

#endif
