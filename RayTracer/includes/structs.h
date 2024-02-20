/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:44:57 by  mchenava         #+#    #+#             */
/*   Updated: 2024/02/13 12:46:52 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "rt_types.h"

struct	s_camera
{
	t_vec3	pos;
	t_vec3	target;
	t_vec3	dir;
	t_vec3	up;
	t_vec3	right;
	float	speed;
	float	fov;
};

struct s_mlx_env
{
	t_xvar* mlx;
	t_win_list* win;
	t_img* img;
};

struct s_uniforms
{
	t_mat4	mvp_mat;
	t_mat4	view;
	t_mat4	proj;
	t_vec3	near_point;
	t_vec3	far_point;
	float	grid_scale;
};

struct	s_ctrl
{
	bool	rotate;
	bool	translate;
	t_vec2	mouse_pos;
};

struct s_grid
{
	float		verts[8];
	t_uint		verts_count;
	t_uint		indices[6];
	t_uint		id_count;
	t_gl_uint	vao;
	t_gl_uint	vbo;
	t_gl_uint	ebo;
};


struct s_rt
{
	t_gl_context	glx;
	t_mlx_env		mxv;
	t_cam			cam;
	t_uniforms		uniforms;
	t_ctrl			ctrl;
	t_grid			grid;
};

#endif
