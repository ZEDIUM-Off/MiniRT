/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:53:39 by agaley            #+#    #+#             */
/*   Updated: 2024/03/09 17:02:35 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERRORS_H
# define PARSER_ERRORS_H

# define ERR_PARSE_FILE_EXT "Invalid file extension. Expected .rt"
# define ERR_PARSE_FILE_OPEN "Failed to open file"

# define ERR_PARSE_TOKENS "Failed to parse tokens"

# define ERR_PARSE_SHAPE_REALLOC "Error reallocating memory for shapes"
# define ERR_PARSE_SHAPE_UNKNOWN "Unknown shape type"

# define ERR_PARSE_AMBIENT_NONE "There should be one ambient light"
# define ERR_PARSE_AMBIENT_COUNT "Ambient light should be unique"
# define ERR_PARSE_AMBIENT_ARGS "Invalid number of args for ambient light"
# define ERR_PARSE_AMBIENT_RATIO "Ambient light ratio is invalid. Range [0,1]"
# define ERR_PARSE_AMBIENT_COLOR "Failed to parse ambient light color"

# define ERR_PARSE_SPOT_ARGS "Invalid number of arguments for a spot light"
# define ERR_PARSE_SPOT_COUNT "Only one spot light allowed in mandatory part"
# define ERR_PARSE_SPOT_REALLOC "Error reallocating memory for spot lights"
# define ERR_PARSE_SPOT_POS "Failed to parse spot light position"
# define ERR_PARSE_SPOT_BRIGHT "Spot light brightness is invalid : < 0"
# define ERR_PARSE_SPOT_COLOR "Failed to parse spot light color"

# define ERR_PARSE_CAM_NONE "We cannot render anything without camera"
# define ERR_PARSE_CAM_COUNT "Camera should be unique"
# define ERR_PARSE_CAM_ARGS "Invalid number of arguments for a camera"
# define ERR_PARSE_CAM_POS "Failed to parse camera position"
# define ERR_PARSE_CAM_DIR "Failed to parse camera direction"
# define ERR_PARSE_CAM_DIR_NORM "Camera direction should be normalized"
# define ERR_PARSE_CAM_FOV "Camera field of view is invalid. Range: ]0,180["

# define ERR_PARSE_SPHERE_ARGS "Invalid number of arguments for a sphere"
# define ERR_PARSE_SPHERE_POS "Failed to parse sphere position"
# define ERR_PARSE_SPHERE_INVALID_DIAM "Sphere diameter is invalid : < 0"
# define ERR_PARSE_SPHERE_COLOR "Failed to parse sphere color"

# define ERR_PARSE_PLANE_ARGS "Invalid number of arguments for a plane"
# define ERR_PARSE_PLANE_POS "Failed to parse plane position"
# define ERR_PARSE_PLANE_NORMAL "Failed to parse plane normal vector"
# define ERR_PARSE_PLANE_NORMAL_NORM "Plane normal vector should be normalized"
# define ERR_PARSE_PLANE_COLOR "Failed to parse plane color"

# define ERR_PARSE_CYLINDER_ARGS "Invalid number of arguments for a cylinder"
# define ERR_PARSE_CYLINDER_POS "Failed to parse cylinder position"
# define ERR_PARSE_CYLINDER_AXIS "Failed to parse cylinder axis vector"
# define ERR_PARSE_CYLINDER_AXIS_NORM "Cylinder axis should be normalized"
# define ERR_PARSE_CYLINDER_DIAM "Cylinder diameter is invalid : < 0"
# define ERR_PARSE_CYLINDER_HEIGHT "Cylinder height is invalid : < 0"
# define ERR_PARSE_CYLINDER_COLOR "Failed to parse cylinder color"

# define ERR_PARSE_CONE_ARGS "Invalid number of arguments for a cone"
# define ERR_PARSE_CONE_POS "Failed to parse cone position"
# define ERR_PARSE_CONE_AXIS "Failed to parse cone axis vector"
# define ERR_PARSE_CONE_AXIS_NORM "Cone axis vector should be normalized"
# define ERR_PARSE_CONE_ANGLE "Cone angle is invalid. Range: ]0,180["
# define ERR_PARSE_CONE_HEIGHT "Cone height is invalid : < 0"
# define ERR_PARSE_CONE_COLOR "Failed to parse cone color"

#endif
