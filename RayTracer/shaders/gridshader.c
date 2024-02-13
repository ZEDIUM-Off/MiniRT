/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gridshader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:08:11 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/13 13:54:22 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	unproject_point(t_vec3 point, t_mat4 view, t_mat4 proj)
{
	t_mat4	inv_view;
	t_mat4	inv_proj;
	t_vec4	unprojected;

	mat4_inverse(inv_view, view);
	mat4_inverse(inv_proj, proj);
	unprojected = mult_mat4_vec4(inv_proj, (t_vec4){point.x, point.y, point.z, 1});
	unprojected = mult_mat4_vec4(inv_view, unprojected);
	return ((t_vec3){unprojected.x, unprojected.y, unprojected.z});
}

void	grid_vs(float *vs_output, void *vertex_attribs,
	t_shader_builtins *builtins, void *uniforms)
{
	t_uniforms	*u;
	t_vec4		*v_attribs;
	t_vec4		repeated_position;

	u = (t_uniforms *)uniforms;
	v_attribs = (t_vec4 *)vertex_attribs;
	repeated_position = v_attribs[0];
	((t_vec4 *)vs_output)[0] = v_attribs[4];
	repeated_position.x = fmod(repeated_position.x, 1.0) - 0.5;
	repeated_position.z = fmod(repeated_position.z, 1.0) - 0.5;
	mult_mat4_mat4(u->mvp_mat, u->proj, u->view);
	builtins->gl_position = mult_mat4_vec4(u->mvp_mat, repeated_position);
}

void	grid_fs(float *fs_input, t_shader_builtins *builtins, void *uniforms)
{
	(void)fs_input;
	(void)uniforms;
	float gridSize = 0.1; // Taille des cellules de la grille
	float lineWidth = 0.01; // Épaisseur des lignes de la grille
	t_vec4 position = builtins->gl_frag_coord; // Utilisez la position du fragment

	// Calcul pour déterminer si le fragment est proche d'une ligne de la grille
	bool isLine = fmod(position.x, gridSize) < lineWidth || fmod(position.y, gridSize) < lineWidth;

	if (isLine) {
		builtins->gl_frag_color = (t_vec4){1.0, 0.0, 0.0, 1.0}; // Couleur des lignes
	} else {
		builtins->gl_frag_color = (t_vec4){1.0, 0.0, 1.0, 1.0}; // Couleur des cellules
	}
}
