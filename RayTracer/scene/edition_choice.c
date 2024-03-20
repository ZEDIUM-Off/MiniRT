/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition_choice.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:49:34 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/20 02:19:23 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	translate_menu(t_rt *rt)
{
	t_obj	obj;

	printf(CHOOSE_ELEM, "translation");
	obj_menu(rt, &obj);
	while (!translate_obj(&obj))
	{
		printf(CHOOSE_ELEM, "translation");
		obj_menu(rt, &obj);
	} 
	return (true);
}

bool	rotate_menu(t_rt *rt)
{
	t_obj	obj;


	printf(CHOOSE_ELEM, "rotation");
	obj_menu(rt, &obj);
	while (!rotate_obj(&obj))
	{
		printf(CHOOSE_ELEM, "rotation");
		obj_menu(rt, &obj);
	} 
	return (true);
}

bool	modify_props(t_rt *rt)
{
	t_obj	obj;

	printf(CHOOSE_ELEM, "properties");
	obj_menu(rt, &obj);
	while (!modify_obj_props(&obj))
	{
		printf(CHOOSE_ELEM, "properties");
		obj_menu(rt, &obj);
	}
	return (true);
}

bool	modify_scene(t_rt *rt)
{
	char	*input;

	printf(MODIFY_SCENE);
	write(1, "Enter your command: ", 21);
	input = get_stdin();
	while (!input_scene_menu(rt, input))
	{
		printf(MODIFY_SCENE);
		write(1, "Enter your command: ", 21);
		input = get_stdin();
	}
	free(input);
	return (true);
}

bool	input_first_menu(t_rt *rt, char *input)
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
