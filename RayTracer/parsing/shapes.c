/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:53:38 by agaley            #+#    #+#             */
/*   Updated: 2024/02/26 21:11:49 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int parse_sphere(char** tokens, t_shape* shape)
{
	shape->type = SPHERE;
	if (!parse_vector3(tokens[1], &shape->position))
		return (0);
	shape->properties.sphere.diameter = atof(tokens[2]);
	return parse_color(tokens[3], &shape->color);
}

static int parse_plane(char** tokens, t_shape* shape)
{
	shape->type = PLANE;
	if (!parse_vector3(tokens[1], &shape->position))
		return (0);
	if (!parse_vector3(tokens[2], &shape->properties.plane.normal))
		return (0);
	return parse_color(tokens[3], &shape->color);
}

static int parse_cylinder(char** tokens, t_shape* shape)
{
	shape->type = CYLINDER;
	if (!parse_vector3(tokens[1], &shape->position))
		return (0);
	shape->properties.cylinder.diameter = atof(tokens[3]);
	shape->properties.cylinder.height = atof(tokens[4]);
	return parse_color(tokens[5], &shape->color);
}

static int parse_cone(char** tokens, t_shape* shape)
{
	shape->type = CONE;
	if (!parse_vector3(tokens[1], &shape->position))
		return (0);
	shape->properties.cone.angle = atof(tokens[3]);
	shape->properties.cone.height = atof(tokens[4]);
	return parse_color(tokens[5], &shape->color);
}

int parse_shape(char** tokens, int num_tokens, t_shape* shape)
{
	int result;

	result = 0;
	if (strcmp(tokens[0], "sp") == 0 && num_tokens == 5)
		result = parse_sphere(tokens, shape);
	else if (strcmp(tokens[0], "pl") == 0 && num_tokens == 5)
		result = parse_plane(tokens, shape);
	else if (strcmp(tokens[0], "cy") == 0 && num_tokens == 7)
		result = parse_cylinder(tokens, shape);
	else if (strcmp(tokens[0], "co") == 0 && num_tokens == 7)
		result = parse_cone(tokens, shape);
	else
		return (0);
	return result;
}
