/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_suite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:24:50 by dande-je          #+#    #+#             */
/*   Updated: 2025/02/13 17:25:16 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "color.h"
#include "cube.h"
// #include <assert.h>
// #include <stdio.h>
#include "ft_assert.h"
#include "ft_stdio.h"

#include "test_suite.h"


void test_color(void)
{
	ft_printf("%s: ", __FUNCTION__);
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
	ft_printf("OK\n");
}

void	test_parse_color(void)
{
	ft_printf("%s: ", __FUNCTION__);
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
	ft_printf("OK\n");
}

int	main(void)
{
	test_color();
	test_parse_color();
	exit (EXIT_SUCCESS);
	return (0);
}
