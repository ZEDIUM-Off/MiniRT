/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:47:38 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/20 02:07:55 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	get_axis(char *axis_name)
{
	t_vec3	axis;
	char	*input;

	printf("Enter the %s axis (x, y, z): \n", axis_name);
	write(1, "x = ", 4);
	input = get_stdin();
	while (!is_float(input))
	{
		write(1, "x = ", 4);
		input = get_stdin();
	}
	axis.x = ft_atof(input);
	write(1, "\ny = ", 5);
	input = get_stdin();
	while (!is_float(input))
	{
		write(1, "\ny = ", 5);
		input = get_stdin();
	}
	axis.y = ft_atof(input);
	write(1, "\nz = ", 5);
	input = get_stdin();
	while (!is_float(input))
	{
		write(1, "\nz = ", 5);
		input = get_stdin();
	}
	axis.z = ft_atof(input);
	free(input);
	return (norm_vec3(axis));
}

bool	modif_shape_color(t_shape *shape)
{
	char	*input;

	write(1, "Enter the new color: ", 22);
	input = get_stdin();
	while (!is_color(input))
	{
		write(1, "Enter the new color: ", 22);
		input = get_stdin();
	}
	parse_color(input, &shape->color);
	free(input);
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
		return (printf("\n%s not in range. (min: %f, max: %f)\n", input, min,
				max), false);
	return (true);
}

bool	is_color(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isdigit(input[i]) && input[i] != ',')
			return (printf("\n%s not a color. (format : 0-255,0-255,0-255)\n",
					input), false);
		i++;
	}
	return (true);
}
