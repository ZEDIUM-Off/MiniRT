#include <minirt.h>

void	list_obj(t_rt *rt)
{
	size_t				i;
	t_shape			*shape;
	t_s_light	*light;

	i = 0;
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
	while (i < rt->sc_input.shapes_count + rt->sc_input.s_lights_count)
	{
		light = &rt->sc_input.s_lights[i - rt->sc_input.shapes_count];
		display_light_props(i, light);
		i++;
	}
}

bool	get_obj(t_rt *rt, char *input, t_obj *obj)
{
	int	id;

	if (!is_number(input))
		return (printf("Invalid input\n"), false);
	id = ft_atoii(input);
	if (id < 0 || (size_t)id >= rt->sc_input.shapes_count + rt->sc_input.s_lights_count)
		return (printf("Invalid object number\n"), false);
	if ((size_t)id < rt->sc_input.shapes_count)
	{
		obj->type = rt->sc_input.shapes[id].type;
		obj->data = &rt->sc_input.shapes[id];
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
		write(1, "Enter the object number: ", 25);
		input = get_stdin();
	} while (!get_obj(rt, input, obj));
	free(input);
}
