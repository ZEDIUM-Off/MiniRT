/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition_choice.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:49:34 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 18:32:34 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	translate_menu(t_rt *rt)
{
	t_obj	obj;

	do
	{
		printf(CHOOSE_ELEM, "translation");
		obj_menu(rt, &obj);
	} while (!translate_obj(&obj));
	return (true);
}

bool	rotate_menu(t_rt *rt)
{
	t_obj	obj;

	do
	{
		printf(CHOOSE_ELEM, "rotation");
		obj_menu(rt, &obj);
	} while (!rotate_obj(&obj));
	return (true);
}

bool	modify_props(t_rt *rt)
{
	t_obj	obj;

	do
	{
		printf(CHOOSE_ELEM, "properties");
		obj_menu(rt, &obj);
	} while (!modify_obj_props(&obj));
	return (true);
}

bool	modify_scene(t_rt *rt)
{
	char	*input;

	do
	{
		printf(MODIFY_SCENE);
		write(1, "Enter your command: ", 21);
		input = get_stdin();
	} while (!input_scene_menu(rt, input));
	free(input);
	return (true);
}

bool	input_fisrt_menu(t_rt *rt, char *input)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (translate_menu(rt));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (rotate_menu(rt));
	else if (ft_strncmp(input, "3", 2) == 0)
		return (modify_props(rt));
	else if (ft_strncmp(input, "4", 2) == 0)
		return (modify_scene(rt));
	else if (ft_strncmp(input, "5", 2) == 0)
		return (true);
	else
	{
		printf("\nInvalid input\n");
		return (false);
	}
}