#include <minirt.h>

t_vec3	get_axis(t_rt *rt, char *axis_name)
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
	return (axis);
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
