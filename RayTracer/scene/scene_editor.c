/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:47:26 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/20 03:11:14 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	get_user_input(t_rt *rt)
{
	char	*input;

	printf(FIRST_MENU);
	write(1, "Enter your command: ", 21);
	input = get_stdin();
	while (!input_first_menu(rt, input))
	{
		printf(FIRST_MENU);
		write(1, "Enter your command: ", 21);
		input = get_stdin();
	}
	free(input);
}

void	editor_menu(t_rt *rt)
{
	printf(RT_HEADER);
	printf(RT_MENU);
	get_user_input(rt);
	printf("Exiting editor.\n");
	update_scene(rt);
	if (rt->mode == MODE_RENDER)
		render_raytraced(rt, true);
}
