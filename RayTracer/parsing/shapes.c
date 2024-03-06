/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:53:38 by agaley            #+#    #+#             */
/*   Updated: 2024/03/06 06:45:22 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_and_add_shape(char **tokens, int num_tokens, t_rt *rt,
		const t_shape_parsers *parser)
{
	void	*shape;

	shape = malloc(parser->shape_size);
	if (!shape)
		return (handle_error(ERR_PARSE_SHAPE_REALLOC, rt));
	if (num_tokens != parser->expected_tokens)
	{
		free(shape);
		return (handle_error(parser->err_code, rt));
	}
	if (!parser->parse_func(tokens, shape, rt))
	{
		free(shape);
		return (0);
	}
	parser->add_func(rt, shape);
	free(shape);
	return (1);
}

int	parse_shape(char **tokens, int num_tokens, t_rt *rt)
{
	const t_shape_parsers	parsers[] = {{"sp", 4, (void *)parse_sphere,
		(void *)add_sphere, ERR_PARSE_SPHERE_ARGS, sizeof(t_sphere)}, {"pl",
		4, (void *)parse_plane, (void *)add_plane, ERR_PARSE_PLANE_ARGS,
		sizeof(t_plan)}, {"cy", 6, (void *)parse_cylinder,
		(void *)add_cylinder, ERR_PARSE_CYLINDER_ARGS, sizeof(t_cylinder)},
		{"co", 6, (void *)parse_cone, (void *)add_cone, ERR_PARSE_CONE_ARGS,
		sizeof(t_cone)}};
	int						i;

	i = 0;
	while (parsers[i].type != NULL)
	{
		if (strcmp(tokens[0], parsers[i].type) == 0)
		{
			return (parse_and_add_shape(tokens, num_tokens, rt, &parsers[i]));
		}
		i++;
	}
	return (handle_error(ERR_PARSE_SHAPE_UNKNOWN, rt));
}
