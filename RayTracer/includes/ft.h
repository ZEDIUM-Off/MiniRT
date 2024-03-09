/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:36:39 by agaley            #+#    #+#             */
/*   Updated: 2024/03/09 16:16:04 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <stdlib.h>

double	ft_atof(const char *str);
int		ft_atoii(const char *str);
char	*ft_itoa(int nbr);

char	**fts_split(const char *str, const char *charset);

size_t	ft_strlen(const char *s);
size_t	ft_ustrlen(const unsigned char *s);

int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);

#endif
