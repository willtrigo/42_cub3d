/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_config_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:25:21 by maurodri          #+#    #+#             */
/*   Updated: 2025/02/19 19:41:18 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/config/config.h"
#include "ft_stdio.h"
#include "test_suite.h"



void test_config_init_valid(void)
{
	ft_printf("\n%s: START\n", __FUNCTION__);

	{
		t_config_file	conf;
		int 			result = config_init(1,
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
		int 			result = config_init(1, \
							(char *[]){ "./test/maps/invalid_floor_color_above_range.cub", NULL},
											 &conf);
		FT_TEST(result == false,
				"when argc == 1 and "
				"filename == \"./test/maps/invalid_floor_color_above_range.cub\" "
				"and the file exists expected return to be false");
	}
	ft_printf("%s: END", __FUNCTION__);
}


void test_config_init(void)
{
	ft_printf("\n%s: START", __FUNCTION__);
	test_config_init_invalid();
	test_config_init_valid();
	ft_printf("%s: END\n", __FUNCTION__);
}
