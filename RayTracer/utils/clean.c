/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:15:27 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/06 07:03:13 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_uint	clean_rt(t_rt *rt)
{
	mlx_destroy_image(rt->mxv.mlx, rt->mxv.img);
	mlx_destroy_window(rt->mxv.mlx, rt->mxv.win);
	mlx_destroy_display(rt->mxv.mlx);
	free(rt->mxv.mlx);
	if (rt->err_msg)
		free(rt->err_msg);
	sc_input_free(rt);
	return (CONTINUE);
}

int	quit_rt(void *rt)
{
	t_rt	*_rt;

	_rt = (t_rt *)rt;
	clean_rt(_rt);
	exit(0);
}
