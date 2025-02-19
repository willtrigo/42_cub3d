/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_suite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:24:50 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/19 18:16:47 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "infrastructure/config/config.h"
#include "utils/color.h"
#include "infrastructure/config/parse/parse_internal.h"
#include "infrastructure/config/config_internal.h"
#include "cube.h"
#include "ft_assert.h"
#include "ft_stdio.h"
#include "test_suite.h"


void test_config_init()
{
	ft_printf("\n%s:\n", __FUNCTION__);

	{
		t_config_file	conf;
		int 			result = config_init(1,
											 (char *[]){ "does_not_exist.cub", NULL} ,
											 &conf); 
		FT_TEST(result == EXIT_FAILURE,
				"when argc == 1 and filename == \"does_not_exist.cub\" "
				"expected return to be EXIT_FAILURE");
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
		FT_TEST(result == EXIT_FAILURE,
				"when argc == 2 and filename == \"./test/maps/trivial.cub\" "
				"and the file exists expected return to be EXIT_FAILURE");
	}

	{
		t_config_file	conf;
		int 			result = config_init(1, \
							(char *[]){ "./test/maps/invalid_floor_color_above_range.cub", NULL},
											 &conf);
		FT_TEST(result == EXIT_FAILURE,
				"when argc == 1 and "
				"filename == \"./test/maps/invalid_floor_color_above_range.cub\" "
				"and the file exists expected return to be EXIT_SUCCESS");
	}

	{
		t_config_file	conf;
		int 			result = config_init(1,
											 (char *[]){ "./test/maps/trivial.cub", NULL},
											 &conf);
		FT_TEST(result == EXIT_SUCCESS,
				"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
				"and the file exists expected return to be EXIT_SUCCESS");
		FT_TEST(conf.floor.value == 0xDC6400FF,
				"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
				"and the file exists expected conf.floor.value == 0xDC6400FF");
		FT_TEST(conf.ceil.value == 0xE11E00FF,
				"when argc == 1 and filename == \"./test/maps/trivial.cub\" "
				"and the file exists expected conf.ceil.value == 0xE11E00FF");
	}
	ft_printf("%s: OK\n", __FUNCTION__);
}

void test_is_valid_args()
{
	ft_printf("\n%s:\n", __FUNCTION__);

	FT_TEST(is_invalid_args(1, "name.cub")
			== false,
			"when argc == 1 and filename == name.cub expected invalid args to be false");

	FT_TEST(is_invalid_args(0, "name.cub")
			== true,
			"when argc == 0 and filename == name.cub expected invalid args to be true");

	FT_TEST(is_invalid_args(2, "name.cub")
			== true,
			"when argc == 2 and filename == name.cub expected invalid args to be true");

	FT_TEST(is_invalid_args(1, "name")
			== true,
			"when argc == 1 and filename == name expected invalid args to be true");

	FT_TEST(is_invalid_args(1, "cub")
			== true,
			"when argc == 1 and filename == cub expected invalid args to be true");

	FT_TEST(is_invalid_args(1, ".cub")
			== false,
			"when argc == 1 and filename == .cub expected invalid args to be false");

	ft_printf("%s: OK\n", __FUNCTION__);
}

void test_color(void)
{
	ft_printf("\n%s:\n", __FUNCTION__);
	t_color color;

	color = ft_color(0, 0, 0, 0);
	FT_TEST(color.value == 0, "ft_color(0, 0, 0, 0) should have color.value == 0");

	color = ft_color(0xFF, 0, 0, 0);
	FT_TEST(color.value == 0xFF000000,
			"ft_color(0xFF, 0, 0, 0) should have color.value == 0xFF000000");

	color = ft_color(0, 0xA1, 0, 0);
	FT_TEST(color.value == 0x00A10000,
			"ft_color(0, 0xA1, 0, 0) should have color.value == 0x00A10000");

	color = ft_color(0, 0x0, 0x77, 0);
	FT_TEST(color.value == 0x00007700,
			"ft_color(0, 0, 0x77, 0) should have color.value == 0x00007700");

	color = ft_color(0, 0, 0, 0x13);
	FT_TEST(color.value == 0x000000013,
			"ft_color(0, 0, 0, 0x13) should have color.value == 0x00000013");

	color = ft_color(0xFE, 0xDC, 0xBA, 0x98);
	FT_TEST(color.value == 0xFEDCBA98,
			"ft_color(0xFE, 0xDC, 0xBA, 0x98) should have color.value == 0xFEDCBA98");
	ft_printf("%s: OK\n", __FUNCTION__);
}

void	test_parse_color(void)
{
	ft_printf("\n%s:\n", __FUNCTION__);
	t_color	color;
	bool	has_set_color;
	int		result;

	has_set_color = false;
	result = parse_color("F 220,100,0", &color, &has_set_color);
	FT_TEST(result == EXIT_SUCCESS,
		 "when parse color F 220,100,0 expect return == EXIT_SUCCESS");
	FT_TEST(color.value == 0xdc6400FF,
		 "when parse color F 220,100,0 expect color.value == xdc6400FF");
	FT_TEST(has_set_color == true,
		 "when parse color F 220,100,0 expect has_set_color == true");

	has_set_color = false;
	result = parse_color("F 220,100", &color, &has_set_color);
	FT_TEST(result == EXIT_FAILURE,
		 "when parse color F 220,100 expect == EXIT_FAILURE");
	FT_TEST(has_set_color == false,
		 "when parse color F 220,100,0 expect has_set_color == false");

	has_set_color = false;
	result = parse_color("", &color, &has_set_color);
	FT_TEST(result == EXIT_FAILURE,
		 "when parse color '' expect == EXIT_FAILURE");
	FT_TEST(has_set_color == false,
		 "when parse color '' expect has_set_color == false");

	has_set_color = false;
	result = parse_color("F 300,100,0", &color, &has_set_color);
	FT_TEST(result == EXIT_FAILURE,
		 "when invalid range 'F 300,100,0' expect == EXIT_FAILURE");
	FT_TEST(has_set_color == false,
		 "when invalid range 'F 300,100,0' expect has_set_color == false");
	ft_printf("%s: OK\n", __FUNCTION__);
}

int	main(void)
{
	test_color();
	test_parse_color();
	test_is_valid_args();
	test_config_init();
	exit (EXIT_SUCCESS);
	return (0);
}
