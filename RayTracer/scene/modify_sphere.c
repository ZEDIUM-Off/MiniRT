/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:49:46 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 13:49:49 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	modify_sphere_diameter(t_shape *sphere)
{
	char	*input;

	do
	{
		write(1, "Enter the new diameter: ", 25);
		input = get_stdin();
	} while (!is_float(input) && !is_in_range(input, 0, 1000));
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

	do
	{
		printf(MODIF_SPHERE);
		write(1, "Enter your command: ", 21);
		input = get_stdin();
	} while (!input_sphere_menu(input, sphere));
	free(input);
}
