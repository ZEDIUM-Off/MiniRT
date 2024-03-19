/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:25:02 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/19 11:05:09 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	make_mesh(t_rt *rt, t_shape *shape)
{
	if (shape->type == SPHERE)
		new_sphere(rt, shape);
	else if (shape->type == PLANE)
		new_plane(rt, shape);
	else if (shape->type == CYLINDER)
		new_cylinder(rt, shape);
	else if (shape->type == CONE)
		new_cone(rt, shape);
}
