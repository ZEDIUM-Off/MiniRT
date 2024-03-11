#include <minirt.h>

t_vec3	get_axis(char *axis_name)
{
	t_vec3	axis;
	char	*input;

	printf("Enter the %s axis (x, y, z): \n", axis_name);
	do
	{
		printf("x = ");
		input = get_next_line(STDIN_FILENO);
	} while (!is_float(input));
	axis.x = ft_atof(input);
	do
	{
		printf("\ny = ");
		input = get_next_line(STDIN_FILENO);
	} while (!is_float(input));
	axis.y = ft_atof(input);
	do
	{
		printf("\nz = ");
		input = get_next_line(STDIN_FILENO);
	} while (!is_float(input));
	axis.z = ft_atof(input);
	return (norm_vec3(axis));
}

bool	modif_shape_color(t_shape *shape)
{
	char	*input;

	do
	{
		printf("Enter the new color: ");
		input = get_next_line(STDIN_FILENO);
	} while (!is_color(input));
	parse_color(input, &shape->color);
	return (true);
}

bool	is_float(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '-')
		i++;
	while (input[i])
	{
		if (!ft_isdigit(input[i]) && input[i] != '.')
			return (printf("\n%s not a float. (format : 0.0)\n", input), false);
		i++;
	}
	return (true);
}

bool	is_in_range(char *input, float min, float max)
{
	float	value;

	value = ft_atof(input);
	if (value < min || value > max)
		return (printf("\n%s not in range. (min: %f, max: %f)\n", input, min, max), false);
	return (true);
}

bool	is_color(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isdigit(input[i]) && input[i] != ',')
			return (printf("\n%s not a color. (format : 0,0,0)\n", input), false);
		i++;
	}
	return (true);
}
