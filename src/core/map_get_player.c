/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 00:53:12 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/22 01:52:29 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/game.h"
#include "infrastructure/config/config.h"
#include <stdbool.h>

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

bool	get_player_pos(t_manager *manager, t_config_file *config,
		size_t map_height)
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
