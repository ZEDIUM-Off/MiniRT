/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:01:16 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 18:35:36 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	modify_ckecker_scale(t_rt *rt)
{
	char	*input;

	do
	{
		write(1, "Enter the new scale: ", 21);
		input = get_stdin();
	} while (!is_float(input) && !is_in_range(input, 0, 64));
	rt->checker_scale = ft_atof(input);
	free(input);
	return (true);
}

bool	modify_sample(t_rt *rt)
{
	char	*input;

	do
	{
		write(1, "Enter the new sample: ", 22);
		input = get_stdin();
	} while (!is_float(input) && !is_in_range(input, 1, 1000));
	rt->samples = (size_t)ft_atof(input);
	free(input);
	return (true);
}

bool	modify_bg_color(t_rt *rt)
{
	char	*input;

	do
	{
		write(1, "Enter the new color: ", 22);
		input = get_stdin();
	} while (!is_color(input));
	parse_color(input, &rt->bg_color);
	gl_clear_color(&rt->glx, (float[4]){(float)rt->bg_color.r / 255.0f,
		(float)rt->bg_color.g / 255.0f, (float)rt->bg_color.b / 255.0f, 1.0f});
	free(input);
	return (true);
}

bool	modify_ambi_bright(t_rt *rt)
{
	char	*input;

	do
	{
		write(1, "Enter the new brightness: ", 27);
		input = get_stdin();
	} while (!is_float(input) && !is_in_range(input, 0, 1));
	rt->sc_input.a_light.ratio = ft_atof(input);
	free(input);
	return (true);
}

bool	input_scene_menu(t_rt *rt, char *input)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (modify_ambi_bright(rt));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (modify_ckecker_scale(rt));
	else if (ft_strncmp(input, "3", 2) == 0)
		return (modify_sample(rt));
	else if (ft_strncmp(input, "4", 2) == 0)
		return (modify_bg_color(rt));
	else if (ft_strncmp(input, "5", 2) == 0)
		return (modify_mesh_details(rt));
	else
	{
		printf("\nInvalid input\n");
		return (false);
	}
}
