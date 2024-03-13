#include <minirt.h>

bool	is_number(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '-')
		i++;
	while (input[i] && input[i] != '\n')
	{
		if (!ft_isdigit(input[i]))
			return (printf("\n%s not a number.\n", input), false);
		i++;
	}
	return (true);
}
