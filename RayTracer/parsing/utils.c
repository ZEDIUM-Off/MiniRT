/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:35:15 by agaley            #+#    #+#             */
/*   Updated: 2024/02/26 21:35:29 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char **parse_tokens(const char *str, const char delim, const size_t max_tokens)
{
	char	**tokens;
	size_t	nb;

	nb = 0;
	tokens = ft_split(str, delim);
	if (!tokens)
		return (0);
	while (tokens[nb])
		nb++;
	if (nb > max_tokens)
	{
		while (nb--)
			free(tokens[nb]);
		return (free(tokens), NULL);
	}
	return (tokens);
}

int	parse_color(const char *str, t_color *out_color)
{
	char	**tokens;
	size_t	i;

	tokens = parse_tokens(str, ',', 3);
	if (!tokens)
		return (0);
	out_color->r = atoi(tokens[0]);
	out_color->g = atoi(tokens[1]);
	out_color->b = atoi(tokens[2]);
	i = 0;
	while (i < 3)
		free(tokens[i++]);
	// Check reverse if atoi worked
	return (1);
}

int	parse_vector3(const char *str, t_vec3 *out_vec3)
{
	char	**tokens;
	size_t	i;

	tokens = parse_tokens(str, ',', 3);
	if (!tokens)
		return (0);
	out_vec3->x = atof(tokens[0]);
	out_vec3->y = atof(tokens[1]);
	out_vec3->z = atof(tokens[2]);
	i = 0;
	while (i < 3)
		free(tokens[i++]);
	// Check reverse if atof worked
	return (1);
}
