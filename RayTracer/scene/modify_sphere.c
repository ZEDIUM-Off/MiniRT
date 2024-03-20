/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:49:46 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/20 02:17:42 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	modify_sphere_diameter(t_shape *sphere)
{
	char	*input;

	write(1, "Enter the new diameter: ", 25);
	input = get_stdin();
	while (!is_float(input) || !is_in_range(input, 0, 1000))
	{
		write(1, "Enter the new diameter: ", 25);
		input = get_stdin();
	}
	((t_sphere_props *)sphere->properties)->diameter = ft_atof(input);
	free(input);
	return (true);
}

bool	input_sphere_menu(char *input, t_shape *sphere)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (modify_sphere_diameter(sphere));
	else if (ft_strncmp(input, "2", 2) == 0)
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

	printf(MODIF_SPHERE);
	write(1, "Enter your command: ", 21);
	input = get_stdin();
	while (!input_sphere_menu(input, sphere))
	{
		printf(MODIF_SPHERE);
		write(1, "Enter your command: ", 21);
		input = get_stdin();
	}
	free(input);
}
