#include <minirt.h>

bool	modify_sphere_diameter(t_rt *rt, t_shape *sphere)
{
	char	*input;

	do
	{
		printf("Enter the new diameter: ");
		input = get_next_line(STDIN_FILENO);
	} while (!is_float(input) && !is_in_range(input, 0, 1000));
	((t_sphere_props *)sphere->properties)->diameter = ft_atof(input);
	return (true);
}

bool	input_sphere_menu(t_rt *rt, char *input, t_shape *sphere)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (modify_sphere_diameter(rt, sphere));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (modif_shape_color(rt, sphere));
	else
	{
		printf("Invalid input\n");
		return (false);
	}
}

void	modify_sphere_props(t_rt *rt, t_shape *sphere)
{
	char	*input;

	do
	{
		printf(MODIF_SPHERE);
		printf("Enter your command: ");
		input = get_next_line(STDIN_FILENO);
	} while (!input_sphere_menu(rt, input, sphere));
}
