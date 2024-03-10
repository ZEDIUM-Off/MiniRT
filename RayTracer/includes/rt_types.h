/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:07:18 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/11 00:29:15 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPES_H
# define RT_TYPES_H

typedef unsigned int				t_uint;
typedef enum e_bump_map_mode		t_bump_map_mode;
typedef struct s_rt					t_rt;
typedef struct s_ray				t_ray;
typedef struct s_camera				t_cam;
typedef struct s_mlx_env			t_mlx_env;
typedef struct s_uniforms			t_uniforms;
typedef struct s_viz_uniforms		t_viz_uniforms;
typedef struct s_ctrl				t_ctrl;
typedef struct s_grid				t_grid;
typedef struct s_mesh				t_mesh;
typedef struct s_scene				t_scene;
typedef struct s_vert_attr			t_vert_attr;
typedef struct s_plane_params		t_plane_params;
typedef struct s_plane_vars			t_plane_vars;
typedef struct s_sphere_params		t_sphere_params;
typedef struct s_shpere_vars		t_shpere_vars;
typedef struct s_cylinder_params	t_cylinder_params;
typedef struct s_cylinder_vars		t_cylinder_vars;
typedef struct s_cone_params		t_cone_params;
typedef struct s_cone_vars			t_cone_vars;
typedef struct s_ambient_light		t_a_light;
typedef struct s_spot_light			t_s_light;
typedef enum e_shape_type			t_shape_type;
typedef struct s_sphere_props		t_sphere_props;
typedef struct s_plane_props		t_plane_props;
typedef struct s_cylinder			t_cylinder_props;
typedef struct s_cone				t_cone_props;
typedef struct s_shape				t_shape;
typedef struct s_scene_input		t_sc_input;
typedef struct s_hit				t_hit;
typedef struct s_ray				t_ray;

typedef bool						(*t_intersect_func)(t_ray *, t_shape *,
							t_hit *);

#endif
