/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:15:27 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 16:23:02 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_shapes(t_rt *rt)
{
	t_uint	i;

	i = 0;
	while (i < rt->sc_input.shapes_count)
	{
		free(rt->sc_input.shapes[i].properties);
		i++;
	}
	free(rt->sc_input.shapes);
}

void	free_meshes(t_rt *rt)
{
	if (rt->all_meshes.verts)
		free(rt->all_meshes.verts);
	if (rt->all_meshes.tris)
		free(rt->all_meshes.tris);
	if (rt->all_meshes.colors)
		free(rt->all_meshes.colors);
}

t_uint	clean_rt(t_rt *rt)
{
	mlx_destroy_image(rt->mxv.mlx, rt->mxv.img);
	mlx_destroy_window(rt->mxv.mlx, rt->mxv.win);
	mlx_destroy_display(rt->mxv.mlx);
	free(rt->mxv.mlx);
	if (rt->err_msg)
		free(rt->err_msg);
	if (rt->sc_input.shapes)
		free_shapes(rt);
	if (rt->sc_input.s_lights)
		free(rt->sc_input.s_lights);
	free_meshes(rt);
	free_gl_context(&rt->glx);
	return (CONTINUE);
}

int	quit_rt(void *rt)
{
	t_rt	*_rt;

	_rt = (t_rt *)rt;
	clean_rt(_rt);
	exit(0);
}
