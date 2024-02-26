/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:19:35 by agaley            #+#    #+#             */
/*   Updated: 2024/02/26 21:34:02 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Parses ambient light parameters from an array.
 *
 * @param tokens The array containing the ambient light parameters.
 * @param ambient_light A pointer to the ambient light structure where the parsed data will be stored.
 * @return 1 if the parameters were successfully parsed, 0 otherwise.
 */
static int parse_ambient_light(char** tokens, t_sc_input* sc_input)
{
	sc_input->a_light.ratio = atof(tokens[1]);
	return parse_color(tokens[2], &sc_input->a_light.color);
}

/**
 * Parses camera parameters from an array.
 *
 * @param tokens The array containing the camera parameters.
 * @param camera A pointer to the camera structure where the parsed data will be stored.
 * @return 1 if the parameters were successfully parsed, 0 otherwise.
 */
static int parse_camera(char** tokens, t_cam* camera)
{
	if (!parse_vector3(tokens[1], &camera->pos))
		return (0);
	if (!parse_vector3(tokens[2], &camera->dir))
		return (0);
	camera->fov = atof(tokens[3]);
	return (1);
}

/**
 * Parses spot light parameters from an array.
 *
 * @param tokens The array containing the spot light parameters.
 * @param light A pointer to the spot light structure where the parsed data will be stored.
 * @return 1 if the parameters were successfully parsed, 0 otherwise.
 */
static int parse_spot_light(char** tokens, t_sc_input* sc_input)
{
	if (!parse_vector3(tokens[1], &sc_input->s_light.position))
		return (0);
	sc_input->s_light.brightness_ratio = atof(tokens[2]);
	return parse_color(tokens[3], &sc_input->s_light.color);
}

static int parse_element(char* line, t_rt* rt)
{
	char	**tokens;
	size_t	nb;

	tokens = parse_tokens(line, ' ', 10);
	if (!tokens)
		return (0);
	nb = 0;
	while (tokens[nb])
		nb++;
	if (strcmp(tokens[0], "A") == 0 && nb == 3)
		return (parse_ambient_light(tokens, &rt->sc_input));
	else if (strcmp(tokens[0], "C") == 0 && nb == 4)
		return (parse_camera(tokens, &rt->cam));
	else if (strcmp(tokens[0], "L") == 0 && nb == 4)
		return (parse_spot_light(tokens, &rt->sc_input));
	else
	{
		rt->sc_input.shapes = realloc(rt->sc_input.shapes,
			(rt->sc_input.shapes_count + 1) * sizeof(t_shape));
		if (!rt->sc_input.shapes)
			return (0);
		rt->sc_input.shapes_count++;
		return (parse_shape(tokens, nb,
			&rt->sc_input.shapes[rt->sc_input.shapes_count - 1]));
	}
}

int	parse_read_file(const char* file_path, t_rt* rt)
{
	FILE* file;
	char	line[1024];

	file = fopen(file_path, "r");
	if (!file)
		return (0);
	while (fgets(line, sizeof(line), file))
	{
		if (!parse_element(line, rt))
		{
			// free(&rt->sc_input.shapes);
			fclose(file);
			return (0);
		}
	}
	fclose(file);
	return (1);
}
