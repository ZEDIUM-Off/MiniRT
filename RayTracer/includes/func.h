/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:17:17 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/07 14:18:54 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

t_uint	init_rt(t_rt *rt);
t_uint	setup_gl_context(t_rt *rt);
t_uint	clean_rt(t_rt *rt);
t_uint	init_window(t_rt *rt);

int	quit_rt(void *rt);
void	set_hooks(t_rt	*rt);

#endif //FUNC_H