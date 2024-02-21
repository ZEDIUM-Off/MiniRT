/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:43:04 by agaley            #+#    #+#             */
/*   Updated: 2024/02/21 15:20:46 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# include <stdlib.h>

# define MAX_DEPTH 5

# define COLOR_BLACK (t_vec3){0.0, 0.0, 0.0}
# define COLOR_DGRAY (t_vec3){0.1, 0.1, 0.1}

# define COLOR_BG COLOR_DGRAY

typedef struct s_fresnel
{
	float	cosi;
	float	etai;
	float	etat;
	float	sint;
	float	cost;
	float	rs;
	float	rp;
}t_fresnel;

typedef struct s_material {
	t_vec3	ambient;
	t_vec3	diffuse;
	t_vec3	specular;
	float	shininess;
	float	refraction_index;
}t_material;

typedef struct s_triangle {
	t_vec3		v0;
	t_vec3		v1;
	t_vec3		v2;
	t_material	material;
}t_triangle;

typedef struct s_sphere {
	t_vec3		center;
	float		radius;
	t_material	material;
}t_sphere;

typedef struct s_hit {
	t_material	material;
	t_vec3		point;
	t_vec3		normal;
	float		distance;
}t_hit;

t_vec3	reflect_vector(t_vec3 incident, t_vec3 normal);
t_vec3	mix_color(t_vec3 color1, t_vec3 color2, float ratio);

float	schlick_approximation(float cosine, float ref_index);

bool	intersect_scene(const t_vec3 ray_origin,
	const t_vec3 ray_direction, t_hit* hit);

void	rt_frag_shader(float* fs_input, t_shader_builtins* builtins, void* uni);

#endif
