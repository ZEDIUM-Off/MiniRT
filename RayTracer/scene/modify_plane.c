#include <minirt.h>

bool	modif_plane_normal(t_shape *shape)
{
	((t_plane_props *)shape->properties)->normal = get_axis("normal");
	return (true);
}

bool	input_plane_menu(char *input, t_shape *shape)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (modif_plane_normal(shape));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (modif_shape_color(shape));
	else
	{
		printf("Invalid input\n");
		return (false);

	}
}

void	modify_plane_props(t_shape *shape)
{
	char	*input;

	do
	{
		printf(MODIF_PLANE);
		printf("Enter your command: ");
		input = get_next_line(STDIN_FILENO);
	} while (!input_plane_menu(input, shape));
}
