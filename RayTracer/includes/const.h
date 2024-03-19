/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:21:00 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 18:24:25 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H

# define WIDTH 1280
# define HEIGHT 720

# define RED_MASK 0x00FF0000
# define GREEN_MASK 0x0000FF00
# define BLUE_MASK 0x000000FF
# define ALPHA_MASK 0xFF000000

# define TITLE "42LiteGL - RayTracer"

# define MESH_DETAIL 32
# define PLANE_SIZE 50

# ifdef BONUS
#  define MANDATORY false
# else
#  define MANDATORY true
# endif

# define RT_HEADER "\n\n" \
"                                                                   ,----,\n" \
"         ,--,                                                    ,/   .`|\n" \
"       ,--.'|      ,----,    .----.                            ,`   .'  :\n" \
"   ,--,   | :    .'   .' \\  /   /  \\                         ;    ;    /\n" \
" ,---.'|  : '  ,----,'    |;   :    \\                      .'___,/    ,' __ " \
" ,-.                                __  ,-.\n" \
" ;   : |  | ;  |    :  .  ;|   | .\\ :                      |    :     |,'"\
" ,'/ /|                              ,' ,'/ /|\n" \
" |   | : _' |  ;    |.'  / .   : |: |   ,--.--.        .--,;    |.';  ;'  | "\
"|' | ,--.--.     ,---.     ,---.  '  | |' |\n" \
" :   : |.'  |  `----'/  ;  |   |  \\ :  /       \\     /_ ./|`----'  |  ||  |"\
"   ,'/       \\   /     \\   /     \\ |  |   ,'\n" \
" |   ' '  ; :    /  ;  /   |   : .  / .--.  .-. | , ' , ' :    '   :  ;'  :  /"\
" .--.  .-. | /    / '  /    /  |'  :  /\n" \
" \\   \\  .'. |   ;  /  /-,  ;   | |  \\  \\__\\/: . ./___/ \\: |    |   |"\
"  '|  | '   \\__\\/: . ..    ' /  .    ' / ||  | '\n" \
"  `---`:  | '  /  /  /.`|  |   | ;\\  \\ ,\" .--.; | .  \\  ' |    '   :  |"\
";  : |   ,\" .--.; |'   ; :__ '   ;   /|;  : |\n" \
"       '  ; |./__;      :  :   ' | \\.'/  /  ,.  |  \\  ;   :    ;   |.' |"\
"  , ;  /  /  ,.  |'   | '.'|'   |  / ||  , ;\n" \
"       |  : ;|   :    .'   :   : :-' ;  :   .'   \\  \\  \\  ;    '---'"\
"    ---'  ;  :   .'   \\   :    :|   :    | ---'\n" \
"       '  ,/ ;   | .'      |   |.'   |  ,     .-./   :  \\  \\         "\
"         |  ,     .-./\\   \\  /  \\   \\  /\n" \
"       '--'  `---'         `---'      `--`---'        \\  ' ;       "\
"            `--`---'     `----'    `----'\n" \
"                                                       `--`\n\n"

# define RT_MENU                                                           \
	"Welcome to the 42RayTracer!\n\n"                                     \
	"This is a simple raytracer that uses the 42LiteGL library to render" \
	"the scene.\n"                                                        \
	"The scene is defined in .rt file, which is parsed by the parser.\n"  \
	"you can edit objects of the scene throug this menue, as there scale" \
	", position, rotation, etc.\n"

# define FIRST_MENU                      \
	"\n\nWhat would you like to do?\n"  \
	"* 1. TRANSLATE AN OBJECT/LIGHT\n"  \
	"* 2. ROTATE AN OBJECT\n"           \
	"* 3. MODIFY AN OBJECT PROPERTIE\n" \
	"* 4. MODIFY SCENE PROPERTIES\n"     \
	"* 5. STOP MODIFYING\n"

# define CHOOSE_ELEM "\n\nOn which object would you apply a %s modification ?\n"

# define MODIFY_SCENE								  \
	"\n\nWhat would you like to do?\n"               \
	"* 1. MODIFY AMBIENT LIGHT BRIGTNESS\n"          \
	"* 2. MODIFY CHECKERBOARD SCALE\n"                \
	"* 3. MODIFY SAMPLE/PIXEL (precision of the tracing)\n" \
	"* 4. MODIFY BACKGROUND COLOR\n"                 \
	"* 5. MODIFY MESH DETAIL\n"                      \

# define MODIF_LIGHT                                   \
	"\n\nWhich propertie would you like to modify?\n" \
	"* 1. BRIGTNESS\n"                                \
	"* 2. COLOR\n"                                    \
	"* 3. RADIUS\n"

# define MODIF_SPHERE                                  \
	"\n\nWhich propertie would you like to modify?\n" \
	"* 1. DIAMETER\n"                                 \
	"* 2. COLOR\n"

# define MODIF_PLANE                                   \
	"\n\nWhich propertie would you like to modify?\n" \
	"* 1. NORMAL\n"                                   \
	"* 2. COLOR\n"

# define MODIF_CYLINDER                                \
	"\n\nWhich propertie would you like to modify?\n" \
	"* 1. DIAMETER\n"                                 \
	"* 2. HEIGHT\n"                                   \
	"* 3. AXIS\n"                                     \
	"* 4. COLOR\n"

# define MODIF_CONE                                    \
	"\n\nWhich propertie would you like to modify?\n" \
	"* 1. ANGLE\n"                                    \
	"* 2. HEIGHT\n"                                   \
	"* 3. AXIS\n"                                     \
	"* 4. COLOR\n"
#endif // CONST_H
