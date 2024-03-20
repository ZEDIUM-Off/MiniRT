/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:48:36 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/20 11:57:13 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	modif_plane_normal(t_shape *shape)
{
	((t_plane_props *)shape->properties)->normal = get_axis("normal");
	return (true);
}

bool	input_plane_menu(char *input, t_shape *shape)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (modif_plane_normal(shape));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (modif_shape_color(shape));
	else
	{
		printf("Invalid input\n");
		return (false);
	}
}

void	modify_plane_props(t_shape *shape)
{
	char	*input;

	printf(MODIF_PLANE);
	write(1, "Enter your command: ", 21);
	input = get_stdin();
	while (!input_plane_menu(input, shape))
	{
		printf(MODIF_PLANE);
		write(1, "Enter your command: ", 21);
		input = get_stdin();
	}
	free(input);
}
