/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:48:13 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 13:49:26 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	modif_cylinder_diameter(t_shape *shape)
{
	char	*input;

	do
	{
		write(1, "Enter the new diameter: ", 25);
		input = get_stdin();
	} while (!is_float(input) && !is_in_range(input, 0, 1000));
	((t_cylinder_props *)shape->properties)->diameter = ft_atof(input);
	free(input);
	return (true);
}

bool	modif_cylinder_height(t_shape *shape)
{
	char	*input;

	do
	{
		write(1, "Enter the new height: ", 23);
		input = get_stdin();
	} while (!is_float(input) && !is_in_range(input, 0, 1000));
	((t_cylinder_props *)shape->properties)->height = ft_atof(input);
	free(input);
	return (true);
}

bool	modif_cylinder_axis(t_shape *shape)
{
	((t_cylinder_props *)shape->properties)->axis = get_axis("direction");
	return (true);
}

bool	input_cylinder_menu(char *input, t_shape *shape)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (modif_cylinder_diameter(shape));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (modif_cylinder_height(shape));
	else if (ft_strncmp(input, "3", 2) == 0)
		return (modif_cylinder_axis(shape));
	else if (ft_strncmp(input, "4", 2) == 0)
		return (modif_shape_color(shape));
	else
	{
		printf("Invalid input\n");
		return (false);
	}
}

void	modify_cylinder_props(t_shape *shape)
{
	char	*input;

	do
	{
		printf(MODIF_CYLINDER);
		write(1, "Enter your command: ", 21);
		input = get_stdin();
	} while (!input_cylinder_menu(input, shape));
	free(input);
}
