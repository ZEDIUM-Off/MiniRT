/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:47:38 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/20 12:03:15 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

float	get_float(char *message)
{
	float	value;
	char	*input;

	write(1, message, ft_strlen(message));
	input = get_stdin();
	while (!is_float(input))
	{
		write(1, message, ft_strlen(message));
		input = get_stdin();
	}
	value = ft_atof(input);
	free(input);
	return (value);
}

t_vec3	get_axis(char *axis_name)
{
	t_vec3	axis;

	printf("Enter the %s axis (x, y, z): \n", axis_name);
	axis.x = get_float("x = ");
	axis.y = get_float("\ny = ");
	axis.z = get_float("\nz = ");
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
