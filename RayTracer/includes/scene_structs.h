/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:20:09 by agaley            #+#    #+#             */
/*   Updated: 2024/03/04 01:19:59 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_STRUCTS_H
# define SCENE_STRUCTS_H

typedef struct s_ambient_light
{
	float	ratio;
	t_color color;
}t_ambient_light;

typedef struct s_spot_light
{
	t_vec3 position;
	float	brightness_ratio;
	t_color color;
}t_spot_light;

typedef enum e_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}t_shape_type;

typedef struct s_sphere_props
{
	float	diameter;
}t_sphere_props;

typedef struct s_plane_props
{
	t_vec3 normal;
}t_plane_props;

typedef struct s_cylinder
{
	float	diameter;
	float	height;
	t_vec3	axis;
}t_cylinder_props;

typedef struct s_cone
{
	float	angle;
	float	height;
	t_vec3	axis;
}t_cone_props;

typedef union u_shape_props
{
	t_sphere_props sphere;
	t_plane_props plane;
	t_cylinder_props cylinder;
	t_cone_props cone;
}u_shape_props;

typedef struct s_shape
{
	t_shape_type type;
	t_vec3 position;
	u_shape_props properties;
	t_color color;
}t_shape;

typedef struct s_scene_input
{
	t_ambient_light a_light;
	t_spot_light s_light;
	t_shape* shapes;
	size_t		shapes_count;
}t_sc_input;

#endif
