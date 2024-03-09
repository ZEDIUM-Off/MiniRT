#include <minirt.h>

bool	modify_obj_props(t_rt *rt, t_obj *obj)
{
	if (obj->type == LIGHT)
		modify_light_props(rt, (t_spot_light *)obj->data);
	else if (obj->type == SPHERE)
	{
		printf("You can't modify a sphere\n");
		return (false);
	}
	else
	{
		if (obj->type == PLANE)
			modify_plane_props(rt, (t_plane_props *)obj->data);
		else if (obj->type == CYLINDER)
			modify_cylinder_props(rt, (t_cylinder_props *)obj->data);
		else if (obj->type == CONE)
			modify_cone_props(rt, (t_cone_props *)obj->data);
	}
	return (true);
}