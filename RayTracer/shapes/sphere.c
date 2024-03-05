/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:48:13 by  mchenava         #+#    #+#             */
/*   Updated: 2024/03/04 16:54:56 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// static void	init_sphere_vars(t_mesh *mesh, t_shpere_vars *vars,
// 		t_sphere_params *params)
// {
// 	vars->tot_verts = (params->stacks - 1) * params->slices + 2;
// 	vars->vert_start = mesh->verts_count;
// 	vars->tri_start = mesh->tris_count;
// 	vars->pole_top = vars->vert_start;
// 	vars->pole_bot = vars->vert_start + (params->stacks - 1) * params->slices
// 		+ 1;
// 	vars->offset = 0;
// }

// static void	push_verts(t_mesh *mesh, t_shpere_vars *vars,
// 		t_sphere_params *params)
// {
// 	t_uint	i;
// 	t_uint	j;

// 	mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + vars->tot_verts)
// 			* sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
// 	vec3_to_array(&(t_vec3){params->center.x, params->center.y + params->radius,
// 		params->center.z}, mesh->verts, mesh->verts_count++);
// 	i = 1;
// 	while (i < params->stacks)
// 	{
// 		vars->phi = M_PI * i++ / params->stacks;
// 		j = 0;
// 		while (j < params->slices)
// 		{
// 			vars->theta = 2 * M_PI * j++ / params->slices;
// 			vec3_to_array(&(t_vec3){params->center.x + params->radius
// 				* sinf(vars->phi) * cosf(vars->theta), params->center.y
// 				+ params->radius * cosf(vars->phi), params->center.z
// 				+ params->radius * sinf(vars->phi) * sinf(vars->theta)},
// 				mesh->verts, mesh->verts_count++);
// 		}
// 	}
// 	vec3_to_array(&(t_vec3){params->center.x, params->center.y - params->radius,
// 		params->center.z}, mesh->verts, mesh->verts_count++);
// }

void	make_sphere(t_mesh *mesh, t_sphere_params *params)
{
	// t_shpere_vars	vars;

	// init_sphere_vars(mesh, &vars, params);
	// push_verts(mesh, &vars, params);
	// printf("verts pushed\n");
	// sphere_push_tris(mesh, &vars, params);
	// printf("tris pushed\n");
	size_t vert_count = 0;
    size_t index_count = 0;
    float phi, theta;
    float x, y, z, xy;                              // Position en coordonnées sphériques
    // float nx, ny, nz, lengthInv = 1.0f / params->radius; // Normal
    // float s, t;                                     // Coordonnées de texture

    size_t stackCount = params->stacks;
    size_t sectorCount = params->slices;
    float stackStep = M_PI / stackCount;
    float sectorStep = 2 * M_PI / sectorCount;

    // Calcul des sommets
    for(size_t i = 0; i <= stackCount; ++i)
    {
        phi = M_PI / 2 - i * stackStep;            // Commence de pi/2 à -pi/2
        xy = params->radius * cosf(phi);             // Rayon du cercle à la hauteur phi
        z = params->radius * sinf(phi);              // Hauteur à partir du centre

        for(size_t j = 0; j <= sectorCount; ++j)
        {
            theta = j * sectorStep;           // Secteur

            x = xy * cosf(theta);             // Coordonnées X
            y = xy * sinf(theta);             // Coordonnées Y
            // nx = x * lengthInv;
            // ny = y * lengthInv;
            // nz = z * lengthInv;

            // s = (float)j / sectorCount;
            // t = (float)i / stackCount;

            t_vec3 vert_pos = {x + params->center.x, y + params->center.y, z + params->center.z};
            mesh->verts = ft_realloc(mesh->verts, (mesh->verts_count + 1) * sizeof(float) * 3, mesh->verts_count * sizeof(float) * 3);
            vec3_to_array(&vert_pos, mesh->verts, mesh->verts_count++);
            vert_count++;
        }
    }

    // Calcul des indices pour chaque triangle
    int k1, k2;
    for(size_t i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // Commencement du stack courant
        k2 = k1 + sectorCount + 1;      // Commencement du stack suivant

        for(size_t j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles par secteur, excluant les premiers et derniers stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 1) * sizeof(int) * 3, mesh->tris_count * sizeof(int) * 3);
                ivec3_to_array(&(t_ivec3){k1, k2, k1 + 1}, mesh->tris, mesh->tris_count++);
                index_count++;
            }

            // k1+1 => k2 => k2+1
            if(i != (stackCount-1))
            {
                mesh->tris = ft_realloc(mesh->tris, (mesh->tris_count + 1) * sizeof(int) * 3, mesh->tris_count * sizeof(int) * 3);
                ivec3_to_array(&(t_ivec3){k1 + 1, k2, k2 + 1}, mesh->tris, mesh->tris_count++);
                index_count++;
            }
        }
    }
	expand_mesh(mesh);
}
