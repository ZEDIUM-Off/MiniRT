#include <minirt.h>

bool	modif_light_brightness(t_s_light *light)
{
	char	*input;

	do
	{
		write(1, "Enter the new brightness: ", 27);
		input = get_next_line(STDIN_FILENO);
	}while (!is_float(input) && !is_in_range(input, 0, 1));
	light->brightness_ratio = ft_atof(input);
	return (true);
}

bool	modif_light_color(t_s_light *light)
{
	char	*input;

	do
	{
		write(1, "Enter the new color: ", 22);
		input = get_next_line(STDIN_FILENO);
	}while (!is_color(input));
	parse_color(input, &light->color);
	return (true);
}

bool	input_light_menu(char	*input, t_s_light *light)
{
	if (ft_strncmp(input, "1\n", 3) == 0)
		return (modif_light_brightness(light));
	else if (ft_strncmp(input, "2\n", 3) == 0)
		return (modif_light_color(light));
	else
	{
		printf("Invalid input\n");
		return (false);
	}
}

void	modify_light_props(t_s_light *light)
{
	char	*input;

	do
	{
		printf(MODIF_LIGHT);
		write(1, "Choose the property to modify: ", 31);
		input = get_next_line(STDIN_FILENO);
	}while (!input_light_menu(input, light));
}
