/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_config_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:25:21 by maurodri          #+#    #+#             */
/*   Updated: 2025/04/09 22:43:52 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collection/ft_arraylist.h"
#include "ft_string.h"
#include "infrastructure/config/config.h"
#include "ft_stdio.h"
#include "test_suite.h"

void test_config_init_valid_trivial_map(void)
{
	ft_printf("\n%s: START\n", __FUNCTION__);

	t_config_file	conf;
	int				result = \
		config_init(1,
					(char *[]){ "./test/maps/trivial.cub", NULL},
					&conf);
	FT_TEST(result == true,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected return to be true");
	FT_TEST(conf.floor.value == 0xDC6400FF,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected conf.floor.value == 0xDC6400FF");
	FT_TEST(conf.ceil.value == 0xE11E00FF,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected conf.ceil.value == 0xE11E00FF");
	FT_TEST(conf.texture_north != NULL,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected conf.texture_north != NULL");
	FT_TEST(conf.texture_east != NULL,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected conf.texture_east != NULL");
	FT_TEST(conf.texture_south != NULL,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected conf.texture_south != NULL");
	FT_TEST(conf.texture_west != NULL,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected conf.texture_west != NULL");
	FT_TEST(conf.texture_north != NULL \
			&& ft_strncmp(conf.texture_north,
						  "./path_to_the_north_texture",
						  sizeof("./path_to_the_north_texture")) == 0,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected "
			"conf.texture_north == \"./path_to_the_north_texture\"");
	FT_TEST(conf.texture_east != NULL \
			&& ft_strncmp(conf.texture_east,
						  "./path_to_the_east_texture",
						  sizeof("./path_to_the_east_texture")) == 0,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected "
			"conf.texture_east == \"./path_to_the_east_texture\"");
	FT_TEST(conf.texture_south != NULL \
			&& ft_strncmp(conf.texture_south,
						  "./path_to_the_south_texture",
						  sizeof("./path_to_the_south_texture")) == 0,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected "
			"conf.texture_south == \"./path_to_the_south_texture\"");
	FT_TEST(conf.texture_west != NULL \
			&& ft_strncmp(conf.texture_west,
						  "./path_to_the_west_texture",
						  sizeof("./path_to_the_west_texture")) == 0,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected "
			"conf.texture_west == \"./path_to_the_west_texture\"");
	FT_TEST(conf.map != NULL,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected "
			"conf.map != NULL");
	FT_TEST(conf.map != NULL && ft_arraylist_len(conf.map) == 5,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected "
			"conf.map length == 5");
	FT_TEST(conf.map != NULL \
		&& ft_arraylist_len(conf.map) == 5 \
		&& ft_strncmp(ft_arraylist_get(conf.map, 0), "11111", sizeof("11111")) \
				== 0,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected "
			"conf.map [0] == \"11111\"");
	FT_TEST(conf.map != NULL \
		&& ft_arraylist_len(conf.map) == 5 \
		&& ft_strncmp(ft_arraylist_get(conf.map, 1), "10001", sizeof("10001")) \
				== 0,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected "
			"conf.map [1] == \"10001\"");
	FT_TEST(conf.map != NULL \
		&& ft_arraylist_len(conf.map) == 5 \
		&& ft_strncmp(ft_arraylist_get(conf.map, 2), "10N01", sizeof("10N01")) \
				== 0,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected "
			"conf.map [2] == \"10N01\"");
	FT_TEST(conf.map != NULL \
		&& ft_arraylist_len(conf.map) == 5 \
		&& ft_strncmp(ft_arraylist_get(conf.map, 3), "10001", sizeof("10001")) \
				== 0,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected "
			"conf.map [3] == \"10001\"");
	FT_TEST(conf.map != NULL \
		&& ft_arraylist_len(conf.map) == 5 \
		&& ft_strncmp(ft_arraylist_get(conf.map, 4), "11111", sizeof("11111")) \
				== 0,
			"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
			"and the file exists expected "
			"conf.map [4] == \"11111\"");
	config_clean(&conf);
	ft_printf("%s: END\n", __FUNCTION__);
}

void test_config_init_valid_random_order(void)
{
	ft_printf("\n%s: START\n", __FUNCTION__);

	{
		t_config_file	conf;
		int				result = \
			config_init(1,
						(char *[]){ "./test/maps/random_order.cub", NULL},
						&conf);
		FT_TEST(result == true,
				"when argc == 1 and filename == \"./test/maps/random_order.cub\" "
				"and the file exists expected return to be true");
		config_clean(&conf);
	}
	{
		t_config_file	conf;
		int				result = \
			config_init(1,
						(char *[]){ "./test/maps/random_order_no_empty_lines.cub", NULL},
						&conf);
		FT_TEST(result == true,
				"when argc == 1 and filename == \"./test/maps/random_order_no_empty_lines.cub\" "
				"and the file exists expected return to be true");
		config_clean(&conf);
	}
	{
		t_config_file	conf;
		int				result = \
			config_init(1,
						(char *[]){ "./test/maps/random_order_multiple_spaces.cub", NULL},
						&conf);
		FT_TEST(result == true,
				"when argc == 1 and filename == \"./test/maps/random_order_multiple_spaces.cub\" "
				"and the file exists expected return to be true");
		config_clean(&conf);
	}
	ft_printf("%s: END\n", __FUNCTION__);
}


void test_config_init_invalid(void)
{
	ft_printf("\n%s: START\n", __FUNCTION__);
	{
		t_config_file	conf;
		FT_TEST(config_init(1, (char *[]){ "does_not_exist.cub", NULL} , &conf)
				== false,
				"when argc == 1 and filename == \"does_not_exist.cub\" "
				"expected return to be false");
	}

	{
		t_config_file	conf;
		int             result = config_init(2,
											 (char *[]) {
												"./test/maps/trivial.cub",
												"./test/maps/trivial.cub",
												NULL
											 },
											 &conf);
		FT_TEST(result == false,
				"when argc == 2 and filename == \"./test/maps/trivial.cub\" "
				"and the file exists expected return to be false");
	}

	{
		t_config_file	conf;
		int				result = \
			config_init(1, \
						(char *[]){\
							"./test/maps/invalid_floor_color_above_range.cub", \
							NULL}, \
						&conf);
		FT_TEST(result == false, \
			"when argc == 1 and "
			"filename == \"./test/maps/invalid_floor_color_above_range.cub\" "
			"and the file exists expected return to be false");
	}

	{
		t_config_file	conf;
		int				result = \
			config_init(1, \
						(char *[]){\
							"./test/maps/invalid_non_blank_fst_separator.cub", \
							NULL}, \
						&conf);
		FT_TEST(result == false, \
			"when argc == 1 and "
			"filename == \"./test/maps/invalid_non_blank_fst_separator.cub\" "
			"and the file exists expected return to be false");
	}

	{
		t_config_file	conf;
		int				result = \
			config_init(1, \
						(char *[]){\
							"./test/maps/invalid_non_blank_snd_separator.cub", \
							NULL}, \
						&conf);
		FT_TEST(result == false, \
			"when argc == 1 and "
			"filename == \"./test/maps/invalid_non_blank_snd_separator.cub\" "
			"and the file exists expected return to be false");
	}

	{
		t_config_file	conf;
		int				result = \
			config_init(1, \
						(char *[]){\
							"./test/maps/invalid_direction_north.cub", \
							NULL}, \
						&conf);
		FT_TEST(result == false, \
			"when argc == 1 and "
			"filename == \"./test/maps/invalid_direction_north.cub\" "
			"and the file exists expected return to be false");
	}

	{
		t_config_file	conf;
		int				result = \
			config_init(1, \
						(char *[]){\
							"./test/maps/invalid_direction_east.cub", \
							NULL}, \
						&conf);
		FT_TEST(result == false, \
			"when argc == 1 and "
			"filename == \"./test/maps/invalid_direction_east.cub\" "
			"and the file exists expected return to be false");
	}

	{
		t_config_file	conf;
		int				result = \
			config_init(1, \
						(char *[]){\
							"./test/maps/invalid_direction_south.cub", \
							NULL}, \
						&conf);
		FT_TEST(result == false, \
			"when argc == 1 and "
			"filename == \"./test/maps/invalid_direction_south.cub\" "
			"and the file exists expected return to be false");
	}

	{
		t_config_file	conf;
		int				result = \
			config_init(1, \
						(char *[]){\
							"./test/maps/invalid_direction_west.cub", \
							NULL}, \
						&conf);
		FT_TEST(result == false, \
			"when argc == 1 and "
			"filename == \"./test/maps/invalid_direction_west.cub\" "
			"and the file exists expected return to be false");
	}

	{
		t_config_file	conf;
		int				result = \
			config_init(1, \
						(char *[]){\
							"./test/maps/invalid_empty2.cub", \
							NULL}, \
						&conf);
		FT_TEST(result == false, \
			"when argc == 1 and "
			"filename == \"./test/maps/invalid_empty2.cub\" "
			"and the file exists expected return to be false");
	}

	{
		t_config_file	conf;
		int				result = \
			config_init(1, \
						(char *[]){\
							"./test/maps/invalid_empty.cub", \
							NULL}, \
						&conf);
		FT_TEST(result == false, \
			"when argc == 1 and "
			"filename == \"./test/maps/invalid_empty.cub\" "
			"and the file exists expected return to be false");
	}

	{
		t_config_file	conf;
		int				result = \
			config_init(1, \
						(char *[]){\
							"./test/maps/invalid_duplicate_direction.cub", \
							NULL}, \
						&conf);
		FT_TEST(result == false, \
			"when argc == 1 and "
			"filename == \"./test/maps/invalid_duplicate_direction.cub\" "
			"and the file exists expected return to be false");
	}

	{
		t_config_file	conf;
		int				result = \
			config_init(1,
						(char *[]){ "./test/maps/invalid_map_line_before_map_section.cub", NULL},
						&conf);
		FT_TEST(result == false,
				"when argc == 1 and filename == \"./test/maps/invalid_map_line_before_map_section.cub\" "
				"and the file exists expected return to be false");

		config_clean(&conf);
	}

	{
		t_config_file	conf;
		int				result = \
			config_init(1,
						(char *[]){ "./test/maps/invalid_direction_missing_north.cub", NULL},
						&conf);
		FT_TEST(result == false,
				"when argc == 1 and filename == \"./test/maps/invalid_direction_missing_north.cub\" "
				"and the file exists expected return to be false");

		config_clean(&conf);
	}
	{
		t_config_file	conf;
		int				result = \
			config_init(1,
						(char *[]){ "./test/maps/invalid_color_missing_floor.cub", NULL},
						&conf);
		FT_TEST(result == false,
				"when argc == 1 and filename == \"./test/maps/invalid_color_missing_floor.cub\" "
				"and the file exists expected return to be false");

		config_clean(&conf);
	}
	{
		t_config_file	conf;
		int				result = \
			config_init(1,
						(char *[]){ "./test/maps/invalid_map_before_elements.cub", NULL},
						&conf);
		FT_TEST(result == false,
				"when argc == 1 and filename == \"./test/maps/invalid_map_before_elements.cub\" "
				"and the file exists expected return to be false");
		config_clean(&conf);
	}

	ft_printf("%s: END", __FUNCTION__);

}


void test_config_init(void)
{
	ft_printf("\n%s: START", __FUNCTION__);
	test_config_init_invalid();
	test_config_init_valid_trivial_map();
	test_config_init_valid_random_order();
	ft_printf("%s: END\n", __FUNCTION__);
}
