/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:19:35 by agaley            #+#    #+#             */
/*   Updated: 2024/03/09 16:51:00 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Parses ambient light parameters from an array.
 *
 * @param tokens The array containing the ambient light parameters.
 * @param rt A pointer to the rt structure.
 * @return 1 if the parameters were successfully parsed, 0 otherwise.
 */
static int	parse_ambient_light(char **tokens, size_t nb, t_rt *rt)
{
	t_sc_input	*sc_input;

	if (nb != 3)
		return (handle_error(ERR_PARSE_AMBIENT_ARGS, rt));
	if (rt->sc_input.has_a_light_been_parsed)
		return (handle_error(ERR_PARSE_AMBIENT_COUNT, rt));
	sc_input = &rt->sc_input;
	sc_input->a_light.ratio = ft_atof(tokens[1]);
	if (sc_input->a_light.ratio < 0.0 || sc_input->a_light.ratio > 1.0)
		return (handle_error(ERR_PARSE_AMBIENT_RATIO, rt));
	if (!parse_color(tokens[2], &sc_input->a_light.color))
		return (handle_error(ERR_PARSE_AMBIENT_COLOR, rt));
	sc_input->has_a_light_been_parsed = true;
	return (1);
}

/**
 * Parses camera parameters from an array.
 *
 * @param tokens The array containing the camera parameters.
 * @param rt A pointer to the rt structure.
 * @return 1 if the parameters were successfully parsed, 0 otherwise.
 */
static int	parse_camera(char **tokens, size_t nb, t_rt *rt)
{
	t_cam	*camera;

	if (nb != 4)
		return (handle_error(ERR_PARSE_CAM_ARGS, rt));
	if (rt->sc_input.has_cam_been_parsed)
		return (handle_error(ERR_PARSE_CAM_COUNT, rt));
	camera = &rt->cam;
	if (!parse_vector3(tokens[1], &camera->pos))
		return (handle_error(ERR_PARSE_CAM_POS, rt));
	if (!parse_vector3(tokens[2], &camera->dir))
		return (handle_error(ERR_PARSE_CAM_DIR, rt));
	camera->fov = ft_atof(tokens[3]);
	if (camera->fov < 0.0 || camera->fov > 180.0)
		return (handle_error(ERR_PARSE_CAM_FOV, rt));
	camera->dir = norm_vec3(camera->dir);
	camera->target = add_vec3s(camera->pos, camera->dir);
	camera->right = norm_vec3(cross_product(camera->dir, (t_vec3){0, 1, 0}));
	camera->up = cross_product(camera->right, camera->dir);
	camera->speed = 0.001f;
	rt->cam = *camera;
	rt->sc_input.has_cam_been_parsed = true;
	return (1);
}

/**
 * Parses spot light parameters from an array.
 *
 * @param tokens The array containing the spot light parameters.
 * @param rt A pointer to the rt structure.
 * @return 1 if the parameters were successfully parsed, 0 otherwise.
 */
static int	parse_spot_light(char **tokens, size_t nb, t_rt *rt)
{
	t_s_light	*light;

	if (nb != 4)
		if (!rt->is_mandatory || (rt->is_mandatory && nb != 3))
			return (handle_error(ERR_PARSE_SPOT_ARGS, rt));
	if (rt->is_mandatory && rt->sc_input.s_lights_count > 0)
		return (handle_error(ERR_PARSE_SPOT_COUNT, rt));
	rt->sc_input.s_lights = realloc(rt->sc_input.s_lights,
			(rt->sc_input.s_lights_count + 1) * sizeof(t_s_light));
	if (!rt->sc_input.s_lights)
		return (handle_error(ERR_PARSE_SPOT_REALLOC, rt));
	light = &rt->sc_input.s_lights[rt->sc_input.s_lights_count];
	rt->sc_input.s_lights_count++;
	if (!parse_vector3(tokens[1], &light->position))
		return (handle_error(ERR_PARSE_SPOT_POS, rt));
	light->brightness_ratio = ft_atof(tokens[2]);
	if (light->brightness_ratio < 0.0 || light->brightness_ratio > 1.0)
		return (handle_error(ERR_PARSE_SPOT_BRIGHT, rt));
	if (rt->is_mandatory)
		light->color = (t_color){255, 255, 255, 255};
	else if (!parse_color(tokens[3], &light->color))
		return (handle_error(ERR_PARSE_SPOT_COLOR, rt));
	rt->sc_input.s_lights_count++;
	return (1);
}

static int	parse_element(char *line, t_rt *rt)
{
	char	**tokens;
	size_t	nb;
	int		result;

	tokens = parse_tokens(line, " \t\n\v\f\r", 10);
	if (!tokens)
		return (handle_error(ERR_PARSE_TOKENS, rt));
	nb = 0;
	while (tokens[nb])
		nb++;
	if (ft_strcmp(tokens[0], "A") == 0)
		result = parse_ambient_light(tokens, nb, rt);
	else if (ft_strcmp(tokens[0], "C") == 0)
		result = parse_camera(tokens, nb, rt);
	else if (ft_strcmp(tokens[0], "L") == 0)
		result = parse_spot_light(tokens, nb, rt);
	else
		result = parse_shape(tokens, nb, rt);
	free_tokens(&tokens);
	return (result);
}

int	parse_read_file(const char *file_path, t_rt *rt)
{
	int		fd;
	char	*line;
	size_t	path_len;

	path_len = ft_strlen(file_path);
	if (path_len < 3 || ft_strcmp(file_path + path_len - 3, ".rt") != 0)
		return (handle_error(ERR_PARSE_FILE_EXT, rt));
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (handle_error(ERR_PARSE_FILE_OPEN, rt));
	while (line)
	{
		line = get_next_line(fd);
		if (line && line[0] != '\n' && line[0] != '#' && !parse_element(line,
				rt))
			return (close(fd), free(line), 0);
		free(line);
	}
	if (rt->sc_input.has_cam_been_parsed == false)
		return (handle_error(ERR_PARSE_CAM_NONE, rt));
	if (rt->sc_input.has_a_light_been_parsed == false)
		return (handle_error(ERR_PARSE_AMBIENT_NONE, rt));
	return (close(fd), 1);
}
