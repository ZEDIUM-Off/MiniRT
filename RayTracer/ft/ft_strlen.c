/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:07:46 by agaley            #+#    #+#             */
/*   Updated: 2024/03/09 14:49:05 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Calculates the length of a string.
 *
 * @param s The string whose length is to be computed.
 *
 * @returns The length of the string.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * Calculates the length of a string.
 *
 * @param s The string whose length is to be computed.
 *
 * @returns The length of the string.
 */
size_t	ft_ustrlen(const unsigned char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
