/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:53:38 by agaley            #+#    #+#             */
/*   Updated: 2024/03/07 16:08:24 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_sphere(char **tokens, t_shape *shape, t_rt *rt)
{
	shape->type = SPHERE;
	shape->properties = malloc(sizeof(t_sphere_props));
	if (!parse_vector3(tokens[1], &shape->position))
		return (handle_error(ERR_PARSE_SPHERE_POS, rt));
	((t_sphere_props *)shape->properties)->diameter = ft_atof(tokens[2]);
	if (((t_sphere_props *)shape->properties)->diameter < 0)
		return (handle_error(ERR_PARSE_SPHERE_INVALID_DIAM, rt));
	if (!parse_color(tokens[3], &shape->color))
		return (handle_error(ERR_PARSE_SPHERE_COLOR, rt));
	return (1);
}

static int	parse_plane(char **tokens, t_shape *shape, t_rt *rt)
{
	shape->type = PLANE;
	shape->properties = malloc(sizeof(t_plane_props));
	if (!parse_vector3(tokens[1], &shape->position))
		return (handle_error(ERR_PARSE_PLANE_POS, rt));
	if (!parse_vector3(tokens[2],
			&((t_plane_props *)shape->properties)->normal))
		return (handle_error(ERR_PARSE_PLANE_NORMAL, rt));
	if (!parse_color(tokens[3], &shape->color))
		return (handle_error(ERR_PARSE_PLANE_COLOR, rt));
	return (1);
}

static int	parse_cylinder(char **tokens, t_shape *shape, t_rt *rt)
{
	shape->type = CYLINDER;
	shape->properties = malloc(sizeof(t_cylinder_props));
	if (!parse_vector3(tokens[1], &shape->position))
		return (handle_error(ERR_PARSE_CYLINDER_POS, rt));
	if (!parse_vector3(tokens[2],
			&((t_cylinder_props *)shape->properties)->axis))
		return (handle_error(ERR_PARSE_CYLINDER_AXIS, rt));
	((t_cylinder_props *)shape->properties)->diameter = ft_atof(tokens[3]);
	if (((t_cylinder_props *)shape->properties)->diameter < 0)
		return (handle_error(ERR_PARSE_CYLINDER_DIAM, rt));
	((t_cylinder_props *)shape->properties)->height = ft_atof(tokens[4]);
	if (((t_cylinder_props *)shape->properties)->height < 0)
		return (handle_error(ERR_PARSE_CYLINDER_HEIGHT, rt));
	if (!parse_color(tokens[5], &shape->color))
		return (handle_error(ERR_PARSE_CYLINDER_COLOR, rt));
	return (1);
}

static int	parse_cone(char **tokens, t_shape *shape, t_rt *rt)
{
	shape->type = CONE;
	shape->properties = malloc(sizeof(t_cone_props));
	if (!parse_vector3(tokens[1], &shape->position))
		return (handle_error(ERR_PARSE_CONE_POS, rt));
	if (!parse_vector3(tokens[2], &((t_cone_props *)shape->properties)->axis))
		return (handle_error(ERR_PARSE_CONE_AXIS, rt));
	((t_cone_props *)shape->properties)->angle = ft_atof(tokens[3]);
	if (((t_cone_props *)shape->properties)->angle < 0
		|| ((t_cone_props *)shape->properties)->angle > 180)
		return (handle_error(ERR_PARSE_CONE_ANGLE, rt));
	((t_cone_props *)shape->properties)->height = ft_atof(tokens[4]);
	if (((t_cone_props *)shape->properties)->height < 0)
		return (handle_error(ERR_PARSE_CONE_HEIGHT, rt));
	if (!parse_color(tokens[5], &shape->color))
		return (handle_error(ERR_PARSE_CONE_COLOR, rt));
	return (1);
}

int	parse_shape(char **tokens, int num_tokens, t_rt *rt)
{
	t_shape	*shape;

	rt->sc_input.shapes = realloc(rt->sc_input.shapes,
			(rt->sc_input.shapes_count + 1) * sizeof(t_shape));
	if (!rt->sc_input.shapes)
		return (handle_error(ERR_PARSE_SHAPE_REALLOC, rt));
	shape = &rt->sc_input.shapes[rt->sc_input.shapes_count];
	rt->sc_input.shapes_count++;
	if (strcmp(tokens[0], "sp") == 0 && num_tokens != 4)
		return (handle_error(ERR_PARSE_SPHERE_ARGS, rt));
	else if (strcmp(tokens[0], "sp") == 0)
		return (parse_sphere(tokens, shape, rt));
	else if (strcmp(tokens[0], "pl") == 0 && num_tokens != 4)
		return (handle_error(ERR_PARSE_PLANE_ARGS, rt));
	else if (strcmp(tokens[0], "pl") == 0)
		return (parse_plane(tokens, shape, rt));
	else if (strcmp(tokens[0], "cy") == 0 && num_tokens != 6)
		return (handle_error(ERR_PARSE_CYLINDER_ARGS, rt));
	else if (strcmp(tokens[0], "cy") == 0)
		return (parse_cylinder(tokens, shape, rt));
	else if (strcmp(tokens[0], "co") == 0 && num_tokens != 6)
		return (handle_error(ERR_PARSE_CONE_ARGS, rt));
	else if (strcmp(tokens[0], "co") == 0)
		return (parse_cone(tokens, shape, rt));
	return (handle_error(ERR_PARSE_SHAPE_UNKNOWN, rt));
}
