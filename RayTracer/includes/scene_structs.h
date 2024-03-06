/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:20:09 by agaley            #+#    #+#             */
/*   Updated: 2024/03/06 06:53:20 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_STRUCTS_H
# define SCENE_STRUCTS_H

typedef struct s_ambient_light
{
	float			ratio;
	t_color			color;
}					t_ambient_light;

typedef struct s_spot_light
{
	t_vec3			position;
	float			brightness_ratio;
	t_color			color;
}					t_spot_light;

typedef struct s_sphere
{
	t_vec3			center;
	double			radius;
	t_color			color;
}					t_sphere;

typedef struct s_plane
{
	t_vec3			point;
	t_vec3			normal;
	t_color			color;
}					t_plan;

typedef struct s_cylinder
{
	t_vec3			position;
	t_vec3			axis;
	double			diameter;
	double			height;
	t_color			color;
}					t_cylinder;

typedef struct s_cone
{
	t_vec3			position;
	t_vec3			axis;
	double			angle;
	double			height;
	t_color			color;
}					t_cone;

typedef struct s_shapes
{
	t_sphere		*spheres;
	size_t			sp_count;
	t_plan			*planes;
	size_t			pl_count;
	t_cylinder		*cylinders;
	size_t			cy_count;
	t_cone			*cones;
	size_t			co_count;
}					t_shapes;

typedef struct s_scene_input
{
	t_ambient_light	a_light;
	t_spot_light	s_light;
	t_shapes		shapes;
}					t_sc_input;

#endif
