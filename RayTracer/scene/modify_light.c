#include <minirt.h>

bool	modif_light_brightness(t_rt *rt, t_spot_light *light)
{
	char	*input;

	do
	{
		printf("Enter the new brightness: ");
		input = get_next_line(STDIN_FILENO);
	}while (!is_float(input) && !is_in_range(input, 0, 1));
	light->brightness = ft_atof(input);
	if
	return (true);
}

bool	modif_light_color(t_rt *rt, t_spot_light *light)
{
	char	*input;

	do
	{
		printf("Enter the new color: ");
		input = get_next_line(STDIN_FILENO);
	}while (!is_color(input));
	parse_color(input, &light->color);
	return (true);
}

bool	input_light_menu(t_rt *rt, char	*input, t_spot_light *light)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (modif_light_brightness(rt, light));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (modif_light_color(rt));
	else
	{
		printf("Invalid input\n");
		return (false);
	}
}

void	modify_light_props(t_rt *rt, t_spot_light *light)
{
	char	*input;

	do
	{
		printf(MODIF_LIGHT);
		printf ("Choose the property to modify: ");
		input = get_next_line(STDIN_FILENO);
	}while (!input_light_menu(rt, input, light));
}
