/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:59:07 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/20 11:59:22 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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
