/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:35:15 by agaley            #+#    #+#             */
/*   Updated: 2024/03/14 00:07:15 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	process_sign(const char **str)
{
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	else if (**str == '+')
	{
		(*str)++;
	}
	return (1);
}

static double	process_integer(const char **str)
{
	double	result;

	result = 0.0;
	while (**str != '\0' && **str != '.')
	{
		if (**str >= '0' && **str <= '9')
		{
			result = result * 10.0 + (**str - '0');
			(*str)++;
		}
		else
			return (0.0);
	}
	return (result);
}

static double	process_fraction(const char **str)
{
	double	fraction;
	int		divisor;

	fraction = 0.0;
	divisor = 1;
	if (**str == '.')
	{
		(*str)++;
		while (**str != '\0')
		{
			if (**str >= '0' && **str <= '9')
			{
				fraction = fraction * 10.0 + (**str - '0');
				divisor *= 10;
				(*str)++;
			}
			else
				return (0.0);
		}
	}
	return (fraction / divisor);
}

double	ft_atof(const char *str)
{
	double	sign;
	double	result;
	double	fraction;

	sign = process_sign(&str);
	result = process_integer(&str);
	fraction = process_fraction(&str);
	return (sign * (result + fraction));
}
