#include <minirt.h>

bool	modif_cylinder_diameter(t_rt *rt, t_shape *shape)
{
	char	*input;

	do
	{
		printf("Enter the new diameter: ");
		input = get_next_line(STDIN_FILENO);
	} while (!is_float(input) && !is_in_range(input, 0, 1000));
	((t_cylinder_props *)shape->properties)->diameter = ft_atof(input);
	return (true);
}

bool	modif_cylinder_height(t_rt *rt, t_shape *shape)
{
	char	*input;

	do
	{
		printf("Enter the new height: ");
		input = get_next_line(STDIN_FILENO);
	} while (!is_float(input) && !is_in_range(input, 0, 1000));
	((t_cylinder_props *)shape->properties)->height = ft_atof(input);
	return (true);
}

bool	modif_cylinder_axis(t_rt *rt, t_shape *shape)
{
	((t_cylinder_props *)shape->properties)->axis = get_axis(rt, "direction");
	return (true);
}

bool	input_cylinder_menu(t_rt *rt, char *input, t_shape *shape)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (modif_cylinder_diameter(rt, shape));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (modif_cylinder_height(rt, shape));
	else if (ft_strncmp(input, "3", 2) == 0)
		return (modif_cylinder_axis(rt, shape));
	else if (ft_strncmp(input, "4", 2) == 0)
		return (modif_shape_color(rt, shape));
	else
	{
		printf("Invalid input\n");
		return (false);
	}
}

void	modify_cylinder_props(t_rt *rt, t_shape *shape)
{
	char	*input;

	do
	{
		printf(MODIF_CYLINDER);
		printf("Enter your command: ");
		input = get_next_line(STDIN_FILENO);
	} while (!input_cylinder_menu(rt, input, shape));
}
