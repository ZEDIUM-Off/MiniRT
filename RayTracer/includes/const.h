/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:21:00 by mchenava          #+#    #+#             */
/*   Updated: 2024/02/20 15:43:40 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H

# define WIDTH 800
# define HEIGHT 800

# define RED_MASK 0x00FF0000
# define GREEN_MASK 0x0000FF00
# define BLUE_MASK 0x000000FF
# define ALPHA_MASK 0xFF000000

# define TITLE "42LiteGL - RayTracer"

# define MESH_DETAIL 32
# define PLANE_SIZE 50
# define PLANE_DIV PLANE_SIZE / 5

# define RT_HEADER "\n\n" \
"                                                          ,----,\n" \
"        ,--,                                                    ,/   .`|\n" \
"      ,--.'|      ,----,  ,-.----.                            ,`   .'  :\n" \
"   ,--,  | :    .'   .' \\ \\    /  \\                         ;    ;     /\n" \
" ,---.'|  : '  ,----,'    |;   :    \\                      .'___,/    ,' __  ,-.                                __  ,-.\n" \
" ;   : |  | ;  |    :  .  ;|   | .\\ :                      |    :     |,' ,'/ /|                              ,' ,'/ /|\n" \
" |   | : _' |  ;    |.'  / .   : |: |   ,--.--.        .--,;    |.';  ;'  | |' | ,--.--.     ,---.     ,---.  '  | |' |\n" \
" :   : |.'  |  `----'/  ;  |   |  \\ :  /       \\     /_ ./|`----'  |  ||  |   ,'/       \\   /     \\   /     \\ |  |   ,'\n" \
" |   ' '  ; :    /  ;  /   |   : .  / .--.  .-. | , ' , ' :    '   :  ;'  :  / .--.  .-. | /    / '  /    /  |'  :  /\n" \
" \\   \\  .'. |   ;  /  /-,  ;   | |  \\  \\__\\/: . ./___/ \\: |    |   |  '|  | '   \\__\\/: . ..    ' /  .    ' / ||  | '\n" \
"  `---`:  | '  /  /  /.`|  |   | ;\\  \\ ,\" .--.; | .  \\  ' |    '   :  |;  : |   ,\" .--.; |'   ; :__ '   ;   /|;  : |\n" \
"       '  ; |./__;      :  :   ' | \\.'/  /  ,.  |  \\  ;   :    ;   |.' |  , ;  /  /  ,.  |'   | '.'|'   |  / ||  , ;\n" \
"       |  : ;|   :    .'   :   : :-' ;  :   .'   \\  \\  \\  ;    '---'    ---'  ;  :   .'   \\   :    :|   :    | ---'\n" \
"       '  ,/ ;   | .'      |   |.'   |  ,     .-./   :  \\  \\                  |  ,     .-./\\   \\  /  \\   \\  /\n" \
"       '--'  `---'         `---'      `--`---'        \\  ' ;                   `--`---'     `----'    `----'\n" \
"                                                       `--`\n\n"

# define RT_MENU "Welcome to the 42RayTracer!\n\n" \
"This is a simple raytracer that uses the 42LiteGL library to render the scene.\n" \
"The scene is defined in .rt file, which is parsed by the parser.\n" \
"you can edit objects of the scene throug this menue, as there scale, position, rotation, etc.\n"

# define FIRST_MENU "\n\nWhat would you like to do?\n" \
"* 1. TRANSLATE AN OBJECT/LIGHT\n" \
"* 2. ROTATE AN OBJECT\n" \
"* 3. MODIFY AN OBJECT PROPERTIE\n" \
"* 4. STOP MODIFYING\n"

# define CHOOSE_ELEM "\n\nOn which object would you apply a %s modification ?\n" 


#endif // CONST_H
