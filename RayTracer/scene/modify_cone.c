/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:47:47 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 13:49:14 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	modif_cone_angle(t_shape *shape)
{
	char	*input;

	do
	{
		write(1, "Enter the new angle: ", 22);
		input = get_stdin();
	} while (!is_float(input) && !is_in_range(input, 0, 180));
	((t_cone_props *)shape->properties)->angle = ft_atof(input);
	free(input);
	return (true);
}

bool	modif_cone_height(t_shape *shape)
{
	char	*input;

	do
	{
		write(1, "Enter the new height: ", 23);
		input = get_stdin();
	} while (!is_float(input) && !is_in_range(input, 0, 1000));
	((t_cone_props *)shape->properties)->height = ft_atof(input);
	free(input);
	return (true);
}

bool	modif_cone_axis(t_shape *shape)
{
	((t_cone_props *)shape->properties)->axis = get_axis("direction");
	return (true);
}

bool	input_cone_menu(char *input, t_shape *shape)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (modif_cone_angle(shape));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (modif_cone_height(shape));
	else if (ft_strncmp(input, "3", 2) == 0)
		return (modif_cone_axis(shape));
	else if (ft_strncmp(input, "4", 2) == 0)
		return (modif_shape_color(shape));
	else
	{
		printf("Invalid input\n");
		return (false);
	}
}

void	modify_cone_props(t_shape *shape)
{
	char	*input;

	do
	{
		printf(MODIF_CONE);
		write(1, "Enter your command: ", 21);
		input = get_stdin();
	} while (!input_cone_menu(input, shape));
	free(input);
}
