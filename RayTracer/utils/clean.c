/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:15:27 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/07 14:16:34 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_uint	clean_rt(t_rt *rt)
{
	mlx_destroy_image(rt->mxv.mlx, rt->mxv.img);
	mlx_destroy_window(rt->mxv.mlx, rt->mxv.win);
	mlx_destroy_display(rt->mxv.mlx);
	free(rt->mxv.mlx);
	return (CONTINUE);
}

t_uint	quit_rt(t_rt *rt)
{
	clean_rt(rt);
	exit(0);
	return (CONTINUE);
}
