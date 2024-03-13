#include <minirt.h>

bool	modify_sphere_diameter(t_shape *sphere)
{
	char	*input;

	do
	{
		write(1, "Enter the new diameter: ", 25);
		input = get_next_line(STDIN_FILENO);
	} while (!is_float(input) && !is_in_range(input, 0, 1000));
	((t_sphere_props *)sphere->properties)->diameter = ft_atof(input);
	return (true);
}

bool	input_sphere_menu(char *input, t_shape *sphere)
{
	if (ft_strncmp(input, "1\n", 3) == 0)
		return (modify_sphere_diameter(sphere));
	else if (ft_strncmp(input, "2\n", 3) == 0)
		return (modif_shape_color(sphere));
	else
	{
		printf("Invalid input\n");
		return (false);
	}
}

void	modify_sphere_props(t_shape *sphere)
{
	char	*input;

	do
	{
		printf(MODIF_SPHERE);
		write(1, "Enter your command: ", 21);
		input = get_next_line(STDIN_FILENO);
	} while (!input_sphere_menu(input, sphere));
}
