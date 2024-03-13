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
