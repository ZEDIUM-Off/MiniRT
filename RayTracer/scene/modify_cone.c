#include <minirt.h>

bool	modif_cone_angle(t_rt *rt, t_shape *shape)
{
	char	*input;

	do
	{
		printf("Enter the new angle: ");
		input = get_next_line(STDIN_FILENO);
	} while (!is_float(input) && !is_in_range(input, 0, 180));
	((t_cone_props *)shape->properties)->angle = ft_atof(input);
	return (true);
}

bool	modif_cone_height(t_rt *rt, t_shape *shape)
{
	char	*input;

	do
	{
		printf("Enter the new height: ");
		input = get_next_line(STDIN_FILENO);
	} while (!is_float(input) && !is_in_range(input, 0, 1000));
	((t_cone_props *)shape->properties)->height = ft_atof(input);
	return (true);
}

bool	modif_cone_axis(t_rt *rt, t_shape *shape)
{
	((t_cone_props *)shape->properties)->axis = get_axis(rt, "direction");
	return (true);
}

bool	input_cone_menu(t_rt *rt, char *input, t_shape *shape)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (modif_cone_angle(rt, shape));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (modif_cone_height(rt, shape));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (modif_cone_axis(rt, shape));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (modif_shape_color(rt, shape));
	else
	{
		printf("Invalid input\n");
		return (false);
	}
}

void	modify_cone_props(t_rt *rt, t_shape *shape)
{
	char	*input;

	do
	{
		printf(MODIF_CONE);
		printf("Enter your command: ");
		input = get_next_line(STDIN_FILENO);
	} while (!input_cone_menu(rt, input, shape));
}
