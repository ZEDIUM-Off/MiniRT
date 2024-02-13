/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:03:20 by agaley            #+#    #+#             */
/*   Updated: 2024/02/13 06:26:10 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3 trace_ray(t_vec3 origin, t_vec3 direction, int depth) {
    t_hit  hit;
    t_vec3      reflectionDirection;
    t_vec3      reflectionColor;
    float       fresnel_effect;
    t_vec3      finalColor;

    if (depth <= 0) {
        return COLOR_BLACK; // Base case for recursion: return black
    }
    if (intersect_scene(origin, direction, &hit)) {
        reflectionDirection = reflect_vector(direction, hit.normal);
        reflectionColor = trace_ray(hit.point, reflectionDirection, depth - 1);
        fresnel_effect = schlick_approximation(dot_vec3s(direction, hit.normal), hit.material.refraction_index);
        finalColor = mix_color(hit.material.diffuse, reflectionColor, fresnel_effect);
        return finalColor;
    }
    return COLOR_BG; // If no intersection, return background color
}

void rt_frag_shader() {
    t_vec3  ray_origin = {0.0, 0.0, 0.0}; // Camera position
    t_vec3  ray_direction = {0.0, 0.0, -1.0}; // Camera direction
    t_vec3  color;

    normalize_vec3(&ray_direction);
    color = trace_ray(ray_origin, ray_direction, MAX_DEPTH);
    printf("Color: R=%f, G=%f, B=%f\n", color.x, color.y, color.z);
    // Output the color
    // gl_FragColor = vec4(color, 1.0); // Assuming this is a fragment shader
}