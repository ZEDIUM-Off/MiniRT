#include <minirt.h>

static void	get_user_input(t_rt *rt)
{
	char	*input;

	do
	{
		printf(FIRST_MENU);
		printf("Enter your command: ");
		input = get_next_line(STDIN_FILENO);
	} while (!input_fisrt_menu(rt, input));
}

void	editor_menu(t_rt *rt)
{
	printf(RT_HEADER);
	printf(RT_MENU);
	get_user_input(rt);
}