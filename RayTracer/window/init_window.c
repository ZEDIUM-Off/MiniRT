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

t_uint	init_window(t_rt *rt)
{
	rt->mxv.mlx = mlx_init();
	if (!rt->mxv.mlx)
		return (MLX_INIT_ERR);
	rt->mxv.win = mlx_new_window(rt->mxv.mlx, WIDTH, HEIGHT, TITLE);
	if (!rt->mxv.win)
		return (MLX_WIN_ERR);
	rt->mxv.img = mlx_new_image(rt->mxv.mlx, WIDTH, HEIGHT);
	if (!rt->mxv.img)
		return (MLX_IMG_ERR);
	return (CONTINUE);
}
