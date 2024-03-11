#include <minirt.h>

void	list_obj(t_rt *rt)
{
	size_t				i;
	t_shape			*shape;
	t_spot_light	*light;

	i = 0;
	printf("\n\nOBJECT LIST\n");
	while (i < rt->sc_input.shapes_count)
	{
		shape = &rt->sc_input.shapes[i];
		if (shape->type == SPHERE)
			display_sphere_props(i, shape);
		else if (shape->type == PLANE)
			display_plane_props(i, shape);
		else if (shape->type == CYLINDER)
			display_cylinder_props(i, shape);
		else if (shape->type == CONE)
			display_cone_props(i, shape);
		i++;
	}
	while (i < rt->sc_input.shapes_count + rt->sc_input.lights_count)
	{
		light = &rt->sc_input.s_lights[i];
		display_light_props(i, light);
		i++;
	}
}

bool	get_obj(t_rt *rt, char *input, t_obj *obj)
{
	int	id;

	if (!is_number(input))
		return (printf("Invalid input\n"), false);
	id = ft_atoi(input);
	if (id < 0 || id >= rt->sc_input.shapes_count + rt->sc_input.lights_count)
		return (printf("Invalid object number\n"), false);
	if (id < rt->sc_input.shapes_count)
	{
		obj->type = rt->sc_input.shapes[id].type;
		obj->type = &rt->sc_input.shapes[id];
	}
	else
	{
		obj->type = LIGHT;
		obj->data = &rt->sc_input.s_lights[id - rt->sc_input.shapes_count];
	}
	return (true);
}

void	obj_menu(t_rt *rt, t_obj *obj)
{
	char *input;

	do
	{
		list_obj(rt);
		printf("Enter the object number: ");
		input = get_next_line(STDIN_FILENO);
	} while (!get_obj(rt, input, obj));
}
