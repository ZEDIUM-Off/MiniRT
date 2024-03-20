/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:25:02 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/20 02:30:27 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	modify_mesh_details(t_rt *rt)
{
	char	*input;

	write(1, "Enter the mesh detail: ", 24);
	input = get_stdin();
	while (!is_float(input) || !is_in_range(input, 8, 64))
	{
		write(1, "Enter the mesh detail: ", 24);
		input = get_stdin();
	}
	rt->mesh_detail = ft_atof(input);
	free(input);
	return (true);
}

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
