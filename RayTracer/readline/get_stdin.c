/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stdin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchenava <mchenava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:50:09 by mchenava          #+#    #+#             */
/*   Updated: 2024/03/19 13:50:12 by mchenava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

char	*get_stdin(void)
{
	char	*input;
	int		i;

	input = get_next_line(STDIN_FILENO);
	i = 0;
	while (input[i] && input[i] != '\n')
		i++;
	input[i] = '\0';
	return (input);
}
