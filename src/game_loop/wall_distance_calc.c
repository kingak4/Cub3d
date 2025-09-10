#include "../../cub3d.h"

void	perp_wall_dis(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	if (ray->perp_wall_dist <= 0.1)
		data->cant_move_forward = 1;
	else
		data->cant_move_forward = 0;
}
