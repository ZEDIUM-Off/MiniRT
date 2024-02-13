/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:03:15 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/20 11:18:26 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main(int argc, char** argv)
{
	t_rt		rt;
	t_gl_uint	shader;

	(void)argc;
	(void)argv;
	printf("running...");
	if (init_rt(&rt) != CONTINUE)
		return (1);
	printf("grid initialized...");
	mlx_loop(rt.mxv.mlx);
	printf("exiting...");
}
