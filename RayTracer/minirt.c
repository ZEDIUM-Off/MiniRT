/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:03:15 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/04 17:02:40 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main(int argc, char **argv)
{
	t_rt	rt;

	(void)argc;
	(void)argv;
	// if (argc != 2)
	// {
	// 	fprintf(stderr, "Usage: %s <scene_description_file.rt>\n", argv[0]);
	// 	return (EXIT_FAILURE);
	// }
	if (init_rt(&rt) != CONTINUE)
		return (1);
	// if (!parse_read_file(argv[1], &rt))
	// {
	// 	printf("Error\nFailed to parse the scene file: %s\n%s\n", argv[1],
	// 		rt.err_msg);
	// 	clean_rt(&rt);
	// 	return (EXIT_FAILURE);
	// }
	printf("Parsing done...");
	printf("lauching loop...");
	mlx_loop(rt.mxv.mlx);
	quit_rt(&rt);
	printf("exiting...");
}
