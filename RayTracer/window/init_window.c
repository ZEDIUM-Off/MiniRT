/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:07:33 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/07 13:15:23 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_uint	init_window(t_rt* rt)
{
	printf("init window...\n");
	rt->mxv.mlx = mlx_init();
	if (!rt->mxv.mlx)
		return (MLX_INIT_ERR);
	printf("mlx inited...\n");
	rt->mxv.win = mlx_new_window(rt->mxv.mlx, WIDTH, HEIGHT, TITLE);
	if (!rt->mxv.win)
		return (MLX_INIT_ERR);
	printf("window inited...\n");
	rt->mxv.img = mlx_new_image(rt->mxv.mlx, WIDTH, HEIGHT);
	if (!rt->mxv.img)
		return (MLX_INIT_ERR);
	printf("img inited...\n");
	return (CONTINUE);
}
