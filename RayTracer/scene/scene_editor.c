#include <minirt.h>

static void	get_user_input(t_rt *rt)
{
	char	*input;

	do
	{
		printf(FIRST_MENU);
		write(1, "Enter your command: ", 20);
		input = get_next_line(STDIN_FILENO);
		printf("input: [%s]\n", input);
	} while (!input_fisrt_menu(rt, input));
}

void	editor_menu(t_rt *rt)
{
	printf(RT_HEADER);
	printf(RT_MENU);
	get_user_input(rt);
}
