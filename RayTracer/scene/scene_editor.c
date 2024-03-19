/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:47:26 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 13:47:29 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	get_user_input(t_rt *rt)
{
	char	*input;

	do
	{
		printf(FIRST_MENU);
		write(1, "Enter your command: ", 21);
		input = get_stdin();
	} while (!input_fisrt_menu(rt, input));
	free(input);
}

void	editor_menu(t_rt *rt)
{
	printf(RT_HEADER);
	printf(RT_MENU);
	get_user_input(rt);
	printf("Exiting editor.\n");
	update_scene(rt);
}
