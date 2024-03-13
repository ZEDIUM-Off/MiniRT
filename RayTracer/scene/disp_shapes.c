#include <minirt.h>

void	 display_sphere_props(size_t i, t_shape *shape)
{
	t_sphere_props	*props;

	props = (t_sphere_props *)shape->properties;
	printf("[Sphere %3zu] | ", i);
	printf("Position: %5.2f %5.2f %5.2f\t", shape->position.x, shape->position.y, shape->position.z);
	printf("Diameter: %.2f\t", props->diameter);
	printf("Color: %d %d %d\n", shape->color.r, shape->color.g, shape->color.b);
}

void	display_plane_props(size_t i, t_shape *shape)
{
	t_plane_props	*props;

	props = (t_plane_props *)shape->properties;
	printf("[Plane %3zu] | ", i);
	printf("Position: %5.2f %5.2f %5.2f\t", shape->position.x, shape->position.y, shape->position.z);
	printf("Normal: %5.2f %5.2f %5.2f\t", props->normal.x, props->normal.y, props->normal.z);
	printf("Color: %d %d %d\n", shape->color.r, shape->color.g, shape->color.b);
}

void	display_cylinder_props(size_t i, t_shape *shape)
{
	t_cylinder_props	*props;

	props = (t_cylinder_props *)shape->properties;
	printf("[Cylinder %3zu] | ", i);
	printf("Position: %5.2f %5.2f %5.2f\t", shape->position.x, shape->position.y, shape->position.z);
	printf("Axis: %5.2f %5.2f %5.2f\t", props->axis.x, props->axis.y, props->axis.z);
	printf("Diameter: %.2f\t", props->diameter);
	printf("Height: %.2f\t", props->height);
	printf("Color: %d %d %d\n", shape->color.r, shape->color.g, shape->color.b);
}


void	display_cone_props(size_t i, t_shape *shape)
{
	t_cone_props	*props;

	props = (t_cone_props *)shape->properties;
	printf("[Cone %3zu] | ", i);
	printf("Position: %5.2f %5.2f %5.2f\t", shape->position.x, shape->position.y, shape->position.z);
	printf("Axis: %5.2f %5.2f %5.2f\t", props->axis.x, props->axis.y, props->axis.z);
	printf("Angle: %.2f\t", props->angle);
	printf("Height: %.2f\t", props->height);
	printf("Color: %d %d %d\n", shape->color.r, shape->color.g, shape->color.b);
}

void	display_light_props(size_t i, t_s_light *light)
{
	printf("[Light %3zu] | ", i);
	printf("Position: %5.2f %5.2f %5.2f\t", light->position.x, light->position.y, light->position.z);
	printf("Color: %d %d %d\t", light->color.r, light->color.g, light->color.b);
	printf("Brightness: %.2f\n", light->brightness_ratio);
}
