/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:48:58 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 23:22:13 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	display_sphere_props(size_t i, t_shape *shape)
{
	t_sphere_props	*props;

	props = (t_sphere_props *)shape->properties;
	printf("[Sphere\t%3zu] | ", i);
	printf("Position: %5.2f %5.2f %5.2f\t", shape->position.x,
		shape->position.y, shape->position.z);
	printf("Color: %d %d %d\t", shape->color.r, shape->color.g, shape->color.b);
	printf("Diameter: %.2f\n", props->diameter);
}

void	display_plane_props(size_t i, t_shape *shape)
{
	t_plane_props	*props;

	props = (t_plane_props *)shape->properties;
	printf("[Plane\t%3zu] | ", i);
	printf("Position: %5.2f %5.2f %5.2f\t", shape->position.x,
		shape->position.y, shape->position.z);
	printf("Color: %d %d %d\t", shape->color.r, shape->color.g, shape->color.b);
	printf("Normal: %5.2f %5.2f %5.2f\n", props->normal.x, props->normal.y,
		props->normal.z);
}

void	display_cylinder_props(size_t i, t_shape *shape)
{
	t_cylinder_props	*props;

	props = (t_cylinder_props *)shape->properties;
	printf("[Cylinder\t%3zu] | ", i);
	printf("Position: %5.2f %5.2f %5.2f\t", shape->position.x,
		shape->position.y, shape->position.z);
	printf("Color: %d %d %d\t", shape->color.r, shape->color.g, shape->color.b);
	printf("Diameter: %.2f\t", props->diameter);
	printf("Axis: %5.2f %5.2f %5.2f\t", props->axis.x, props->axis.y,
		props->axis.z);
	printf("Height: %.2f\n", props->height);
}

void	display_cone_props(size_t i, t_shape *shape)
{
	t_cone_props	*props;

	props = (t_cone_props *)shape->properties;
	printf("[Cone\t%3zu] | ", i);
	printf("Position: %5.2f %5.2f %5.2f\t", shape->position.x,
		shape->position.y, shape->position.z);
	printf("Color: %d %d %d\t", shape->color.r, shape->color.g, shape->color.b);
	printf("Axis: %5.2f %5.2f %5.2f\t", props->axis.x, props->axis.y,
		props->axis.z);
	printf("Angle: %.2f\t", props->angle);
	printf("Height: %.2f\n", props->height);
}

void	display_light_props(size_t i, t_s_light *light)
{
	printf("[Light\t%3zu] | ", i);
	printf("Color: %d %d %d\t", light->color.r, light->color.g, light->color.b);
	printf("Position: %5.2f %5.2f %5.2f\t", light->position.x,
		light->position.y, light->position.z);
	printf("Brightness: %.2f\n", light->brightness_ratio);
}
