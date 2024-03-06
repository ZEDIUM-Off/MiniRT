/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:35:15 by agaley            #+#    #+#             */
/*   Updated: 2024/03/06 07:04:45 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_sc_input(t_rt *rt)
{
	rt->sc_input.shapes.spheres = NULL;
	rt->sc_input.shapes.planes = NULL;
	rt->sc_input.shapes.cylinders = NULL;
	rt->sc_input.shapes.cones = NULL;
	rt->sc_input.shapes.sp_count = 0;
	rt->sc_input.shapes.pl_count = 0;
	rt->sc_input.shapes.cy_count = 0;
	rt->sc_input.shapes.co_count = 0;
}

void	sc_input_free(t_rt *rt)
{
	if (rt->sc_input.shapes.spheres)
		free(rt->sc_input.shapes.spheres);
	if (rt->sc_input.shapes.planes)
		free(rt->sc_input.shapes.planes);
	if (rt->sc_input.shapes.planes)
		free(rt->sc_input.shapes.planes);
	if (rt->sc_input.shapes.cylinders)
		free(rt->sc_input.shapes.cylinders);
	if (rt->sc_input.shapes.cones)
		free(rt->sc_input.shapes.cones);
}

char	**parse_tokens(const char *str, const char delim,
		const size_t max_tokens)
{
	char	**tokens;
	size_t	nb;
	size_t	l;

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
	if (nb > 0)
	{
		nb = nb - 1;
		l = strlen(tokens[nb]) - 1;
		while ((tokens[nb][l] == ' ' || tokens[nb][l] == '\n'))
			tokens[nb][l--] = '\0';
	}
	return (tokens);
}

int	parse_color(const char *str, t_color *out_color)
{
	char	**tokens;
	size_t	i;
	int		color_values[3];

	tokens = parse_tokens(str, ',', 3);
	if (!tokens)
		return (0);
	if (!tokens[0] || !tokens[1] || !tokens[2])
		return (free_tokens(&tokens));
	i = -1;
	while (++i < 3)
	{
		color_values[i] = atoi(tokens[i]);
		if (color_values[i] < 0 || color_values[i] > 255)
			return (free_tokens(&tokens));
	}
	out_color->r = color_values[0];
	out_color->g = color_values[1];
	out_color->b = color_values[2];
	out_color->a = 255;
	free_tokens(&tokens);
	return (1);
}

int	parse_vector3(const char *str, t_vec3 *out_vec3)
{
	char	**tokens;
	size_t	i;

	tokens = parse_tokens(str, ',', 3);
	if (!tokens)
		return (0);
	out_vec3->x = ft_atof(tokens[0]);
	out_vec3->y = ft_atof(tokens[1]);
	out_vec3->z = ft_atof(tokens[2]);
	i = 0;
	while (i < 3)
		free(tokens[i++]);
	free(tokens);
	return (1);
}

int	free_tokens(char ***tokens)
{
	size_t	i;

	i = 0;
	if (tokens && *tokens)
	{
		while ((*tokens)[i])
		{
			free((*tokens)[i]);
			i++;
		}
		free(*tokens);
		*tokens = NULL;
	}
	return (0);
}
