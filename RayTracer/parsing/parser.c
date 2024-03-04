/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:19:35 by agaley            #+#    #+#             */
/*   Updated: 2024/03/04 03:13:11 by agaley           ###   ########lyon.fr   */
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
static int parse_ambient_light(char** tokens, t_rt* rt)
{
	t_sc_input* sc_input;

	sc_input = &rt->sc_input;
	sc_input->a_light.ratio = ft_atof(tokens[1]);
	if (sc_input->a_light.ratio < 0 || sc_input->a_light.ratio > 1)
		return (handle_error(ERR_PARSE_AMBIENT_RATIO, rt));
	if (!parse_color(tokens[2], &sc_input->a_light.color))
		return (handle_error(ERR_PARSE_AMBIENT_COLOR, rt));
	return (1);
}

/**
 * Parses camera parameters from an array.
 *
 * @param tokens The array containing the camera parameters.
 * @param camera A pointer to the camera structure where the parsed data will be stored.
 * @return 1 if the parameters were successfully parsed, 0 otherwise.
 */
static int parse_camera(char** tokens, t_rt* rt)
{
	t_cam* camera;

	camera = &rt->cam;
	if (!parse_vector3(tokens[1], &camera->pos))
		return (handle_error(ERR_PARSE_CAM_POS, rt));
	if (!parse_vector3(tokens[2], &camera->dir))
		return (handle_error(ERR_PARSE_CAM_DIR, rt));
	camera->fov = ft_atof(tokens[3]);
	if (camera->fov < 0 || camera->fov > 180)
		return (handle_error(ERR_PARSE_CAM_FOV, rt));
	return (1);
}

/**
* Parses spot light parameters from an array.
*
* @param tokens The array containing the spot light parameters.
* @param light A pointer to the spot light structure where the parsed data will be stored.
* @return 1 if the parameters were successfully parsed, 0 otherwise.
*/
static int parse_spot_light(char** tokens, t_rt* rt)
{
	t_sc_input* sc_input;

	sc_input = &rt->sc_input;
	if (!parse_vector3(tokens[1], &sc_input->s_light.position))
		return (handle_error(ERR_PARSE_SPOT_POS, rt));
	sc_input->s_light.brightness_ratio = ft_atof(tokens[2]);
	if (sc_input->s_light.brightness_ratio < 0 || sc_input->s_light.brightness_ratio > 1)
		return (handle_error(ERR_PARSE_SPOT_BRIGHT, rt));
	if (!parse_color(tokens[3], &sc_input->s_light.color))
		return (handle_error(ERR_PARSE_SPOT_COLOR, rt));
	return (1);
}

static int parse_element(char* line, t_rt* rt)
{
	char** tokens;
	size_t nb;
	int result;

	tokens = parse_tokens(line, ' ', 10);
	if (!tokens)
		return (handle_error(ERR_PARSE_TOKENS, rt));
	nb = 0;
	while (tokens[nb])
		nb++;
	if (strcmp(tokens[0], "A") == 0 && nb == 3)
		result = parse_ambient_light(tokens, rt);
	else if (strcmp(tokens[0], "C") == 0 && nb == 4)
		result = parse_camera(tokens, rt);
	else if (strcmp(tokens[0], "L") == 0 && nb == 4)
		result = parse_spot_light(tokens, rt);
	else
		result = parse_shape(tokens, nb, rt);
	free_tokens(&tokens);
	return (result);
}

int	parse_read_file(const char* file_path, t_rt* rt)
{
	int fd;
	char* line;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (handle_error(ERR_PARSE_FILE_OPEN, rt));
	while (line)
	{
		line = get_next_line(fd);
		if (line && line[0] == '\n')
		{
			free(line);
			continue;
		}
		if (line && !parse_element(line, rt))
		{
			if (rt->sc_input.shapes)
				free(rt->sc_input.shapes);
			close(fd);
			free(line);
			return (0);
		}
		free(line);
	}
	close(fd);
	return (1);
}
