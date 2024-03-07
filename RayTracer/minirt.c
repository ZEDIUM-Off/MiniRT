/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:03:15 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/07 02:23:56 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main(int argc, char **argv)
{
	t_rt	rt;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <scene_description_file.rt>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (init_rt(&rt) != CONTINUE)
		return (1);
	if (!parse_read_file(argv[1], &rt))
	{
		printf("Error\nFailed to parse the scene file: %s\n%s\n", argv[1],
			rt.err_msg);
		clean_rt(&rt);
		return (EXIT_FAILURE);
	}
	printf("Parsing done...");
	printf("lauching loop...");
	cam_proj(&rt, &rt.uniforms);
	gl_clear(&rt.glx, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	lgl_draw_frame(&rt.glx);
	mlx_put_image_to_window(rt.mxv.mlx, rt.mxv.win, rt.mxv.img, 0, 0);
	mlx_loop(rt.mxv.mlx);
	quit_rt(&rt);
	printf("exiting...");
}
