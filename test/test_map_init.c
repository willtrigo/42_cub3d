/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:04:30 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/11 17:05:26 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/config/config.h"
#include "ft_stdio.h"
#include "test_suite.h"
#include "core/game.h"
#include "core/game_init_internal.h"

void test_player_direction(void)
{
	ft_printf("\n%s: START\n", __FUNCTION__);
	{
		t_config_file	conf;
		config_init(1,
					(char *[]){ "./test/maps/trivial_player_north.cub", NULL},
					&conf);
		t_game game;
		map_init(&game, &conf);
		FT_TEST(game.player.angle == ANGLE_NORTH,
				"when filename == \"./test/maps/trivial_player_north.cub\" "
				"expected "
				"game.player.angle == ANGLE_NORTH");
		config_clean(&conf);
	}
	{
		t_config_file	conf;
		config_init(1,
					(char *[]){ "./test/maps/trivial_player_east.cub", NULL},
					&conf);
		t_game game;
		map_init(&game, &conf);
		FT_TEST(game.player.angle == ANGLE_EAST,
				"when filename == \"./test/maps/trivial_player_east.cub\" "
				"expected "
				"game.player.angle == ANGLE_EAST");
		config_clean(&conf);
	}
	{
		t_config_file	conf;
		config_init(1,
					(char *[]){ "./test/maps/trivial_player_south.cub", NULL},
					&conf);
		t_game game;
		map_init(&game, &conf);
		FT_TEST(game.player.angle == ANGLE_SOUTH,
				"when filename == \"./test/maps/trivial_player_south.cub\" "
				"expected "
				"game.player.angle == ANGLE_SOUTH");
		config_clean(&conf);
	}
	{
		t_config_file	conf;
		config_init(1,
					(char *[]){ "./test/maps/trivial_player_west.cub", NULL},
					&conf);
		t_game game;
		map_init(&game, &conf);
		FT_TEST(game.player.angle == ANGLE_WEST,
				"when filename == \"./test/maps/trivial_player_west.cub\" "
				"expected "
				"game.player.angle == ANGLE_WEST");
		config_clean(&conf);
	}
	ft_printf("%s: END\n", __FUNCTION__);
}

void test_map_init(void)
{
	ft_printf("\n%s: START", __FUNCTION__);

	//TODO: add tests for valid maps
	// test/maps/diamond.cub
	// test/maps/diamond_leftpad.cub
	// test/maps/diamond_trailing_spaces.cub

	test_player_direction();
	ft_printf("%s: END\n", __FUNCTION__);
}
