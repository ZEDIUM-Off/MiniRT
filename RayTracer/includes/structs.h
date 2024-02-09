/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:44:57 by  mchenava         #+#    #+#             */
/*   Updated: 2024/02/09 12:46:24 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "types.h"


struct s_mlx_env
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_img		*img;
};

struct s_rt
{
	t_gl_context	glx;
	t_mlx_env		mxv;
	t_cam			*cam;
};

#endif