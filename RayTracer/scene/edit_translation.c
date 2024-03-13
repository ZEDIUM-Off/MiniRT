#include <minirt.h>

t_vec3	get_translation()
{
	t_vec3	axis;
	float	value;
	char	*input;

	axis = get_axis("translation");
	printf("Enter the translation value: \n");
	do
	{
		write(1, "value = ", 8);
		input = get_next_line(STDIN_FILENO);
	} while (!is_float(input));
	value = ft_atof(input);
	return (scale_vec3s(axis, value));
}

bool	translate_obj(t_obj *obj)
{
	t_vec3 translation;
	t_shape *shape;
	t_s_light *light;

	translation = get_translation();
	if (obj->type == LIGHT)
	{
		light = (t_s_light *)obj->data;
		light->position = add_vec3s(light->position, translation);
	}
	else
	{
		shape = (t_shape *)obj->data;
		shape->position = add_vec3s(shape->position, translation);
	}
	return (true);
}
