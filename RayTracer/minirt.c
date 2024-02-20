/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:03:15 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/13 11:09:31 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main(int argc, char** argv)
{
	t_rt	rt;

	(void)argc;
	(void)argv;
	printf("running...");
	if (init_rt(&rt) != CONTINUE)
		return (1);
	printf("grid initialized...");
	mlx_loop(rt.mxv.mlx);
	printf("exiting...");
}
