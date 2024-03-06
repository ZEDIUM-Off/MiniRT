/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:19:31 by agaley            #+#    #+#             */
/*   Updated: 2024/03/06 07:05:03 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "parser_errors.h"
# include "scene_structs.h"

typedef int			(*t_parse_func)(char **, void *, t_rt *);
typedef int			(*t_add_func)(t_rt *, void *);

typedef struct s_shape_parsers
{
	const char		*type;
	int				expected_tokens;
	t_parse_func	parse_func;
	t_add_func		add_func;
	char			*err_code;
	size_t			shape_size;
}					t_shape_parsers;

void				init_sc_input(t_rt *rt);

/**
 * Parses the scene description from a file.
 *
 * @param file_path The path to the .rt file containing the scene description.
 * @param rt A pointer to the rt structure.
 * @return 1 if the file is parsed and scene_input populated, 0 otherwise.
 */
int					parse_read_file(const char *file_path, t_rt *rt);

// Shape parsers : parse a shape to prepare to add it to sc_input
int					parse_sphere(char **tokens, t_sphere *sphere, t_rt *rt);
int					parse_plane(char **tokens, t_plan *plane, t_rt *rt);
int					parse_cylinder(char **tokens, t_cylinder *cylinder,
						t_rt *rt);
int					parse_cone(char **tokens, t_cone *cone, t_rt *rt);

// Shape adders : add a shape to it's respective array in sc_input
int					add_sphere(t_rt *rt, t_sphere *sp);
int					add_plane(t_rt *rt, t_plan *plane);
int					add_cylinder(t_rt *rt, t_cylinder *cy);
int					add_cone(t_rt *rt, t_cone *cone);

/**
 * Parses shape parameters from an array.
 *
 * @param tokens The array containing the shape parameters.
 * @param num_tokens The number of tokens contained by the array.
 * @param rt A pointer to the rt structure.
 * @return 1 if the parameters were successfully parsed, 0 otherwise.
 */
int					parse_shape(char **tokens, int num_tokens, t_rt *rt);

/**
 * Parses a string representing a color in r,g,b.
 *
 * @param str The string to parse.
 * @param out_color Pointer to t_color where the color will be stored.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int					parse_color(const char *str, t_color *out_color);

/**
 * Parses a string representing a 3D vector or point in x,y,z.
 *
 * @param str The string to parse.
 * @param out_vec3 Pointer to t_vec3 where vector/point will be stored.
 * @return 1 if parsing is successful, 0 otherwise.
 */
int					parse_vector3(const char *str, t_vec3 *out_vec3);

char				**ft_split(char const *str, char c);

double				ft_atof(const char *str);

char				**parse_tokens(const char *str, const char delim,
						const size_t max_tokens);

int					free_tokens(char ***tokens);

void				sc_input_free(t_rt *rt);

#endif
