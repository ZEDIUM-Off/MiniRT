/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:44:57 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/07 16:55:52 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "rt_types.h"
// # include "scene_structs.h"

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
	t_gl_uint			tri_buffer;
	t_gl_uint			buffer;
	t_gl_uint			norm_buffer;
};

struct					s_plane_params
{
	t_mesh				*curr_mesh;
	t_vec3				corner;
	t_vec3				v1;
	t_vec3				v2;
	size_t				dim_v1;
	size_t				dim_v2;
	bool				tile;
};

struct					s_sphere_params
{
	t_mesh				*curr_mesh;
	float				radius;
	size_t				slices;
	size_t				stacks;
	t_vec3				center;
};

struct					s_cylinder_params
{
	t_mesh				*curr_mesh;
	float				diameter;
	float				height;
	t_vec3				axis;
	t_vec3				center;
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
	float				theta;
};

struct					s_cone_params
{
	t_mesh				*curr_mesh;
	float				angle;
	float				height;
	t_vec3				axis;
	t_vec3				center;
};

struct					s_cone_vars
{
	int					segments;
	float				radius;
	float				theta;
	t_vec3				top;
};

struct					s_shpere_vars
{
	float				stack_step;
	float				slice_step;
	float				phi;
	float				theta;
	int					k1;
	int					k2;
};

struct					s_scene
{
	t_mesh				*meshes;
	t_uint				mesh_count;
	// t_light* lights;
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

typedef enum e_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}						t_shape_type;

typedef struct s_sphere_props
{
	float				diameter;
}						t_sphere_props;

typedef struct s_plane_props
{
	t_vec3				normal;
}						t_plane_props;

typedef struct s_cylinder
{
	float				diameter;
	float				height;
	t_vec3				axis;
}						t_cylinder_props;

typedef struct s_cone
{
	float				angle;
	float				height;
	t_vec3				axis;
}						t_cone_props;

typedef union u_shape_props
{
	t_sphere_props		sphere;
	t_plane_props		plane;
	t_cylinder_props	cylinder;
	t_cone_props		cone;
}						t_shape_props;

struct					s_shape
{
	t_shape_type		type;
	t_vec3				position;
	void				*properties;
	t_color				color;
	t_mesh				shape_mesh;
};

struct					s_scene_input
{
	t_ambient_light		a_light;
	t_spot_light		s_light;
	t_shape				*shapes;
	size_t				shapes_count;
};

struct					s_rt
{
	t_gl_context		glx;
	t_mlx_env			mxv;
	t_cam				cam;
	t_viz_uniforms		uniforms;
	t_ctrl				ctrl;
	t_sc_input			sc_input;
	t_scene				scene;
	t_uint				loop;
	t_uint				mode;
	t_gl_uint			shaders[MODE_MAX];
	t_mesh				all_meshes;
	char				*err_msg;
};

#endif
