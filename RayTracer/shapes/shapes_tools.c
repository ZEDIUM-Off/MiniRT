/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:25:02 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/04 13:49:30 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	expand_mesh(t_mesh *mesh)
{
	t_uint	i;

	i = 0;
	while (i < mesh->tris_count)
	{
		mesh->draw_verts = ft_realloc(mesh->draw_verts, (mesh->draw_count + 1)
				* sizeof(float) * 3, mesh->draw_count * sizeof(float) * 3);
		vec3_to_array(&(t_vec3){mesh->verts[mesh->tris[i * 3] * 3],
			mesh->verts[mesh->tris[i * 3] * 3 + 1], mesh->verts[mesh->tris[i
			* 3] * 3 + 2]}, mesh->draw_verts, mesh->draw_count++);
		i++;
	}
}
