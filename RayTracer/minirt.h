/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:04:07 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/07 13:21:26 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <lite_gl.h>
# include "includes/rt_includes.h"

struct s_rt
{
	t_gl_context	glx;
	t_mlx_env		mxv;
	t_cam			*cam;
};

struct s_mlx_env
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_img		*img;
};

#endif