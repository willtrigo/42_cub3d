/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:38:49 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/21 18:34:24 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collection/ft_arraylist.h"
#include "core/game.h"
#include "infrastructure/config/config.h"
#include "utils/output.h"
#include "utils/vec2.h"
#include <stdbool.h>
#include <stddef.h>

bool	get_player_pos(t_manager *manager, t_config_file *config, \
	size_t map_height);
void	player_init(t_player *player, char angle, int row, int col);
void	flood_fill(int x, int y, t_config_file *config, bool rot_state);
bool	check_elements(t_config_file *config, size_t map_height, bool valid);

bool	map_validation(\
	t_manager *manager, t_config_file *config, size_t map_height)
{
	if (!check_elements(config, map_height, false))
		return (logerr_ret("invalid elements of the map", false));
	if (!get_player_pos(manager, config, map_height))
		return (logerr_ret("invalid player", false));
	flood_fill((int)manager->player.loc.pos.x, \
			(int)manager->player.loc.pos.y, config, true);
	if (!check_elements(config, map_height, true))
		return (logerr_ret("invalid map, must be closed/surrounded by walls",
				false));
	flood_fill((int)manager->player.loc.pos.x, \
		(int)manager->player.loc.pos.y, config, false);
	return (true);
}

bool	check_elements(t_config_file *config, size_t map_height, bool valid)
{
	size_t	i;
	int		j;
	char	*ln;

	i = -1;
	while (++i < map_height)
	{
		ln = (char *)ft_arraylist_get(config->map, i);
		j = -1;
		while (ln[++j])
		{
			if (ln[j] == ' ' || ln[j] == '1' || ln[j] == '0' || ln[j] == 'N'
				|| ln[j] == 'W' || ln[j] == 'E' || ln[j] == 'S')
				continue ;
			if (valid && ln[j] == '3')
				continue ;
			return (false);
		}
	}
	return (true);
}

bool	get_player_pos(t_manager *manager, t_config_file \
	*config, size_t map_height)
{
	size_t	i;
	int		j;
	char	*ln;
	bool	set_pos;

	set_pos = false;
	i = -1;
	while (++i < map_height)
	{
		ln = (char *)ft_arraylist_get(config->map, i);
		j = -1;
		while (ln[++j])
		{
			if (ln[j] == 'N' || ln[j] == 'W' || ln[j] == 'E' || ln[j] == 'S')
			{
				if (set_pos || i == 0 || i == (map_height - 1)
					|| j == 0 || j == (config->map_width - 2))
					return (false);
				player_init(&manager->player, ln[j], i, j);
				ln[j] = '0';
				set_pos = true;
			}
		}
	}
	return (set_pos);
}

void	player_init(t_player *player, char angle, int row, int col)
{
	if (angle == 'N')
		player->loc.angle = ANGLE_NORTH;
	else if (angle == 'W')
		player->loc.angle = ANGLE_WEST;
	else if (angle == 'E')
		player->loc.angle = ANGLE_EAST;
	else if (angle == 'S')
		player->loc.angle = ANGLE_SOUTH;
	player->loc.pos = (t_vec2f){col + 0.5, row + 0.5};
}

void	flood_fill(int x, int y, t_config_file *config, bool rot_state)
{
	char	*map;

	if (x < 0 || y < 0 || x >= config->map_width - 1
		|| (size_t)y >= ft_arraylist_len(config->map))
		return ;
	map = ft_arraylist_get(config->map, y);
	if (rot_state && map[x] == '0')
	{
		map[x] += 3;
		flood_fill(x + 1, y, config, rot_state);
		flood_fill(x - 1, y, config, rot_state);
		flood_fill(x, y + 1, config, rot_state);
		flood_fill(x, y - 1, config, rot_state);
	}
	else if (rot_state && (map[x] != '1' && map[x] != '3'))
		map[x] = 'X';
	else if (!rot_state && map[x] == '3')
	{
		map[x] -= 3;
		flood_fill(x + 1, y, config, rot_state);
		flood_fill(x - 1, y, config, rot_state);
		flood_fill(x, y + 1, config, rot_state);
		flood_fill(x, y - 1, config, rot_state);
	}
}
