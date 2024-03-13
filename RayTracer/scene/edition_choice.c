#include <minirt.h>

bool	translate_menu(t_rt *rt)
{
	t_obj	obj;

	do
	{
		printf(CHOOSE_ELEM, "translation");
		obj_menu(rt, &obj);
	} while (!translate_obj(&obj));
	return (true);
}

bool	rotate_menu(t_rt *rt)
{
	t_obj	obj;

	do
	{
		printf(CHOOSE_ELEM, "rotation");
		obj_menu(rt, &obj);
	} while (!rotate_obj(&obj));
	return (true);
}

bool	modify_props(t_rt *rt)
{
	t_obj	obj;

	do
	{
		printf(CHOOSE_ELEM, "properties");
		obj_menu(rt, &obj);
	} while (!modify_obj_props(&obj));
	return (true);
}

bool	input_fisrt_menu(t_rt *rt, char *input)
{
	if (ft_strncmp(input, "1", 2) == 0)
		return (translate_menu(rt));
	else if (ft_strncmp(input, "2", 2) == 0)
		return (rotate_menu(rt));
	else if (ft_strncmp(input, "3", 2) == 0)
		return (modify_props(rt));
	else if (ft_strncmp(input, "4", 2) == 0)
		return (true);
	else
	{
		printf("\nInvalid input\n");
		return (false);
	}
}
