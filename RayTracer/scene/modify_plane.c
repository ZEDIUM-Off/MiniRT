#include <minirt.h>

bool	modif_plane_normal(t_rt *rt, t_shape *shape)
{
	((t_plane_props *)shape->properties)->normal = get_axis(rt, "normal");
	return (true);
}

bool	input_plane_menu(t_rt *rt, char *input, t_shape *shape)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (modif_plane_normal(rt, shape));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (modif_shape_color(rt, shape));
	else
	{
		printf("Invalid input\n");
		return (false);

	}
}

void	modify_plane_props(t_rt *rt, t_shape *shape)
{
	char	*input;

	do
	{
		printf(MODIF_PLANE);
		printf("Enter your command: ");
		input = get_next_line(STDIN_FILENO);
	} while (!input_plane_menu(rt, input, shape));
}
