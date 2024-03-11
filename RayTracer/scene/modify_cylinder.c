#include <minirt.h>

bool	modif_cylinder_diameter(t_shape *shape)
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

bool	modif_cylinder_height(t_shape *shape)
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

bool	modif_cylinder_axis(t_shape *shape)
{
	((t_cylinder_props *)shape->properties)->axis = get_axis("direction");
	return (true);
}

bool	input_cylinder_menu(char *input, t_shape *shape)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (modif_cylinder_diameter(shape));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (modif_cylinder_height(shape));
	else if (ft_strncmp(input, "3", 2) == 0)
		return (modif_cylinder_axis(shape));
	else if (ft_strncmp(input, "4", 2) == 0)
		return (modif_shape_color(shape));
	else
	{
		printf("Invalid input\n");
		return (false);
	}
}

void	modify_cylinder_props(t_shape *shape)
{
	char	*input;

	do
	{
		printf(MODIF_CYLINDER);
		printf("Enter your command: ");
		input = get_next_line(STDIN_FILENO);
	} while (!input_cylinder_menu(input, shape));
}
