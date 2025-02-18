/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_suite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:24:50 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/18 20:01:30 by maurodri         ###   ########.fr       */
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

void test_is_valid_args()
{
	ft_printf("\n%s:\n", __FUNCTION__);

	FT_TEST(is_invalid_args(1, (char *){"name.cub"})
			== false,
			"when argc == 1 and filename == name.cub expected invalid args to be false");

	FT_TEST(is_invalid_args(0, (char *){"name.cub"})
			== true,
			"when argc == 0 and filename == name.cub expected invalid args to be true");

	FT_TEST(is_invalid_args(2, (char *){"name.cub"})
			== true,
			"when argc == 2 and filename == name.cub expected invalid args to be true");

	FT_TEST(is_invalid_args(1, (char *){"name"})
			== true,
			"when argc == 1 and filename == name expected invalid args to be true");

	FT_TEST(is_invalid_args(1, (char *){"cub"})
			== true,
			"when argc == 1 and filename == cub expected invalid args to be true");

	FT_TEST(is_invalid_args(1, (char *){".cub"})
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
	exit (EXIT_SUCCESS);
	return (0);
}
