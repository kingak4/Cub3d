#include "../../cub3d.h"

int	is_no(char *line)
{
	return (check_prefix(line, "NO "));
}

int	is_so(char *line)
{
	return (check_prefix(line, "SO "));
}

int	is_we(char *line)
{
	return (check_prefix(line, "WE "));
}

int	is_ea(char *line)
{
	return (check_prefix(line, "EA "));
}

int	is_floor(char *line)
{
	return (check_prefix(line, "F "));
}
