/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:19:31 by agaley            #+#    #+#             */
/*   Updated: 2024/03/04 03:00:40 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "parser_errors.h"
# include "scene_structs.h"

/**
 * Parses the scene description from a file.
 *
 * @param file_path The path to the .rt file containing the scene description.
 * @param rt A pointer to the rt structure.
 * @return 1 if the file is parsed and scene_input populated, 0 otherwise.
 */
int		parse_read_file(const char *file_path, t_rt *rt);

/**
 * Parses shape parameters from an array.format
format
 *
 * @param tokens The array containing the shape parameters.
 * @param num_tokens The number of tokens contained by the array.
 * @param rt A pointer to the rt structure.
 * @return 1 if the parameters were successfully parsed, 0 otherwise.
 */
int		parse_shape(char **tokens, int num_tokens, t_rt *rt);

/**
 * Parses a string representing a color in r,g,b.
 *
 * @param str The string to parse.
 * @param out_color Pointer to t_color where the color will be stored.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int		parse_color(const char *str, t_color *out_color);

/**
 * Parses a string representing a 3D vector or point in x,y,z.
 *
 * @param str The string to parse.
 * @param out_vec3 Pointer to t_vec3 where vector/point will be stored.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int		parse_vector3(const char *str, t_vec3 *out_vec3);

char	**ft_split(char const *str, char c);

double	ft_atof(const char *str);

char	**parse_tokens(const char *str, const char delim,
			const size_t max_tokens);

int		free_tokens(char ***tokens);

#endif
