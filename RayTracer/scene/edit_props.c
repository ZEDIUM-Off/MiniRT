/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_props.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:42:16 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 13:46:40 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	modify_obj_props(t_obj *obj)
{
	if (obj->type == LIGHT)
		modify_light_props((t_s_light *)obj->data);
	else if (obj->type == SPHERE)
		modify_sphere_props((t_shape *)obj->data);
	else if (obj->type == PLANE)
		modify_plane_props((t_shape *)obj->data);
	else if (obj->type == CYLINDER)
		modify_cylinder_props((t_shape *)obj->data);
	else if (obj->type == CONE)
		modify_cone_props((t_shape *)obj->data);
	return (true);
}
