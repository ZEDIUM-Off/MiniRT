/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:44:57 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/14 15:42:17 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "rt_types.h"

struct					s_camera
{
	t_vec3				pos;
	t_vec3				target;
	t_vec3				dir;
	t_vec3				up;
	t_vec3				right;
	float				speed;
	float				fov;
};

struct					s_mlx_env
{
	t_xvar				*mlx;
	t_win_list			*win;
	t_img				*img;
};

struct					s_uniforms
{
	t_mat4				mvp_mat;
	t_mat4				view;
	t_mat4				proj;
	t_vec3				near_point;
	t_vec3				far_point;
	float				grid_scale;
	size_t				max_depth;
	t_rt				*rt;
};

struct					s_viz_uniforms
{
	t_mat4				mvp_mat;
	t_mat4				view;
	t_mat4				proj;
	t_vec4				material;
	t_vec3				*cam_pos;
	t_sc_input			*sc_input;
};

struct					s_ctrl
{
	bool				rotate;
	bool				translate;
	t_vec2				mouse_pos;
};

struct					s_ambient_light
{
	float				ratio;
	t_color				color;
};

struct					s_spot_light
{
	t_vec3				position;
	float				brightness_ratio;
	t_color				color;
};


struct					s_sphere_props
{
	float				diameter;
};

struct					s_plane_props
{
	t_vec3				normal;
};

struct					s_cylinder
{
	float				diameter;
	float				height;
	t_vec3				axis;
};

struct					s_cone
{
	float				angle;
	float				height;
	t_vec3				axis;
};

struct					s_mesh
{
	t_uint				type;
	float				*verts;
	t_uint				verts_count;
	int					*tris;
	t_uint				tris_count;
	float				*draw_verts;
	t_uint				draw_count;
	float				*normals;
	t_uint				normals_count;
	float				*colors;
	t_uint				colors_count;
	t_gl_uint			tri_buffer;
	t_gl_uint			buffer;
	t_gl_uint			norm_buffer;
	t_gl_uint			color_buffer;
};

struct					s_shape
{
	t_shape_type		type;
	t_vec3				position;
	t_color				color;
	void				*properties;
	t_mesh				shape_mesh;
};

struct					s_scene_input
{
	t_a_light			a_light;
	t_shape				*shapes;
	size_t				shapes_count;
	t_s_light			*s_lights;
	size_t				s_lights_count;
	bool				has_cam_been_parsed;
	bool				has_a_light_been_parsed;
};

struct					s_plane_params
{
	t_mesh				*curr_mesh;
	t_vec3				center;
	t_vec3				normal;
	t_vec3				color;
};

struct					s_plane_vars
{
	int					verts_start;
	t_vec3				up;
	t_vec3				right;
	float				halph;
};

struct					s_sphere_params
{
	t_mesh				*curr_mesh;
	float				radius;
	size_t				slices;
	size_t				stacks;
	t_vec3				center;
	t_vec3				color;
};

struct					s_cylinder_params
{
	t_mesh				*curr_mesh;
	float				diameter;
	float				height;
	t_vec3				axis;
	t_vec3				center;
	t_vec3				color;
};

struct					s_cylinder_vars
{
	int					segments;
	float				radius;
	t_vec3				axis_normalized;
	t_vec3				perp_axis;
	t_vec3				perp_axis2;
	t_vec3				top_center;
	int					top_center_index;
	int					bottom_center_index;
	int					verts_start;
	int					tris_start;
	float				theta;
	t_vec3				top;
	t_vec3				bottom;
};

struct					s_cone_params
{
	t_mesh				*curr_mesh;
	float				angle;
	float				height;
	t_vec3				axis;
	t_vec3				center;
	t_vec3				color;
};

struct					s_cone_vars
{
	int					segments;
	float				radius;
	float				theta;
	int					verts_start;
	t_vec3				base;
};

struct					s_shpere_vars
{
	float				stack_step;
	float				slice_step;
	float				phi;
	float				theta;
	int					k1;
	int					k2;
	int					verts_start;
};

struct					s_scene
{
	t_mesh				*meshes;
	t_uint				mesh_count;
	// t_light* lights;
};

typedef struct s_fresnel
{
	float				cosi;
	float				etai;
	float				etat;
	float				sint;
	float				cost;
	float				rs;
	float				rp;
}						t_fresnel;

typedef struct s_triangle
{
	t_vec3				v0;
	t_vec3				v1;
	t_vec3				v2;
	t_color				color;
	// t_material			material;
}						t_triangle;

struct					s_hit
{
	// t_material	material;
	t_color				color;
	t_vec3				point;
	t_vec3				normal;
	float				distance;
};

enum					e_bump_map_mode
{
	NO_BUMP_MAP,
	ORANGE_PEEL,
};

struct					s_rt
{
	bool				is_mandatory;
	t_gl_context		glx;
	t_mlx_env			mxv;
	t_cam				cam;
	t_uniforms			uniforms;
	t_ctrl				ctrl;
	t_uint				loop;
	bool				modifying;
	t_uint				mode;
	t_gl_uint			shaders[MODE_MAX];
	char				*obj_types[5];
	t_mesh				all_meshes;
	t_sc_input			sc_input;
	t_intersect_func	intersect_shape[4];
	bool				checker_mode;
	float				checker_scale;
	t_bump_map_mode		bump_map_mode;
	char				*err_msg;
};

struct					s_obj
{
	t_uint				type;
	void				*data;
};

struct					s_ray
{
	t_vec3				ori;
	t_vec3				dir;
};

#endif
