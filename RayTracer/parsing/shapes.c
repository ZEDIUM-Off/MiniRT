/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:53:38 by agaley            #+#    #+#             */
/*   Updated: 2024/03/09 14:23:08 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_sphere(char **tokens, t_shape *sphere, t_rt *rt)
{
	sphere->type = SPHERE;
	sphere->properties = malloc(sizeof(t_sphere_props));
	if (!sphere->properties)
		return (handle_error(ERR_PARSE_SHAPE_REALLOC, rt));
	if (!parse_vector3(tokens[1], &sphere->position))
		return (handle_error(ERR_PARSE_SPHERE_POS, rt));
	((t_sphere_props *)(sphere->properties))->diameter = ft_atof(tokens[2]);
	if (((t_sphere_props *)(sphere->properties))->diameter < 0)
		return (handle_error(ERR_PARSE_SPHERE_INVALID_DIAM, rt));
	if (!parse_color(tokens[3], &sphere->color))
		return (handle_error(ERR_PARSE_SPHERE_COLOR, rt));
	return (1);
}

static int	parse_plane(char **tokens, t_shape *plane, t_rt *rt)
{
	plane->type = PLANE;
	plane->properties = malloc(sizeof(t_plane_props));
	if (!plane->properties)
		return (handle_error(ERR_PARSE_SHAPE_REALLOC, rt));
	if (!parse_vector3(tokens[1], &plane->position))
		return (handle_error(ERR_PARSE_PLANE_POS, rt));
	if (!parse_vector3(tokens[2],
			&((t_plane_props *)(plane->properties))->normal))
		return (handle_error(ERR_PARSE_PLANE_NORMAL, rt));
	if (!parse_color(tokens[3], &plane->color))
		return (handle_error(ERR_PARSE_PLANE_COLOR, rt));
	return (1);
}

static int	parse_cylinder(char **tokens, t_shape *cy, t_rt *rt)
{
	cy->type = CYLINDER;
	cy->properties = malloc(sizeof(t_cylinder_props));
	if (!cy->properties)
		return (handle_error(ERR_PARSE_SHAPE_REALLOC, rt));
	if (!parse_vector3(tokens[1], &cy->position))
		return (handle_error(ERR_PARSE_CYLINDER_POS, rt));
	if (!parse_vector3(tokens[2],
			&((t_cylinder_props *)(cy->properties))->axis))
		return (handle_error(ERR_PARSE_CYLINDER_AXIS, rt));
	((t_cylinder_props *)(cy->properties))->diameter = ft_atof(tokens[3]);
	if (((t_cylinder_props *)(cy->properties))->diameter < 0)
		return (handle_error(ERR_PARSE_CYLINDER_DIAM, rt));
	((t_cylinder_props *)(cy->properties))->height = ft_atof(tokens[4]);
	if (((t_cylinder_props *)(cy->properties))->height < 0)
		return (handle_error(ERR_PARSE_CYLINDER_HEIGHT, rt));
	if (!parse_color(tokens[5], &cy->color))
		return (handle_error(ERR_PARSE_CYLINDER_COLOR, rt));
	return (1);
}

static int	parse_cone(char **tokens, t_shape *cone, t_rt *rt)
{
	cone->type = CONE;
	cone->properties = malloc(sizeof(t_cone_props));
	if (!cone->properties)
		return (handle_error(ERR_PARSE_SHAPE_REALLOC, rt));
	if (!parse_vector3(tokens[1], &cone->position))
		return (handle_error(ERR_PARSE_CONE_POS, rt));
	if (!parse_vector3(tokens[2], &((t_cone_props *)(cone->properties))->axis))
		return (handle_error(ERR_PARSE_CONE_AXIS, rt));
	((t_cone_props *)(cone->properties))->angle = ft_atof(tokens[3]);
	if (((t_cone_props *)(cone->properties))->angle < 0
		|| ((t_cone_props *)(cone->properties))->angle > 180)
		return (handle_error(ERR_PARSE_CONE_ANGLE, rt));
	((t_cone_props *)(cone->properties))->height = ft_atof(tokens[4]);
	if (((t_cone_props *)(cone->properties))->height < 0)
		return (handle_error(ERR_PARSE_CONE_HEIGHT, rt));
	if (!parse_color(tokens[5], &cone->color))
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
	if (ft_strcmp(tokens[0], "sp") == 0 && num_tokens != 4)
		return (handle_error(ERR_PARSE_SPHERE_ARGS, rt));
	else if (ft_strcmp(tokens[0], "sp") == 0)
		return (parse_sphere(tokens, shape, rt));
	else if (ft_strcmp(tokens[0], "pl") == 0 && num_tokens != 4)
		return (handle_error(ERR_PARSE_PLANE_ARGS, rt));
	else if (ft_strcmp(tokens[0], "pl") == 0)
		return (parse_plane(tokens, shape, rt));
	else if (ft_strcmp(tokens[0], "cy") == 0 && num_tokens != 6)
		return (handle_error(ERR_PARSE_CYLINDER_ARGS, rt));
	else if (ft_strcmp(tokens[0], "cy") == 0)
		return (parse_cylinder(tokens, shape, rt));
	else if (ft_strcmp(tokens[0], "co") == 0 && num_tokens != 6)
		return (handle_error(ERR_PARSE_CONE_ARGS, rt));
	else if (ft_strcmp(tokens[0], "co") == 0)
		return (parse_cone(tokens, shape, rt));
	return (handle_error(ERR_PARSE_SHAPE_UNKNOWN, rt));
}
