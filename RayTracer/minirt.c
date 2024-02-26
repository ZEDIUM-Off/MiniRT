/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:03:15 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/26 21:46:46 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main(int argc, char** argv)
{
	t_rt	rt;

	printf("running...");
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <scene_description_file.rt>\n", argv[0]);
		return EXIT_FAILURE;
	}
	// if (init_rt(&rt) != CONTINUE)
	// 	return (1);
	// Initialize the scene to zero
	if (!parse_read_file(argv[1], &rt))
		return (fprintf(stderr, "Error\nFailed to parse the scene file: %s\n", argv[1]), EXIT_FAILURE);
	printf("lauching loop...");
	// mlx_loop(rt.mxv.mlx);
	printf("exiting...");
}
