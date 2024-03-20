/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:48:00 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/20 02:12:04 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	modif_light_brightness(t_s_light *light)
{
	char	*input;

	write(1, "Enter the new brightness: ", 27);
	input = get_stdin();
	while (!is_float(input) || !is_in_range(input, 0, 1))
	{
		write(1, "Enter the new brightness: ", 27);
		input = get_stdin();
	}
	light->brightness_ratio = ft_atof(input);
	free(input);
	return (true);
}

bool	modif_light_color(t_s_light *light)
{
	char	*input;

	write(1, "Enter the new color: ", 22);
	input = get_stdin();
	while (!is_color(input))
	{
		write(1, "Enter the new color: ", 22);
		input = get_stdin();
	}
	parse_color(input, &light->color);
	free(input);
	return (true);
}

bool	modif_light_radius(t_s_light *light)
{
	char	*input;

	write(1, "Enter the new radius: ", 23);
	input = get_stdin();
	while (!is_float(input))
	{
		write(1, "Enter the new radius: ", 23);
		input = get_stdin();
	}
	light->radius = ft_atof(input);
	free(input);
	return (true);
}

bool	input_light_menu(char *input, t_s_light *light)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (modif_light_brightness(light));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (modif_light_color(light));
	else if (ft_strncmp(input, "3", 2) == 0)
		return (modif_light_radius(light));
	else
	{
		printf("Invalid input\n");
		return (false);
	}
}

void	modify_light_props(t_s_light *light)
{
	char	*input;

	printf(MODIF_LIGHT);
	write(1, "Choose the property to modify: ", 31);
	input = get_stdin();
	while (!input_light_menu(input, light))
	{
		printf(MODIF_LIGHT);
		write(1, "Choose the property to modify: ", 31);
		input = get_stdin();
	}
	free(input);
}
