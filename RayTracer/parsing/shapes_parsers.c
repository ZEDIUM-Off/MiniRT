/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_parsers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 06:21:52 by agaley            #+#    #+#             */
/*   Updated: 2024/03/06 06:39:33 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere(char **tokens, t_sphere *sphere, t_rt *rt)
{
	if (!parse_vector3(tokens[1], &sphere->center))
		return (handle_error(ERR_PARSE_SPHERE_POS, rt));
	sphere->radius = ft_atof(tokens[2]);
	if (sphere->radius < 0)
		return (handle_error(ERR_PARSE_SPHERE_INVALID_DIAM, rt));
	if (!parse_color(tokens[3], &sphere->color))
		return (handle_error(ERR_PARSE_SPHERE_COLOR, rt));
	return (1);
}

int	parse_plane(char **tokens, t_plan *plane, t_rt *rt)
{
	if (!parse_vector3(tokens[1], &plane->point))
		return (handle_error(ERR_PARSE_PLANE_POS, rt));
	if (!parse_vector3(tokens[2], &plane->normal))
		return (handle_error(ERR_PARSE_PLANE_NORMAL, rt));
	if (!parse_color(tokens[3], &plane->color))
		return (handle_error(ERR_PARSE_PLANE_COLOR, rt));
	return (1);
}

int	parse_cylinder(char **tokens, t_cylinder *cylinder, t_rt *rt)
{
	if (!parse_vector3(tokens[1], &cylinder->position))
		return (handle_error(ERR_PARSE_CYLINDER_POS, rt));
	if (!parse_vector3(tokens[2], &cylinder->axis))
		return (handle_error(ERR_PARSE_CYLINDER_AXIS, rt));
	cylinder->diameter = ft_atof(tokens[3]);
	if (cylinder->diameter < 0)
		return (handle_error(ERR_PARSE_CYLINDER_DIAM, rt));
	cylinder->height = ft_atof(tokens[4]);
	if (cylinder->height < 0)
		return (handle_error(ERR_PARSE_CYLINDER_HEIGHT, rt));
	if (!parse_color(tokens[5], &cylinder->color))
		return (handle_error(ERR_PARSE_CYLINDER_COLOR, rt));
	return (1);
}

int	parse_cone(char **tokens, t_cone *cone, t_rt *rt)
{
	if (!parse_vector3(tokens[1], &cone->position))
		return (handle_error(ERR_PARSE_CONE_POS, rt));
	if (!parse_vector3(tokens[2], &cone->axis))
		return (handle_error(ERR_PARSE_CONE_AXIS, rt));
	cone->angle = ft_atof(tokens[3]);
	if (cone->angle < 0 || cone->angle > 180)
		return (handle_error(ERR_PARSE_CONE_ANGLE, rt));
	cone->height = ft_atof(tokens[4]);
	if (cone->height < 0)
		return (handle_error(ERR_PARSE_CONE_HEIGHT, rt));
	if (!parse_color(tokens[5], &cone->color))
		return (handle_error(ERR_PARSE_CONE_COLOR, rt));
	return (1);
}
