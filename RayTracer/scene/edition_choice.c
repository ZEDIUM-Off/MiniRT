#include <minirt.h>

bool	translate_menu(t_rt *rt)
{
	char	*input;
	bool	ret;
	t_obj	obj;

	do
	{
		printf(CHOOSE_ELEM, "translation");
		obj_menu(rt, &obj);
		ret = tramslate_obj(rt, &obj);
	} while (!ret);
}

bool	rotate_menu(t_rt *rt)
{
	char	*input;
	bool	ret;
	t_obj	obj;

	do
	{
		printf(CHOOSE_ELEM, "rotation");
		obj_menu(rt, &obj);
		ret = rotate_obj(rt, &obj);
	} while (!ret);
}

bool	modify_props(t_rt *rt)
{
	char	*input;
	bool	ret;
	t_obj	obj;

	do
	{
		printf(CHOOSE_ELEM, "properties");
		obj_menu(rt, &obj);
		ret = modify_obj_props(rt, &obj);
	} while (!ret);
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
		printf("Invalid input\n");
		return (false);
	}
}