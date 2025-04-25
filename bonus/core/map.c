/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:38:49 by dande-je          #+#    #+#             */
/*   Updated: 2025/04/22 18:24:13 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collection/ft_arraylist.h"
#include "core/game.h"
#include "infrastructure/config/config.h"
#include "utils/output.h"
#include <stdbool.h>
#include <stddef.h>
#include "core/map.h"

void	flood_fill(int x, int y, t_config_file *config, bool rot_state);
bool	check_elements(t_config_file *config, size_t map_height, bool valid);
void	check_border(int x, int y, t_config_file *config);
void	set_flood_fill(t_config_file *config, size_t map_height,
			bool rot_state);

bool	map_validation(\
	t_manager *manager, t_config_file *config, size_t map_height)
{
	if (!check_elements(config, map_height, false))
		return (logerr_ret("invalid elements of the map", false));
	if (!get_player_pos(manager, config, map_height))
		return (logerr_ret("invalid player", false));
	set_flood_fill(config, map_height, true);
	if (!check_elements(config, map_height, true))
		return (logerr_ret("invalid map, must be closed/surrounded by walls",
				false));
	set_flood_fill(config, map_height, false);
	return (true);
}

void	set_flood_fill(t_config_file *config, size_t map_height, bool rot_state)
{
	int		i;
	int		j;
	char	*ln;

	i = -1;
	while ((size_t)++i < map_height)
	{
		j = -1;
		ln = ft_arraylist_get(config->map, i);
		while (ln[++j])
		{
			if (rot_state && ln[j] == '0')
				flood_fill(j, i, config, rot_state);
			else if (!rot_state && ln[j] == '3')
				flood_fill(j, i, config, rot_state);
		}
	}
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
		check_border(x, y, config);
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

void	check_border(int x, int y, t_config_file *config)
{
	char	*map;

	map = ft_arraylist_get(config->map, y);
	if (x + 1 < config->map_width - 1)
		flood_fill(x + 1, y, config, true);
	else
		map[x] = 'X';
	if (x - 1 >= 0)
		flood_fill(x - 1, y, config, true);
	else
		map[x] = 'X';
	if ((size_t)(y + 1) < ft_arraylist_len(config->map))
		flood_fill(x, y + 1, config, true);
	else
		map[x] = 'X';
	if (y - 1 >= 0)
		flood_fill(x, y - 1, config, true);
	else
		map[x] = 'X';
}
