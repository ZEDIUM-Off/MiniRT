#include <minirt.h>

void	rotate_shape(t_shape *shape, t_vec3 axis, float rotation)
{
	t_cone_props		*cn_props;
	t_cylinder_props	*cy_props;
	t_plane_props		*pl_props;

	if (shape->type == PLANE)
	{
		pl_props = (t_plane_props *)shape->properties;
		pl_props->normal = vec3_rotate(pl_props->normal, rotation, axis);
	}
	else if (shape->type == CYLINDER)
	{
		cy_props = (t_cylinder_props *)shape->properties;
		cy_props->axis = vec3_rotate(cy_props->axis, rotation, axis);
	}
	else if (shape->type == CONE)
	{
		cn_props = (t_cone_props *)shape->properties;
		cn_props->axis = vec3_rotate(cn_props->axis, rotation, axis);
	}
}

bool	rotate_obj(t_obj *obj)
{
	char *input;
	t_vec3 axis;
	float rotation;
	t_shape *shape;

	if (obj->type == LIGHT)
		printf("You can't rotate a light\n");
	else if (obj->type == SPHERE)
		printf("You can't rotate a sphere\n");
	else
	{
		shape = (t_shape *)obj->data;
		axis = get_axis("rotation");
		do
		{
			printf("Enter the rotation degre: ");
			input = get_next_line(STDIN_FILENO);
		} while (!is_float(input));
		rotation = ft_atof(input);
		rotate_shape(shape, axis, rotation);
	}
	return (true);
}
