/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:44:57 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/04 02:02:56 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "rt_types.h"
# include "scene_structs.h"

struct				s_camera
{
	t_vec3			pos;
	t_vec3			target;
	t_vec3			dir;
	t_vec3			up;
	t_vec3			right;
	float			speed;
	float			fov;
};

struct				s_mlx_env
{
	t_xvar			*mlx;
	t_win_list		*win;
	t_img			*img;
};

struct				s_uniforms
{
	t_mat4			mvp_mat;
	t_mat4			view;
	t_mat4			proj;
	t_vec3			near_point;
	t_vec3			far_point;
	float			grid_scale;
};

struct				s_ctrl
{
	bool			rotate;
	bool			translate;
	t_vec2			mouse_pos;
};

struct				s_grid
{
	float			verts[8];
	t_uint			verts_count;
	t_uint			indices[6];
	t_uint			id_count;
	t_gl_uint		vao;
	t_gl_uint		vbo;
	t_gl_uint		ebo;
};

struct				s_vert_attr
{
	t_vec3			pos;
	t_vec3			normal;
};

struct				s_mesh
{
	t_uint			type;
	float			*verts;
	t_uint			verts_count;
	int				*tris;
	t_uint			tris_count;
	float			*tex;
	t_uint			tex_count;
	float			*draw_verts;
	t_uint			draw_count;
	t_gl_uint		tri_buffer;
	t_gl_uint		buffer;
};

struct				s_plane_params
{
	t_mesh			*curr_mesh;
	t_vec3			corner;
	t_vec3			v1;
	t_vec3			v2;
	size_t			dim_v1;
	size_t			dim_v2;
	bool			tile;
};

struct				s_sphere_params
{
	t_mesh			*curr_mesh;
	float			radius;
	size_t			slices;
	size_t			stacks;
	t_vec3			center;
};

struct				s_shpere_vars
{
	float			down;
	float			around;
	t_mat3			rotdown;
	t_mat3			rotaround;
	t_uint			vert_start;
	t_uint			tri_start;
	t_vec3			point;
	t_vec3			tmp;
};

struct				s_scene
{
	t_mesh			*meshes;
	t_uint			mesh_count;
	// t_light* lights;
};

struct				s_rt
{
	t_gl_context	glx;
	t_mlx_env		mxv;
	t_cam			cam;
	t_uniforms		uniforms;
	t_ctrl			ctrl;
	t_sc_input		sc_input;
	t_scene			scene;
	t_uint			loop;
	char			*err_msg;
};

#endif
