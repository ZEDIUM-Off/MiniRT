/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_adders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 06:19:44 by agaley            #+#    #+#             */
/*   Updated: 2024/03/06 06:56:58 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	add_sphere(t_rt *rt, t_sphere *sp)
{
	rt->sc_input.shapes.spheres = realloc(rt->sc_input.shapes.spheres,
			(rt->sc_input.shapes.sp_count + 1) * sizeof(t_sphere));
	if (!rt->sc_input.shapes.spheres)
		return (handle_error(ERR_PARSE_SHAPE_REALLOC, rt));
	rt->sc_input.shapes.spheres[rt->sc_input.shapes.sp_count++] = *sp;
	return (1);
}

int	add_plane(t_rt *rt, t_plan *plane)
{
	rt->sc_input.shapes.planes = realloc(rt->sc_input.shapes.planes,
			(rt->sc_input.shapes.pl_count + 1) * sizeof(t_plan));
	if (!rt->sc_input.shapes.planes)
		return (handle_error(ERR_PARSE_SHAPE_REALLOC, rt));
	rt->sc_input.shapes.planes[rt->sc_input.shapes.pl_count++] = *plane;
	return (1);
}

int	add_cylinder(t_rt *rt, t_cylinder *cy)
{
	rt->sc_input.shapes.cylinders = realloc(rt->sc_input.shapes.cylinders,
			(rt->sc_input.shapes.cy_count + 1) * sizeof(t_cylinder));
	if (!rt->sc_input.shapes.cylinders)
		return (handle_error(ERR_PARSE_SHAPE_REALLOC, rt));
	rt->sc_input.shapes.cylinders[rt->sc_input.shapes.cy_count++] = *cy;
	return (1);
}

int	add_cone(t_rt *rt, t_cone *cone)
{
	rt->sc_input.shapes.cones = realloc(rt->sc_input.shapes.cones,
			(rt->sc_input.shapes.co_count + 1) * sizeof(t_cone));
	if (!rt->sc_input.shapes.cones)
	{
		return (handle_error(ERR_PARSE_SHAPE_REALLOC, rt));
	}
	rt->sc_input.shapes.cones[rt->sc_input.shapes.co_count++] = *cone;
	return (1);
}
